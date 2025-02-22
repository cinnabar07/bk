#include "expr.h"
#include "../ast/ast_types.h"
#include "cond.h"
#include "expr_internal.h"
#include "irfixup.h"
#include "sem_common.h"

ExprInfo resolve_expr(AST_Exp *node) { return visit_Exp(node); }

static ExprInfo handle_binop(ast_base *node, ExprInfo *l, ExprInfo *r,
                             binop_type b);

static ExprInfo EI_BAD() {
  ExprInfo ei;
  ei.ty = type_getPrim(TY_ERROR);
  ei.op.type = OP_ERR;
  return ei;
}

ExprInfo visit_Exp(AST_Exp *node) {
  switch (node->clkind) {
  case 0:
    return visit_Exp_Assign((AST_Exp_Assign *)node);
    break;
  /*
  case 1: return visit_Exp_And((AST_Exp_And*)node); break;
  case 2: return visit_Exp_Or((AST_Exp_Or*)node); break;
  case 3: return visit_Exp_Rel((AST_Exp_Rel*)node); break;
  case 10: return visit_Exp_Not((AST_Exp_Not*)node); break;
  */
  case 1:
  case 2:
  case 3:
  case 10: {
    ExprInfo ret;
    ret.ty = type_getPrim(TY_INT);
    ret.op = op_var(var_def(ANON_NAME, ret.ty));
    Operand imm = op_imm(0);
    emit_mov_or_str(&ret.op, &imm);
    BB *yes = fndef_bbnew(rm_fndef);
    BB *next = fndef_bbnew(rm_fndef);

    resolve_cond(node, yes, next);
    BB_setcurr(yes);
    imm.imm = 1;
    emit_mov_or_str(&ret.op, &imm);
    BB_end_jmp(next);
    BB_setcurr(next);
    return ret;
  } break;
  case 4:
    return visit_Exp_Plus((AST_Exp_Plus *)node);
    break;
  case 5:
    return visit_Exp_Minus((AST_Exp_Minus *)node);
    break;
  case 6:
    return visit_Exp_Mul((AST_Exp_Mul *)node);
    break;
  case 7:
    return visit_Exp_Div((AST_Exp_Div *)node);
    break;
  case 8:
    return visit_Exp(((AST_Exp_P *)node)->Exp);
    break;
  case 9:
    return visit_Exp_Neg((AST_Exp_Neg *)node);
    break;
  case 11:
    return visit_Exp_Call((AST_Exp_Call *)node);
    break;
  case 12:
    return visit_Exp_CallV((AST_Exp_CallV *)node);
    break;
  case 13:
    return visit_Exp_Arr((AST_Exp_Arr *)node);
    break;
  case 14:
    return visit_Exp_Fld((AST_Exp_Fld *)node);
    break;
  case 15:
    return visit_Exp_Var((AST_Exp_Var *)node);
    break;
  case 16:
    return visit_Exp_Int((AST_Exp_Int *)node);
    break;
  case 17:
    return visit_Exp_Float((AST_Exp_Float *)node);
    break;
  }
  return EI_BAD();
}

// check lhs type
static ExprInfo visit_Exp_Assign(AST_Exp_Assign *node) {
  AST_Exp *lhs = node->Exp, *rhs = node->Exp1;
  if (lhs->clkind != Exp_Var && lhs->clkind != Exp_Arr &&
      lhs->clkind != Exp_Fld) {
    REPORT_ERR(ERR_ASSRV);
    return visit_Exp(node->Exp1);
  }
  // when clkind is Exp_Arr or Exp_Fld, el = Operand(deref,error)
  ExprInfo el = visit_Exp(lhs), er = visit_Exp(rhs);
  type *ut = type_unify(el.ty, er.ty);
  if (ut == NULL) {
    REPORT_ERR(ERR_ASSTY);
    return EI_BAD();
  }
  if (TY_ISERR(ut)) {
    return EI_BAD();
  }
  emit_mov_or_str(&el.op, &er.op);
  // el may have deref in op, use er here
  return er;
}

