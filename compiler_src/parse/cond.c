#include "cond.h"
#include "../ast/ast_types.h"
#include "cond_internal.h"
#include "expr.h"
#include "irfixup.h"
#include "sem_common.h"

#define NTY(ty) AST_##ty *nd = (AST_##ty *)node
void resolve_cond(AST_Exp *node, BB *yes, BB *no) {
  switch (node->clkind) {
  case Exp_Rel: {
    NTY(Exp_Rel);
    ExprInfo el = resolve_expr(nd->Exp);
    ExprInfo er = resolve_expr(nd->Exp1);
    type *ut = type_unify(el.ty, er.ty);
    if (!ut) {
      REPORT_ERR(ERR_BINTY);
      goto err_out;
    }
    if (ut->ty == TY_ERROR) {
      goto err_out;
    }
    if (ut->ty == TY_ARRAY || ut->ty == TY_STRUCT) {
      REPORT_ERR(ERR_BINTY);
      goto err_out;
    }
    fixup_relop(el.op);
    fixup_relop(er.op);
    IFCond cond;

    // 0 = T_INVLAID , 1 = CC_GT ; 0 = GT
    cond.op = nd->RELOP->clkind + 1;

    cond.lhs = el.op;
    cond.rhs = er.op;

    BB_end_br(&cond, yes, no);
    break;
  }
  case Exp_Not: {
    NTY(Exp_Not);
// we will check types in next resolve_cond call
#if 0
	ExprInfo ei=resolve_expr(nd->Exp);
	type* ut=type_unify(ei.ty,type_getPrim(TY_INT));
	if(!ut){
		REPORT_ERR(ERR_BINTY);
		return;
	}
	if(TY_ISERR(ut)) return;
#endif
    return resolve_cond(nd->Exp, no, yes);
    break;
  }
  case Exp_And: {
    NTY(Exp_And);
    BB *lhs_hold = fndef_bbnew(rm_fndef);
    resolve_cond(nd->Exp, lhs_hold, no);
    BB_setcurr(lhs_hold);
    resolve_cond(nd->Exp1, yes, no);
    break;
  }
  case Exp_Or: {
    NTY(Exp_Or);
    BB *lhs_nothold = fndef_bbnew(rm_fndef);
    resolve_cond(nd->Exp, yes, lhs_nothold);
    BB_setcurr(lhs_nothold);
    resolve_cond(nd->Exp1, yes, no);
    break;
  }
  default: {
    ExprInfo ei = resolve_expr(node);

    type *ut = type_unify(ei.ty, type_getPrim(TY_INT));
    if (!ut) {
      REPORT_ERR(ERR_BINTY);
      goto err_out;
    }
    if (TY_ISERR(ut))
      goto err_out;

    fixup_relop(ei.op);
    IFCond cond;
    cond.lhs = ei.op;

    cond.rhs=op_imm(0);

    cond.op = CC_NE;

    BB_end_br(&cond, yes, no);
  }
  }
  return;
err_out:
  return;
}
