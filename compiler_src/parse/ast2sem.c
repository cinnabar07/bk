#include "ast2sem.h"
#include "../ir/bb.h"
#include "cond.h"
#include "expr.h"
#include "irfixup.h"
#include "sem_common.h"
#include "typing.h"

void visit_program(AST_Program *pg,int bootstrap) {
  init_typing();
  if(bootstrap){
    fndef_def("read",type_getPrim(TY_INT));
    fndef* fd=fndef_def("write",type_getPrim(TY_INT));
    PA_PUSH(fd->arg_ty,type,type_getPrim(TY_INT));
  }
  visit_Program(pg);
}

// right most specifier ( to deduce type for vardec and retty for fundec )
static type *rm_specifier;
// right most fndef ( to insert args )
fndef *rm_fndef;

static structdef *dec_handler; // NULL = not in struct def

typedef struct vardec {
  type *ty;
  char *name;
} vardec;

static void *visit_Program(AST_Program *node) {
  void *res = NULL;
  // pre
  res = visit_child_Program(node);
  // post
  return res;
}
static void *visit_child_Program(AST_Program *node) {
  void *res = NULL;
  if (node->ExtDefList)
    res = visit_ExtDefList(node->ExtDefList);
  return res;
}
static void *visit_ExtDefList(AST_ExtDefList *node) {
  void *res = NULL;
  // pre
  res = visit_child_ExtDefList(node);
  // post
  return res;
}
static void *visit_child_ExtDefList(AST_ExtDefList *node) {
  void *res = NULL;
  res = visit_ExtDef(node->ExtDef);
  if (node->ExtDefList)
    res = visit_ExtDefList(node->ExtDefList);
  return res;
}
static void *visit_ExtDef(AST_ExtDef *node) {
  void *res = NULL;
  switch (node->clkind) {
  case 0:
    res = visit_ExtDef_Var((AST_ExtDef_Var *)node);
    break;
  case 1:
    res = visit_ExtDef_MayStruct((AST_ExtDef_MayStruct *)node);
    break;
  case 2:
    res = visit_ExtDef_Fn((AST_ExtDef_Fn *)node);
    break;
  }
  return res;
}
static void *visit_ExtDef_Var(AST_ExtDef_Var *node) {
  void *res = NULL;
  // pre
  res = visit_child_ExtDef_Var(node);
  // post
  return res;
}
static void *visit_child_ExtDef_Var(AST_ExtDef_Var *node) {
  void *res = NULL;
  res = visit_Specifier(node->Specifier);
  res = visit_ExtDecList(node->ExtDecList);
  // lex node SEMI
  return res;
}
static void *visit_ExtDef_MayStruct(AST_ExtDef_MayStruct *node) {
  void *res = NULL;
  // pre
  res = visit_child_ExtDef_MayStruct(node);
  // post
  return res;
}
static void *visit_child_ExtDef_MayStruct(AST_ExtDef_MayStruct *node) {
  void *res = NULL;
  res = visit_Specifier(node->Specifier);
  // lex node SEMI
  return res;
}
static void *visit_ExtDef_Fn(AST_ExtDef_Fn *node) {
  void *res = NULL;
  // pre
  res = visit_child_ExtDef_Fn(node);
  // post
  return res;
}
static void *visit_child_ExtDef_Fn(AST_ExtDef_Fn *node) {
  void *res = NULL;
  res = visit_Specifier(node->Specifier);
  res = visit_FunDec(node->FunDec);
  res = visit_CompSt(node->CompSt);
  env_pop();
  rm_fndef=NULL;
  return res;
}
static void *visit_ExtDecList(AST_ExtDecList *node) {
  void *res = NULL;
  switch (node->clkind) {
  case 0:
    res = visit_ExtDecList_0((AST_ExtDecList_0 *)node);
    break;
  case 1:
    res = visit_ExtDecList_1((AST_ExtDecList_1 *)node);
    break;
  }
  return res;
}
static void *visit_ExtDecList_0(AST_ExtDecList_0 *node) {
  void *res = NULL;
  // pre
  res = visit_child_ExtDecList_0(node);
  // post
  return res;
}

static void globval_def(ast_base *node, vardec *vd) {
  // check if vd name exists ( var/struct )
  ERROR_ON(var_query(vd->name) || structdef_query(vd->name), ERR_DUPVAR);
  var_def(vd->name, vd->ty);
}