static ExprInfo visit_Exp_Plus(AST_Exp_Plus *node) {
  ExprInfo el = visit_Exp(node->Exp);
  ExprInfo er = visit_Exp(node->Exp1);
  return handle_binop(ABASE, &el, &er, B_ADD);
}

static ExprInfo visit_Exp_Minus(AST_Exp_Minus *node) {
  ExprInfo el = visit_Exp(node->Exp);
  ExprInfo er = visit_Exp(node->Exp1);
  return handle_binop(ABASE, &el, &er, B_SUB);
}

static ExprInfo visit_Exp_Mul(AST_Exp_Mul *node) {
  ExprInfo el = visit_Exp(node->Exp);
  ExprInfo er = visit_Exp(node->Exp1);
  return handle_binop(ABASE, &el, &er, B_MUL);
}

static ExprInfo visit_Exp_Div(AST_Exp_Div *node) {
  ExprInfo el = visit_Exp(node->Exp);
  ExprInfo er = visit_Exp(node->Exp1);
  return handle_binop(ABASE, &el, &er, B_DIV);
}

static ExprInfo handle_binop(ast_base *node, ExprInfo *l, ExprInfo *r,
                             binop_type b) {
  ExprInfo res;
  type *uty = type_unify(l->ty, r->ty);
  if (!uty) {
    REPORT_ERR(ERR_BINTY);
    return EI_BAD();
  }
  if (uty->ty == TY_ERROR) {
    return EI_BAD();
  }
  if (TY_ISPTR(uty)) {
    REPORT_ERR(ERR_BINTY);
    return EI_BAD();
  }
  res.ty = uty;
  res.op = op_var(var_def(ANON_NAME, res.ty));
  fixup_binop(l->op);
  fixup_binop(r->op);
  emit_bin(&res.op, b, &l->op, &r->op);
  return res;
}

static ExprInfo visit_Exp_Neg(AST_Exp_Neg *node) {
  ExprInfo ei = visit_Exp(node->Exp);
  ExprInfo zero;
  zero.op = op_imm(0);
  zero.ty = ei.ty;
  return handle_binop(ABASE, &zero, &ei, B_SUB);
}

static ExprInfo handle_invoke(ast_base *node, const char *name, array *argops) {
  fndef *fd = fndef_query(name);
  if (!fd) {
    if (var_query_recur(name)) {
      REPORT_ERR(ERR_FNTY);
    } else {
      REPORT_ERR(ERR_NOFN);
    }
    return EI_BAD();
  }
  if (fd->arg_ty.size != argops->size) {
    REPORT_ERR(ERR_ARG);
    return EI_BAD();
  }
  int err = 0;
  for (int i = 0; i < argops->size; ++i) {
    type *ft = PA_AT(fd->arg_ty, type, i);
    ExprInfo *aei = ARRAY_AT(*argops, ExprInfo, i);
    type *at = aei->ty;
    type *ut = type_unify(ft, at);
    if (!ut) {
      REPORT_ERR(ERR_ARG);
      err = 1;
    } else {
      if (TY_ISERR(ut))
        err = 1;
      else {
        fixup_argop(aei->op);
      }
    }
  }
  if (err) {
    return EI_BAD();
  }
  ExprInfo res;
  res.ty = fd->ret_ty;
  res.op = op_var(var_def(ANON_NAME, res.ty));
  emit_call(&res.op, name, argops);
  return res;
}

static ExprInfo visit_Exp_Call(AST_Exp_Call *node) {
  array ops;
  array_init(&ops);
  AST_Args *now = node->Args;
  while (1) {
    ExprInfo arg = visit_Exp(now->b1.Exp);
    ARRAY_PUSH(ops, ExprInfo, arg);
    if (now->clkind == Args_1) {
      break;
    } else {
      now = now->b0.Args;
    }
  }
  return handle_invoke(ABASE, node->ID->v, &ops);
}

