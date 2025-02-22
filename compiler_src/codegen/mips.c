#include "../ir/bb.h"
#include "../parse/typing.h"
extern FILE *iof;
extern void pr_ir(IRBase *ir);
FILE *cg_iof;
static int ctr = 0;

static inline void restore_ra();
static inline void save_ra();
static void cg_leave_ret();

#define cprintf(f, ...) fprintf(cg_iof, f, __VA_ARGS__)
#define cprintl(f, ...) fprintf(cg_iof, "\t" f "\n", __VA_ARGS__)
#define cputl(x) fputs("\t" x "\n", cg_iof)

typedef struct fnInfo {
  int msize;
  int is_leaf;
} fnInfo;

static fnInfo cfi;

#define IS_S16(x) (((short)x) == x)

#define REG_RET 2
#define REG_TMP1 3
#define REG_TMP2 4
#define REG_START 5
#define REG_END 25

#define REG_SP 29

#define CACHE_SIZE (REG_END - REG_START + 1)

#define S2REG(sid) ((sid) + REG_START)

// use new type for cache slot id to avoid confusion with reg id
typedef int sid_t;

static inline void emit_lw(int off, int tgt) {
  assert(IS_S16(off));
  cprintl("lw $%d,%d($fp)", tgt, off);
}

static inline void emit_sw(int off, int tgt) {
  assert(IS_S16(off));
  cprintl("sw $%d,%d($fp)", tgt, off);
}

static inline void emit_swreg(int addrreg, int tgt) {
  cprintl("sw $%d,0($%d)", tgt, addrreg);
}

static inline void emit_lwreg(int addrreg, int tgt) {
  cprintl("lw $%d,0($%d)", tgt, addrreg);
}

static inline void emit_mov(int dst, int src) {
  cprintl("move $%d,$%d", dst, src);
}

static inline void emit_li(int imm, int tgt) { cprintl("li $%d,%d", tgt, imm); }

static inline void emit_alloca(int size, int tgt) {
  if(IS_S16(size)){
    cprintl("addi $sp,$sp,-%d", size);
  }else{
    cprintl("li $%d,%d",REG_TMP1,size);
    cprintl("subu $sp,$sp,$%d",REG_TMP1);
  }
  cprintl("move $%d,$sp", tgt);
}



// cache slot's memoff, 0 = invalid
static int cache_moff[CACHE_SIZE];
static int cache_dirty[CACHE_SIZE];
static int cache_atime[CACHE_SIZE];

static int time_stamp;

static void reset_cache() {
  bzero(cache_moff, sizeof(cache_moff));
  bzero(cache_dirty, sizeof(cache_dirty));
  bzero(cache_atime, sizeof(cache_atime));
}

static inline void flush_cache_slot(sid_t id) {
  if (!cache_dirty[id] || !cache_moff[id])
    return;
  emit_sw(cache_moff[id], S2REG(id));
}

// writeback cache. note that we do not clear dirty bits here
static void flush_cache() {
  for (sid_t i = 0; i < CACHE_SIZE; ++i) {
    flush_cache_slot(i);
  }
}

static inline sid_t alloc_cache_slot(int off) {
  // 1. find an invalid slot
  sid_t i = 0;
  for (; i < CACHE_SIZE; ++i) {
    if (cache_moff[i] == 0)
      break;
  }
  if (i != CACHE_SIZE) {
    cache_moff[i] = off;
    cache_dirty[i] = 0;
    cache_atime[i] = ++time_stamp;
    return i;
  }
  // 2. find LRU slot
  sid_t best = -1;
  int min_time = 2100000000;
  for (i = 0; i < CACHE_SIZE; ++i) {
    if (cache_atime[i] < min_time) {
      min_time = cache_atime[i];
      best = i;
    }
  }
  flush_cache_slot(best);
  cache_moff[best] = off;
  cache_dirty[best] = 0;
  cache_atime[best] = ++time_stamp;
  return best;
}

static inline sid_t cache_lookup(int off) {
  for (sid_t i = 0; i < CACHE_SIZE; ++i) {
    if (cache_moff[i] == off) {
      cache_atime[i] = ++time_stamp;
      return i;
    }
  }
  return -1;
}