static void *visit_child_ExtDecList_0(AST_ExtDecList_0 *node) {
  void *res = NULL;
  vardec *dec = visit_VarDec(node->VarDec);
  globval_def(ABASE, dec);
  // lex node COMMA
  res = visit_ExtDecList(node->ExtDecList);
  return res;
}
static void *visit_ExtDecList_1(AST_ExtDecList_1 *node) {
  void *res = NULL;
  // pre
  res = visit_child_ExtDecList_1(node);
  // post
  return res;
}
static void *visit_child_ExtDecList_1(AST_ExtDecList_1 *node) {
  void *res = NULL;
  vardec *dec = visit_VarDec(node->VarDec);
  globval_def(ABASE, dec);
  return res;
}
static type *visit_Specifier(AST_Specifier *node) {
  type *res = NULL;
  switch (node->clkind) {
  case 0:
    res = visit_Specifier_Ty((AST_Specifier_Ty *)node);
    break;
  case 1:
    res = visit_Specifier_Struct((AST_Specifier_Struct *)node);
    break;
  }
  return rm_specifier = res;
}
static type *visit_Specifier_Ty(AST_Specifier_Ty *node) {
  type *res = NULL;
  // pre
  if (node->TYPE->clkind) {
    // float
    return type_getPrim(TY_FLOAT);
  } else {
    // int
    return type_getPrim(TY_INT);
  }
  // post
  return res;
}
static type *visit_child_Specifier_Ty(AST_Specifier_Ty *node) {
  type *res = NULL;
  // lex node TYPE
  return res;
}
static type *visit_Specifier_Struct(AST_Specifier_Struct *node) {
  type *res = NULL;
  // pre
  res = visit_child_Specifier_Struct(node);
  // post
  return res;
}
static type *visit_child_Specifier_Struct(AST_Specifier_Struct *node) {
  type *res = NULL;
  res = visit_StructSpecifier(node->StructSpecifier);
  return res;
}
static type *visit_StructSpecifier(AST_StructSpecifier *node) {
  type *res = NULL;
  switch (node->clkind) {
  case 0:
    res = visit_StructSpecifier_Ref((AST_StructSpecifier_Ref *)node);
    break;
  case 1:
    res = visit_StructSpecifier_Def((AST_StructSpecifier_Def *)node);
    break;
  }
  return res;
}
static type *visit_StructSpecifier_Ref(AST_StructSpecifier_Ref *node) {
  // pre
  char *sname = node->Tag->ID->v;
  structdef *sd = structdef_query(sname);
  if (!sd) {
    REPORT_ERR(ERR_NOSTRU);
    return type_getPrim(TY_ERROR);
  }
  return type_new_struct(sd);
  // post
}
static void *visit_child_StructSpecifier_Ref(AST_StructSpecifier_Ref *node) {
  // type* res=NULL;
  //  lex node STRUCT
  // res=visit_Tag(node->Tag);
  return NULL;
}
static type *visit_StructSpecifier_Def(AST_StructSpecifier_Def *node) {
  type *res = NULL;
  // pre
  res = visit_child_StructSpecifier_Def(node);
  // post
  return res;
}
static type *visit_child_StructSpecifier_Def(AST_StructSpecifier_Def *node) {
  // lex node STRUCT
  char *defname = NULL;
  if (node->OptTag)
    defname = visit_OptTag(node->OptTag);
  else
    defname = ANON_NAME;
  const int is_dup = structdef_query(defname) || var_query_recur(defname);
  ERROR_ON(is_dup, ERR_DUPSTRU);
  // we will cont handling even when dup, but use an anon name
  if (is_dup) {
    defname = ANON_NAME;
  }
  structdef *sd = structdef_def(defname);

  structdef *old_dh = dec_handler;
  dec_handler = sd;

  // lex node LC
  if (node->DefList)
    visit_DefList(node->DefList);
  // lex node RC

  dec_handler = old_dh;

  if (is_dup) {
    // error type
    return type_getPrim(TY_ERROR);
  } else {
    return type_new_struct(sd);
  }
}
static char *visit_OptTag(AST_OptTag *node) { return node->ID->v; }
static void *visit_child_OptTag(AST_OptTag *node) {
  void *res = NULL;
  // lex node ID
  return res;
}
static char *visit_Tag(AST_Tag *node) { return node->ID->v; }
static void *visit_child_Tag(AST_Tag *node) {
  void *res = NULL;
  // lex node ID
  return res;
}
static vardec *visit_VarDec(AST_VarDec *node) {
  vardec *res = NULL;
  switch (node->clkind) {
  case 0:
    res = visit_VarDec_Var((AST_VarDec_Var *)node);
    break;
  case 1:
    res = visit_VarDec_Array((AST_VarDec_Array *)node);
    break;
  }
  // printf("vd %s type %s\n",res->name,type_debug(res->ty));
  return res;
}
static vardec *visit_VarDec_Var(AST_VarDec_Var *node) {
  void *res = NULL;
  // pre
  res = visit_child_VarDec_Var(node);
  // post
  return res;
}
static vardec *visit_child_VarDec_Var(AST_VarDec_Var *node) {
  // lex node ID
  PNEW(vardec, res);
  res->name = node->ID->v;
  res->ty = rm_specifier;
  return res;
}
static vardec *visit_VarDec_Array(AST_VarDec_Array *node) {
  void *res = NULL;
  // pre
  res = visit_child_VarDec_Array(node);
  // post
  return res;
}
static vardec *visit_child_VarDec_Array(AST_VarDec_Array *node) {
  vardec *res = NULL;
  res = visit_VarDec(node->VarDec);
  // lex node LB
  // lex node INT
  // lex node RB

  // insert array indice
  type **top = &res->ty;
  while ((*top)->ty == TY_ARRAY) {
    top = &((*top)->array.chd);
  }
  *top = type_new_arr(*top, node->INT->v);
  return res;

  return res;
}
static void *visit_FunDec(AST_FunDec *node) {
  void *res = NULL;
  switch (node->clkind) {
  case 0:
    res = visit_FunDec_HasArg((AST_FunDec_HasArg *)node);
    break;
  case 1:
    res = visit_FunDec_NoArg((AST_FunDec_NoArg *)node);
    break;
  }
  return res;
}
static void *visit_FunDec_HasArg(AST_FunDec_HasArg *node) {
  void *res = NULL;
  // pre
  res = visit_child_FunDec_HasArg(node);
  // post
  return res;
}

