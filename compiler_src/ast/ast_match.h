#ifndef ASTMATCH_H
#define ASTMATCH_H
#include "ast_structs.h"
#include "ast_types.h"
#include "../common.h"

#define MATCH(x) switch((x)->kind)
#define CASE(ty) case CONCAT(ATY_,ty):
#define TCAST(x,ty) CONCAT(AST_,ty)* node=(CONCAT(AST_,ty)*)(x)
#define TIS(x,ty) ((x)->kind == CONCAT(ATY_,ty))

#endif