#include "ast_printer.h"
#include "ast_base.h"
#include "ast_structs.h"
#include "ast_types.h"
#include "stdio.h"
#include "ast_match.h"

static int ident_num;
static void prepline(){
    for(int i=0;i<ident_num;++i){
        putchar(' ');
    }
}
#define Tprintf(x,...) prepline();printf(x,__VA_ARGS__) 
static void visit_node(ast_base* nd);

static void visit_lex(ast_base* nd){
    Tprintf("%s",ATY_NAME[nd->kind]);
    MATCH(nd){
        CASE(ID) {
            TCAST(nd,ID);
            printf(": %s",node->v);
            break;
        }
        CASE(TYPE) {
            TCAST(nd,TYPE);
            printf(": %s",node->clkind==INT?"int":"float");
            break;
        }
        CASE(INT){
            TCAST(nd,INT);
            printf(": %d",node->v);
            break;
        }
        CASE(FLOAT){
            TCAST(nd,FLOAT);
            printf(": %f",node->v);
            break;
        }
    }    
    printf("\n");
}
static void visit_complex(ast_base* nd){
    Tprintf("%s (%d)\n",ATY_NAME[nd->kind],nd->lineno);
    ident_num+=2;
    // visit childs
    for(int i=0;i<nd->nr_childs;++i){
        visit_node(nd->child[i]);
    }
    ident_num-=2;
}
static void visit_node(ast_base* nd){
    if(!nd) return;
    if(AST_IS_LEX(nd)){
        visit_lex(nd);
    }else{
        visit_complex(nd);
    }
}
void print_ast(){
    visit_node(ast_root);   
}