static void handle_newfunc(ast_base *node, char *name) {
  if (fndef_query(name)) {
    REPORT_ERR(ERR_DUPFN);
    name = ANON_NAME;
  }
  rm_fndef = fndef_def(name, rm_specifier);
  env_push();
  BB_setcurr(fndef_bbnew(rm_fndef));
}

static void *visit_child_FunDec_HasArg(AST_FunDec_HasArg *node) {
  void *res = NULL;
  // register fndef and enter new env
  handle_newfunc(ABASE, node->ID->v);

  // lex node ID
  // lex node LP
  res = visit_VarList(node->VarList);
  // lex node RP
  return res;
}
static void *visit_FunDec_NoArg(AST_FunDec_NoArg *node) {
  void *res = NULL;
  // pre
  res = visit_child_FunDec_NoArg(node);
  // post
  return res;
}
static void *visit_child_FunDec_NoArg(AST_FunDec_NoArg *node) {
  void *res = NULL;
  // register fndef and enter new env
  handle_newfunc(ABASE, node->ID->v);

  // lex node ID
  // lex node LP
  // lex node RP
  return res;
}
static void *visit_VarList(AST_VarList *node) {
  void *res = NULL;
  switch (node->clkind) {
  case 0:
    res = visit_VarList_0((AST_VarList_0 *)node);
    break;
  case 1:
    res = visit_VarList_1((AST_VarList_1 *)node);
    break;
  }
  return res;
}
static void *visit_VarList_0(AST_VarList_0 *node) {
  void *res = NULL;
  // pre
  res = visit_child_VarList_0(node);
  // post
  return res;
}
static void *visit_child_VarList_0(AST_VarList_0 *node) {
  void *res = NULL;
  res = visit_ParamDec(node->ParamDec);
  // lex node COMMA
  res = visit_VarList(node->VarList);
  return res;
}
static void *visit_VarList_1(AST_VarList_1 *node) {
  void *res = NULL;
  // pre
  res = visit_child_VarList_1(node);
  // post
  return res;
}
static void *visit_child_VarList_1(AST_VarList_1 *node) {
  void *res = NULL;
  res = visit_ParamDec(node->ParamDec);
  return res;
}
static void *visit_ParamDec(AST_ParamDec *node) {
  // pre
  vardec *vd = visit_child_ParamDec(node);
  // arg var
  if (var_query(vd->name)) {
    REPORT_ERR(ERR_DUPVAR);
    vd->name = ANON_NAME;
  } else {
    if (structdef_query(vd->name)) {
      REPORT_ERR(ERR_DUPVAR);
    }
  }
  var *v = var_def(vd->name, vd->ty);
  fndef_addarg(rm_fndef, v);
  // post
  return NULL;
}
static vardec *visit_child_ParamDec(AST_ParamDec *node) {
  visit_Specifier(node->Specifier);
  return visit_VarDec(node->VarDec);
}
static void *visit_CompSt(AST_CompSt *node) {
  void *res = NULL;
  // pre
  res = visit_child_CompSt(node);
  // post
  return res;
}
static void *visit_child_CompSt(AST_CompSt *node) {
  void *res = NULL;
  // lex node LC

  structdef *old_dh = dec_handler;
  dec_handler = NULL;

  if (node->DefList)
    res = visit_DefList(node->DefList);

  dec_handler = old_dh;

  if (node->StmtList)
    res = visit_StmtList(node->StmtList);
  // lex node RC
  return res;
}
static void *visit_StmtList(AST_StmtList *node) {
  void *res = NULL;
  // pre
  res = visit_child_StmtList(node);
  // post
  return res;
}
static void *visit_child_StmtList(AST_StmtList *node) {
  void *res = NULL;
  res = visit_Stmt(node->Stmt);
  if (node->StmtList)
    res = visit_StmtList(node->StmtList);
  return res;
}
static void *visit_Stmt(AST_Stmt *node) {
  void *res = NULL;
  switch (node->clkind) {
  case 0:
    res = visit_Stmt_Expr((AST_Stmt_Expr *)node);
    break;
  case 1:
    res = visit_Stmt_Comp((AST_Stmt_Comp *)node);
    break;
  case 2:
    res = visit_Stmt_Ret((AST_Stmt_Ret *)node);
    break;
  case 3:
    res = visit_Stmt_If((AST_Stmt_If *)node);
    break;
  case 4:
    res = visit_Stmt_Ife((AST_Stmt_Ife *)node);
    break;
  case 5:
    res = visit_Stmt_While((AST_Stmt_While *)node);
    break;
  }
  return res;
}
static void *visit_Stmt_Expr(AST_Stmt_Expr *node) {
  resolve_expr(node->Exp);
  return NULL;
}