static int reg_for_write(int off) {
  sid_t cid = cache_lookup(off);
  if (cid == -1) {
    cid = alloc_cache_slot(off);
  }
  cache_dirty[cid] = 1;
  return S2REG(cid);
}

static int reg_for_read(int off) {
  sid_t cid = cache_lookup(off);
  if (cid == -1) {
    cid = alloc_cache_slot(off);
    emit_lw(off, S2REG(cid));
  }
  return S2REG(cid);
}

static inline void restore_ra() {
  if (cfi.is_leaf)
    return;
  cputl("lw $ra, -4($fp)");
}

static inline void save_ra() {
  if (cfi.is_leaf)
    return;
  cputl("sw $ra, -4($fp)");
}

static inline int do_op2reg(pOperand op, int tmpreg) {
  if (op->type == OP_VAR) {
    return reg_for_read(op->var->off);
  }
  if (op->type == OP_IMM) {
    if (op->imm == 0)
      return 0;
    emit_li(op->imm, tmpreg);
    return tmpreg;
  }
  if (op->type == OP_DEREF) {
    emit_lwreg(reg_for_read(op->var->off), tmpreg);
    return tmpreg;
  }
  assert(0);
}

static int op2reg(pOperand op) { return do_op2reg(op, REG_TMP1); }
static int op2reg2(pOperand op) { return do_op2reg(op, REG_TMP2); }

static void op2reg_fixed(pOperand op, int reg) {
  int res = do_op2reg(op, reg);
  if (res != reg)
    emit_mov(reg, res);
}

static void cg_pr_bb(BB *now) {
  for (int i = 0; i < now->ir.size; ++i) {
    IRBase *ir = PA_AT(now->ir, IRBase, i);
    //fprintf(cg_iof, "# ");
    //pr_ir(ir);

    switch (ir->kind) {
    case IR_ALLOC: {
      IRAlloc *ia = (IRAlloc *)ir;
      assert(ia->out.type == OP_VAR);
      int wr = reg_for_write(ia->out.var->off);
      emit_alloca(ia->size.imm, wr);
    } break;
    case IR_BIN: {
      IRBin *ib = (IRBin *)ir;
      int l = op2reg(&ib->op0), r = op2reg2(&ib->op1);
      int wr = reg_for_write(ib->out.var->off);
      switch (ib->binop.binop) {
      case B_ADD:
        cprintl("addu $%d,$%d,$%d", wr, l, r);
        break;
      case B_SUB:
        cprintl("subu $%d,$%d,$%d", wr, l, r);
        break;
      case B_MUL:
        cprintl("mult $%d,$%d", l, r);
        cprintl("mflo $%d", wr);
        break;
      case B_DIV:
        cprintl("div $%d,$%d", l, r);
        cprintl("mflo $%d", wr);
        break;
      default:
        break;
      }
    } break;
    case IR_CALL: {
      cprintl("addi $sp,$sp,-%d", ir->in_cnt * 4);
      for (int i = 1; i <= ir->in_cnt; ++i) {
        cprintl("sw $%d,%d($sp)", op2reg(&ir->ops[i]), 4 * (i - 1));
      }
      flush_cache();
      const char *n = ir->ops[0].name;
      if (strcmp(n, "main") == 0) {
        cputl("jal main");
      } else {
        cprintl("jal .F%s", ir->ops[0].name);
      }
      cprintl("addi $sp,$sp,%d", ir->in_cnt * 4);
      reset_cache();
      int wr = reg_for_write(ir->out.var->off);
      emit_mov(wr, REG_RET);
      break;
    }
    case IR_MOV: {
      // lhs is var
      IRMov *im = (IRMov *)ir;
      int wr = reg_for_write(im->out.var->off);
      op2reg_fixed(&im->op0, wr);
    } break;
    case IR_STR: {
      IRStr *im = (IRStr *)ir;
      int rhs = op2reg(&im->op0);
      int addr = reg_for_read(im->out.var->off);
      emit_swreg(addr, rhs);
    } break;
    default:
      break;
    }
  }
}

static const char *TT2BRASM[] = {"err", "bgt", "blt", "bge",
                                 "ble", "beq", "bne"};
