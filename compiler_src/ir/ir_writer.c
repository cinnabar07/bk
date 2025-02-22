#include "../parse/typing.h"
#include "bb.h"
FILE *iof;

static const char *CONDNAME[] = {
    " ERR ", " > ", " < ", " >= ", " <= ", " == ", " != "};
static const char *BINNAME[] = {" + ", " - ", " * ", " / "};

static int ctr = 0;
static inline void pr_op(Operand *op) {
  int has_star = 0;
  if (op->type == OP_IMM) {
    fprintf(iof, "#%d", op->imm);
    return;
  }
  if (op->type == OP_DEREF) {
    has_star = 1;
  }
  if (!has_star && op->type != OP_VAR) {
    fprintf(iof, "!err");
    return;
  }
  if (has_star)
    fputc('*', iof);
  fprintf(iof, "%s", op->var->name);
}
void pr_ir(IRBase *ir) {
  switch (ir->kind) {
  case IR_ALLOC:
    assert(ir->out.type == OP_VAR);
    fprintf(iof, "DEC %s_mem %d\n", ir->out.var->name, ir->ops[0].imm);
    fprintf(iof, "%s := &%s_mem\n", ir->out.var->name, ir->out.var->name);
    break;
  case IR_BIN:
    pr_op(&ir->out);
    fprintf(iof, "%s", " := ");
    pr_op(&ir->ops[1]);
    fprintf(iof, "%s", BINNAME[ir->ops[0].binop]);
    pr_op(&ir->ops[2]);
    fputc('\n', iof);
    break;
  case IR_CALL: {
    if (strcmp(ir->ops[0].name, "read") == 0) {
      fprintf(iof, "READ ");
      pr_op(&ir->out);
      fputc('\n', iof);
      break;
    }
    if (strcmp(ir->ops[0].name, "write") == 0) {
      fprintf(iof, "WRITE ");
      pr_op(&ir->ops[1]);
      fputc('\n', iof);
      break;
    }
    for (int i = ir->in_cnt; i >= 1; --i) {
      fprintf(iof, "ARG ");
      pr_op(&ir->ops[i]);
      fputc('\n', iof);
    }
    pr_op(&ir->out);
    fprintf(iof, " := CALL %s\n", ir->ops[0].name);
    break;
  }
  case IR_MOV:
  case IR_STR:
    pr_op(&ir->out);
    fprintf(iof, "%s", " := ");
    pr_op(&ir->ops[0]);
    fputc('\n', iof);
    break;
  default:
    break;
  }
}
static void pr_bb(BB *now) {
  for (int i = 0; i < now->ir.size; ++i) {
    IRBase *ir = PA_AT(now->ir, IRBase, i);
    pr_ir(ir);
  }
}
static void dfs_bb(BB *now) {
  if (now->bbid == -1)
    now->bbid = ++ctr;
  fprintf(iof, "LABEL label%d : \n", now->bbid);

  pr_bb(now);

  if (now->tt == T_RET) {
    fprintf(iof, "RETURN ");
    pr_op(&now->t_ret.op);
    fputc('\n', iof);
    return;
  }
  if (now->tt == T_JMP) {
    if (now->t_jmp.next->bbid != -1) {
      fprintf(iof, "GOTO label%d\n", now->t_jmp.next->bbid);
    } else {
      dfs_bb(now->t_jmp.next);
    }
    return;
  }

  if (now->tt == 0) {
    // ! this bb not terms
    return;
  }

  if (now->tt <= T_BR) {
    fprintf(iof, "IF ");
    pr_op(&now->t_br.cond.lhs);
    fprintf(iof, "%s", CONDNAME[now->t_br.cond.op]);
    pr_op(&now->t_br.cond.rhs);
    int workyes = (now->t_br.yes->bbid == -1);
    int workno = (now->t_br.no->bbid == -1);
    if (workyes)
      now->t_br.yes->bbid = ++ctr;
    if (workno)
      now->t_br.no->bbid = ++ctr;
    fprintf(iof, " GOTO label%d\n", now->t_br.yes->bbid);
    if (workno) {
      dfs_bb(now->t_br.no);
    } else {
      fprintf(iof, "GOTO label%d\n", now->t_br.no->bbid);
    }
    if (workyes) {
      dfs_bb(now->t_br.yes);
    }
    return;
  }
}
void print_fn(fndef *fd) {
  // number bb when doing dfs

  // step1. write entry info
  fprintf(iof, "FUNCTION %s :\n", fd->name);
  for (int i = 0; i < fd->arg_vars.size; ++i) {
    fprintf(iof, "PARAM %s\n", PA_AT(fd->arg_vars, var, i)->name);
  }
  // step2. dfs from entry
  dfs_bb(PA_AT(fd->bb, BB, 0));
}