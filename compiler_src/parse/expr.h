#ifndef EXPRH
#define EXPRH
#include "../common.h"
#include "typing.h"
#include "../ir/bb.h"
#include "../ast/ast_structs.h"

ExprInfo resolve_expr(AST_Exp* node);
ExprInfo visit_Exp(AST_Exp *node);

#endif