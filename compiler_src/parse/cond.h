#ifndef CONDH
#define CONDH
#include "../common.h"
#include "typing.h"
#include "../ir/bb.h"
#include "../ast/ast_structs.h"

void resolve_cond(AST_Exp* node,BB* yes,BB* no);

#endif