static void *visit_Stmt_Comp(AST_Stmt_Comp *node) {
  void *res = NULL;
  env_push();
  // pre
  res = visit_child_Stmt_Comp(node);
  // post
  env_pop();
  return res;
}
static void *visit_child_Stmt_Comp(AST_Stmt_Comp *node) {
  void *res = NULL;
  res = visit_CompSt(node->CompSt);
  return res;
}
static void *visit_Stmt_Ret(AST_Stmt_Ret *node) {
  ExprInfo ei = visit_Exp(node->Exp);
  type *ut = type_unify(rm_fndef->ret_ty, ei.ty);
  if (!ut) {
    REPORT_ERR(ERR_RETTY);
    return NULL;
  }
  if (TY_ISERR(ut)) {
    return NULL;
  }
  fixup_retop(ei.op);
  BB_end_ret(&ei.op);
  // create a dummy bb to avoid crash
  BB_setcurr(fndef_bbnew(rm_fndef));
  return NULL;
}

static void *visit_Stmt_If(AST_Stmt_If *node) {
  BB *cont = fndef_bbnew(rm_fndef);
  BB *yes = fndef_bbnew(rm_fndef);
  resolve_cond(node->Exp, yes, cont);
  BB_setcurr(yes);
  visit_Stmt(node->Stmt);
  BB_end_jmp(cont);
  BB_setcurr(cont);
  return NULL;
}

static void *visit_Stmt_Ife(AST_Stmt_Ife *node) {
  BB *cont = fndef_bbnew(rm_fndef);
  BB *yes = fndef_bbnew(rm_fndef);
  BB *no = fndef_bbnew(rm_fndef);
  resolve_cond(node->Exp, yes, no);
  BB_setcurr(yes);
  visit_Stmt(node->Stmt);
  BB_end_jmp(cont);
  BB_setcurr(no);
  visit_Stmt(node->Stmt1);
  BB_end_jmp(cont);
  BB_setcurr(cont);
  return NULL;
}

static void *visit_Stmt_While(AST_Stmt_While *node) {
  BB *check = fndef_bbnew(rm_fndef);
  BB *body = fndef_bbnew(rm_fndef);
  BB *cont = fndef_bbnew(rm_fndef);
  BB_end_jmp(check);
  BB_setcurr(check);
  resolve_cond(node->Exp, body, cont);
  BB_setcurr(body);
  visit_Stmt(node->Stmt);
  BB_end_jmp(check);
  BB_setcurr(cont);
  return NULL;
}