static ExprInfo visit_Exp_CallV(AST_Exp_CallV *node) {
  array ops;
  array_init(&ops);
  return handle_invoke(ABASE, node->ID->v, &ops);
}

static ExprInfo visit_Exp_Arr(AST_Exp_Arr *node) {
  ExprInfo res;
  ExprInfo eb = visit_Exp(node->Exp);
  ExprInfo ei = visit_Exp(node->Exp1);
  {
    int err = 0;
    if (ei.ty->ty != TY_ERROR && ei.ty->ty != TY_INT) {
      REPORT_ERR(ERR_AINDTY);
      err = 1;
    }
    if (eb.ty->ty != TY_ERROR && eb.ty->ty != TY_ARRAY) {
      REPORT_ERR(ERR_ABASETY);
      err = 1;
    }
    if (err || TY_ISERR(eb.ty) || TY_ISERR(ei.ty)) {
      return EI_BAD();
    }
  }
  // ei.op contains address of struct
  ExprInfo stride;
  stride.op = op_imm(type_size(eb.ty->array.chd));
  stride.ty = type_getPrim(TY_INT);

  ExprInfo offset = handle_binop(ABASE, &stride, &ei, B_MUL);
  // dirty hack here to make handle_binop happy
  enum typekind oldty = eb.ty->ty;
  eb.ty->ty = TY_INT;
  ExprInfo address = handle_binop(ABASE, &eb, &offset, B_ADD);
  eb.ty->ty = oldty;

  res.ty = eb.ty->array.chd;
  res.op = address.op;
  assert(res.op.type==OP_VAR);
  res.op.var->ty=res.ty;
  if (!TY_ISPTR(res.ty)) {
    res.op.type = OP_DEREF;
  }
  return res;
}

static ExprInfo visit_Exp_Fld(AST_Exp_Fld *node) {
  ExprInfo res;
  ExprInfo ei = visit_Exp(node->Exp);
  char *fname = node->ID->v;
  if (ei.ty->ty == TY_ERROR) {
    return EI_BAD();
  }
  if (ei.ty->ty != TY_STRUCT) {
    REPORT_ERR(ERR_STRUTY);
    return EI_BAD();
  }
  structfld *fd = structdef_queryfld(ei.ty->sdef, fname);
  if (!fd) {
    REPORT_ERR(ERR_NOFLD);
    return EI_BAD();
  }

  // ei.op contains address of struct
  ExprInfo offset;
  offset.op = op_imm(fd->offset);
  offset.ty = type_getPrim(TY_INT);

  // dirty hack here to make handle_binop happy
  enum typekind oldty = ei.ty->ty;
  ei.ty->ty = TY_INT;
  ExprInfo address = handle_binop(ABASE, &ei, &offset, B_ADD);
  ei.ty->ty = oldty;
  // address = Operand(var)

  res.ty = fd->ty;
  res.op = address.op;
  assert(res.op.type==OP_VAR);
  res.op.var->ty=res.ty;
  if (!TY_ISPTR(res.ty)) {
    res.op.type = OP_DEREF;
  }
  return res;
}

static ExprInfo visit_Exp_Var(AST_Exp_Var *node) {
  char *vname = node->ID->v;
  var *v = var_query_recur(vname);
  if (!v) {
    REPORT_ERR(ERR_NOVAR);
    return EI_BAD();
  }
  ExprInfo ret;
  ret.ty = v->ty;
  ret.op = op_var(v);
  return ret;
}

static ExprInfo visit_Exp_Int(AST_Exp_Int *node) {
  ExprInfo ret;
  ret.ty = type_getPrim(TY_INT);
  ret.op = op_imm(node->INT->v);
  return ret;
}

static ExprInfo visit_Exp_Float(AST_Exp_Float *node) {
  ExprInfo ret;
  ret.ty = type_getPrim(TY_FLOAT);
  // TODO: support float here
  ret.op.type = OP_IMM;
  ret.op.imm = 0;
  return ret;
}
