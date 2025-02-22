#ifndef ASTBASE_H
#define ASTBASE_H
#include "../mydefs.h"

#define ASTFLAG_ISLEX (1u<<0)
#define ASTFLAG_LEX_VAL (1u<<1) // this term node has value (i.e. literal)
#define ASTFLAG_LEXBR (1u<<2) // this term node has variants

#define AST_IS_LEX(a) ((a)->flags & ASTFLAG_ISLEX)

#define AST_HEADER     u8 kind; \
    u8 clkind; \
    u8 nr_childs; \
    u8 flags; \
    int lineno; \
    void* p
typedef struct ast_base
{
    AST_HEADER;
    struct ast_base* child[1];
} ast_base;

extern ast_base* ast_root;
static inline ast_base* ast_setroot(ast_base* rt){
    ast_root=rt;
    return rt;
}
#endif
