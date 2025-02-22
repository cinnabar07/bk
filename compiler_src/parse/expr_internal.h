#ifndef EXPRIN_H
#define EXPRIN_H
#include "../common.h"
#include "../ast/ast_structs.h"
#include "typing.h"

static struct ExprInfo visit_Exp_Assign(AST_Exp_Assign* node);
static struct ExprInfo visit_Exp_And(AST_Exp_And* node);
static struct ExprInfo visit_Exp_Or(AST_Exp_Or* node);
static struct ExprInfo visit_Exp_Rel(AST_Exp_Rel* node);
static struct ExprInfo visit_Exp_Plus(AST_Exp_Plus* node);
static struct ExprInfo visit_Exp_Minus(AST_Exp_Minus* node);
static struct ExprInfo visit_Exp_Mul(AST_Exp_Mul* node);
static struct ExprInfo visit_Exp_Div(AST_Exp_Div* node);
static struct ExprInfo visit_Exp_P(AST_Exp_P* node);
static struct ExprInfo visit_Exp_Neg(AST_Exp_Neg* node);
static struct ExprInfo visit_Exp_Not(AST_Exp_Not* node);
static struct ExprInfo visit_Exp_Call(AST_Exp_Call* node);
static struct ExprInfo visit_Exp_CallV(AST_Exp_CallV* node);
static struct ExprInfo visit_Exp_Arr(AST_Exp_Arr* node);
static struct ExprInfo visit_Exp_Fld(AST_Exp_Fld* node);
static struct ExprInfo visit_Exp_Var(AST_Exp_Var* node);
static struct ExprInfo visit_Exp_Int(AST_Exp_Int* node);
static struct ExprInfo visit_Exp_Float(AST_Exp_Float* node);
static struct ExprInfo visit_child_Exp_Assign(AST_Exp_Assign* node);
static struct ExprInfo visit_child_Exp_And(AST_Exp_And* node);
static struct ExprInfo visit_child_Exp_Or(AST_Exp_Or* node);
static struct ExprInfo visit_child_Exp_Rel(AST_Exp_Rel* node);
static struct ExprInfo visit_child_Exp_Plus(AST_Exp_Plus* node);
static struct ExprInfo visit_child_Exp_Minus(AST_Exp_Minus* node);
static struct ExprInfo visit_child_Exp_Mul(AST_Exp_Mul* node);
static struct ExprInfo visit_child_Exp_Div(AST_Exp_Div* node);
static struct ExprInfo visit_child_Exp_P(AST_Exp_P* node);
static struct ExprInfo visit_child_Exp_Neg(AST_Exp_Neg* node);
static struct ExprInfo visit_child_Exp_Not(AST_Exp_Not* node);
static struct ExprInfo visit_child_Exp_Call(AST_Exp_Call* node);
static struct ExprInfo visit_child_Exp_CallV(AST_Exp_CallV* node);
static struct ExprInfo visit_child_Exp_Arr(AST_Exp_Arr* node);
static struct ExprInfo visit_child_Exp_Fld(AST_Exp_Fld* node);
static struct ExprInfo visit_child_Exp_Var(AST_Exp_Var* node);
static struct ExprInfo visit_child_Exp_Int(AST_Exp_Int* node);
static struct ExprInfo visit_child_Exp_Float(AST_Exp_Float* node);

#endif