static void *visit_DefList(AST_DefList *node) {
  void *res = NULL;
  // pre
  res = visit_child_DefList(node);
  // post
  return res;
}
static void *visit_child_DefList(AST_DefList *node) {
  void *res = NULL;
  res = visit_Def(node->Def);
  if (node->DefList)
    res = visit_DefList(node->DefList);
  return res;
}
static void *visit_Def(AST_Def *node) {
  void *res = NULL;
  // pre
  res = visit_child_Def(node);
  // post
  return res;
}
static void *visit_child_Def(AST_Def *node) {
  void *res = NULL;
  res = visit_Specifier(node->Specifier);
  res = visit_DecList(node->DecList);
  // lex node SEMI
  return res;
}
static void *visit_DecList(AST_DecList *node) {
  void *res = NULL;
  switch (node->clkind) {
  case 0:
    res = visit_DecList_0((AST_DecList_0 *)node);
    break;
  case 1:
    res = visit_DecList_1((AST_DecList_1 *)node);
    break;
  }
  return res;
}
static void *visit_DecList_0(AST_DecList_0 *node) {
  void *res = NULL;
  // pre
  res = visit_child_DecList_0(node);
  // post
  return res;
}
static void *visit_child_DecList_0(AST_DecList_0 *node) {
  void *res = NULL;
  res = visit_Dec(node->Dec);
  // lex node COMMA
  res = visit_DecList(node->DecList);
  return res;
}
static void *visit_DecList_1(AST_DecList_1 *node) {
  void *res = NULL;
  // pre
  res = visit_child_DecList_1(node);
  // post
  return res;
}
static void *visit_child_DecList_1(AST_DecList_1 *node) {
  void *res = NULL;
  res = visit_Dec(node->Dec);
  return res;
}
static void *visit_Dec(AST_Dec *node) {
  void *res = NULL;
  switch (node->clkind) {
  case 0:
    res = visit_Dec_Simple((AST_Dec_Simple *)node);
    break;
  case 1:
    res = visit_Dec_WithInit((AST_Dec_WithInit *)node);
    break;
  }
  return res;
}
static void *visit_Dec_Simple(AST_Dec_Simple *node) {
  void *res = NULL;
  // pre
  res = visit_child_Dec_Simple(node);
  // post
  return res;
}
static void *visit_child_Dec_Simple(AST_Dec_Simple *node) {
  vardec *vd = visit_VarDec(node->VarDec);

  if (dec_handler) {
    structdef *sd = dec_handler;
    if (structdef_queryfld(sd, vd->name)) {
      REPORT_ERR(ERR_DUPFLD);
    } else {
      structfld_def(sd, vd->name, vd->ty);
    }
  } else {
    if (var_query(vd->name)) {
      REPORT_ERR(ERR_DUPVAR);
      vd->name = ANON_NAME;
    } else {
      if (structdef_query(vd->name)) {
        REPORT_ERR(ERR_DUPVAR);
      }
    }
    var *v = var_def(vd->name, vd->ty);
    if (TY_ISPTR(v->ty)) {
      Operand vop=op_var(v);
      emit_alloc(&vop, type_size(vd->ty));
    }
  }

  return NULL;
}
static void *visit_Dec_WithInit(AST_Dec_WithInit *node) {
  void *res = NULL;
  // pre
  res = visit_child_Dec_WithInit(node);
  // post
  return res;
}

static inline type *handle_assign(ast_base *node, var *lhs, ExprInfo *ei) {
  type *rty = type_unify(lhs->ty, ei->ty);
  if (!rty) {
    REPORT_ERR(ERR_ASSTY);
    return type_getPrim(TY_ERROR);
  }
  if (TY_ISERR(rty))
    return rty;
  // emit assign ir
  Operand out=op_var(lhs);
  emit_mov_or_str(&out, &ei->op);
  return rty;
}

static void *visit_child_Dec_WithInit(AST_Dec_WithInit *node) {
  vardec *vd = visit_VarDec(node->VarDec);
  // lex node ASSIGNOP

  if (dec_handler) {
    REPORT_ERR(ERR_DUPFLD);
    structdef *sd = dec_handler;
    if (!structdef_queryfld(sd, vd->name)) {
      structfld_def(sd, vd->name, vd->ty);
    }
  } else {
    ExprInfo ei = resolve_expr(node->Exp);
    if (var_query(vd->name)) {
      REPORT_ERR(ERR_DUPVAR);
      vd->name = ANON_NAME;
    } else {
      if (structdef_query(vd->name)) {
        REPORT_ERR(ERR_DUPVAR);
      }
    }
    var *v = var_def(vd->name, vd->ty);

    if (TY_ISPTR(v->ty)) {
      Operand vop=op_var(v);
      emit_alloc(&vop, type_size(vd->ty));
    }

    handle_assign(ABASE, v, &ei);
  }
  return NULL;
}
