#include "bb.h"
BB *BB_new() {
  PNEW(BB, res);
  PA_INIT(res->ir);
  res->tt = 0;
  res->bbid = -1;
  return res;
}

#define clear_curr() BB_setcurr(NULL)

void BB_end_ret(pOperand v) {
  BB *bb = bb_curr;
  bb->tt = T_RET;
  bb->t_ret.op = v[0];
  clear_curr();
}

void BB_end_jmp(BB *tgt) {
  BB *bb = bb_curr;
  bb->tt = T_JMP;
  bb->t_jmp.next = tgt;
  clear_curr();
}

void BB_end_br(IFCond *cond, BB *yes, BB *no) {
  BB *bb = bb_curr;
  // FIXME: workaround incomplete IFCond init
  cond->bbid = -1;
  bb->tt = T_BR;
  bb->t_br.cond = *cond;
  bb->t_br.yes = yes;
  bb->t_br.no = no;
  clear_curr();
}

BB *bb_curr;

#define IR_NEWDEF(iname, ikind, icnt, ecnt)                                    \
  static inline iname *new_##iname() {                                         \
    PNEW(iname, res);                                                          \
    res->ext_cnt = ecnt;                                                       \
    res->in_cnt = icnt;                                                        \
    res->kind = ikind;                                                         \
    return res;                                                                \
  }

IR_NEWDEF(IRMov, IR_MOV, 1, 0)
IR_NEWDEF(IRBin, IR_BIN, 2, 1)
IR_NEWDEF(IRStr, IR_STR, 1, 0)
IR_NEWDEF(IRAlloc, IR_ALLOC, 0, 1)
// IR_NEWDEF(IRCall,IR_CALL,0,1)

static inline void insert_ir(IRBase *ir) { PA_PUSH(bb_curr->ir, IRBase, ir); }

static Operand anon_op() {
  static int cnt = 0;
  char buf[16];
  sprintf(buf, "_L_%d", ++cnt);
  return op_var(var_def(pstrdup(buf), type_getPrim(TY_INT)));
}

static void emit_builtin_memcpy(pOperand out, pOperand op0) {
  assert(out->var->ty->ty == TY_ARRAY || out->var->ty->ty == TY_STRUCT);
  int s1 = type_size(out->var->ty), s2 = type_size(op0->var->ty);
  int scpy;
  if (s1 >= s2) {
    scpy = s2;
  } else {
    scpy = s1;
  }
  Operand adr1 = anon_op(), adr2 = anon_op(), mid = anon_op();
  Operand off = op_imm(0);
  for (int i = 0; i < scpy; i += 4) {
    off.imm = i;
    // adr2 = op0 + off
    emit_bin(&adr2, B_ADD, op0, &off);
    // mid = *adr2
    adr2.type=OP_DEREF;
    emit_mov_or_str(&mid,&adr2);
    adr2.type=OP_VAR;

    // adr1 = out + off
    emit_bin(&adr1, B_ADD, out, &off);
    // *adr1 = mid
    adr1.type=OP_DEREF;
    emit_mov_or_str(&adr1,&mid);
    adr1.type=OP_VAR;
  }
}

void emit_mov_or_str(pOperand out, pOperand op0) {
  // handle array copy here
  if (out->type == OP_VAR && TY_ISPTR(out->var->ty)) {
    emit_builtin_memcpy(out, op0);
    return;
  }
  IRBase *ir;
  if (out->type == OP_DEREF) {
    ir = (IRBase *)new_IRStr();
  } else {
    ir = (IRBase *)new_IRMov();
  }
  ir->out = *out;
  ir->ops[0] = *op0;
  insert_ir(ir);
}

void emit_bin(pOperand out, binop_type binop, pOperand lhs, pOperand rhs) {
  IRBin *ir = new_IRBin();
  ir->out = *out;
  ir->binop.type = OP_BINOP;
  ir->binop.binop = binop;
  ir->op0 = *lhs;
  ir->op1 = *rhs;
  insert_ir((IRBase *)ir);
}

void emit_alloc(pOperand out, int size) {
  IRAlloc *ir = new_IRAlloc();
  ir->out = *out;
  ir->size = op_imm(size);
  insert_ir((IRBase *)ir);
}

void emit_call(pOperand out, const char *tgt, array *args) {
  IRCall *ir = palloc(sizeof(IRCall) + args->size * sizeof(Operand));
  ir->out = *out;
  ir->kind = IR_CALL;
  ir->ext_cnt = 1;
  ir->in_cnt = args->size;
  for (int i = 0; i < args->size; ++i) {
    ir->args[i] = ARRAY_AT(*args, ExprInfo, i)->op;
  }
  ir->tgt.type = OP_FN;
  ir->tgt.name = tgt;
  insert_ir((IRBase *)ir);
}