static void cg_dfs_bb(BB *now) {
  reset_cache();

  if (now->bbid == -1)
    now->bbid = ++ctr;
  cprintf(".label%d : \n", now->bbid);
  cg_pr_bb(now);

  if (now->tt == T_RET) {
    op2reg_fixed(&now->t_ret.op, REG_RET);
  // no need to flush cache here
  cleanup_and_ret:
    cg_leave_ret();
    return;
  }

  if (now->tt == 0) {
    // ! this bb does not term, fix it
    // goto cleanup_and_ret;
    assert(0 && "codegen: function does not return");
  }

  if (now->tt == T_JMP) {
    flush_cache();
    if (now->t_jmp.next->bbid != -1) {
      cprintl("j .label%d", now->t_jmp.next->bbid);
    } else {
      cg_dfs_bb(now->t_jmp.next);
    }
    return;
  }

  if (now->tt <= T_BR) {
    // a little difficult here due to bad IR :)
    int l = op2reg(&now->t_br.cond.lhs), r = op2reg2(&now->t_br.cond.rhs);

    int workyes = (now->t_br.yes->bbid == -1);
    int workno = (now->t_br.no->bbid == -1);
    if (workyes)
      now->t_br.yes->bbid = ++ctr;
    if (workno)
      now->t_br.no->bbid = ++ctr;

    flush_cache();
    cprintl("%s $%d,$%d,.label%d", TT2BRASM[now->tt], l, r,
            now->t_br.yes->bbid);

    if (workno) {
      cg_dfs_bb(now->t_br.no);
    } else {
      cprintl("j .label%d", now->t_br.no->bbid);
    }
    if (workyes) {
      cg_dfs_bb(now->t_br.yes);
    }
    return;
  }
}

static fnInfo cg_preproc(fndef *fd) {
  assert(fd->vars.size<1024);
  fnInfo res;
  res.is_leaf = 1;
  // clear bbids, and check leaf
  for (int i = 0; i < fd->bb.size; ++i) {
    BB *bb = PA_AT(fd->bb, BB, i);
    bb->bbid = -1;
    for (int j = 0; j < bb->ir.size; ++j) {
      IRBase *ir = PA_AT(bb->ir, IRBase, j);
      if (ir->kind == IR_CALL) {
        res.is_leaf = 0;
        break;
      }
    }
  }
  for (int i = 0; i < fd->vars.size; ++i) {
    var *v = PA_AT(fd->vars, var, i);
    v->off = v->moff = 0;
  }
  // alloc stack
  for (int i = 0; i < fd->arg_vars.size; ++i) {
    var *v = PA_AT(fd->arg_vars, var, i);
    v->off = 4 * (i + 1);
  }
  // -4 for LR
  int next_slot = res.is_leaf ? -4 : -8;
  for (int i = 0; i < fd->vars.size; ++i) {
    var *v = PA_AT(fd->vars, var, i);
    if (!v->off) {
      v->off = next_slot;
      next_slot -= 4;
    }
  }
  res.msize = -next_slot - 4;
  assert(res.msize<=4096);
  return res;
}

static void cg_leave_ret() {
  restore_ra();
  // use a safer impl even though no intr
  cputl("move $sp,$fp");
  cputl("lw $fp,0($sp)");
  cputl("addi $sp,$sp,4");
  cputl("jr $ra");
}

void cg_fn(fndef *fd) {
  time_stamp = 0;
  cfi = cg_preproc(fd);
  // step1. write entry info
  if (strcmp(fd->name, "main") == 0)
    cprintf("%s:\n", fd->name);
  else
    cprintf(".F%s:\n", fd->name);

  cputl("addi $sp, $sp, -4");
  cputl("sw $fp, 0($sp)");
  cputl("move $fp, $sp");
  cprintl("addi $sp, $sp, -%d", cfi.msize);

  save_ra();

  // step2. dfs from entry
  cg_dfs_bb(PA_AT(fd->bb, BB, 0));
  fputc('\n', cg_iof);
}

static const char start[] = ".globl main\n"
                            ".text\n"
                            ".Fread:\n"
                            "li $2, 0\n"
                            "jr $ra\n" // stub
                            ".Fwrite:\n"
                            "jr $ra\n"; // stub

void cg_boot() {
  fputs(start, cg_iof);
  iof = cg_iof;
}