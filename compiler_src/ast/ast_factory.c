#include "../common.h"
#include "ast_factory.h"
#include "ast_structs.h"
ast_base* new_ast_INT(int l,int v){
            AST_INT* res=(AST_INT*)palloc(sizeof(AST_INT));
            res->p=NULL;
            res->lineno=l;
            res->nr_childs=0;
            res->clkind=0;
            res->kind=1;
            res->v=v;
            res->flags=ASTFLAG_ISLEX|ASTFLAG_LEX_VAL;
            return (ast_base*)res; 
            }
ast_base* new_ast_FLOAT(int l,float v){
            AST_FLOAT* res=(AST_FLOAT*)palloc(sizeof(AST_FLOAT));
            res->p=NULL;
            res->lineno=l;
            res->nr_childs=0;
            res->clkind=0;
            res->kind=2;
            res->v=v;
            res->flags=ASTFLAG_ISLEX|ASTFLAG_LEX_VAL;
            return (ast_base*)res; 
            }
ast_base* new_ast_ID(int l,char* v){
            AST_ID* res=(AST_ID*)palloc(sizeof(AST_ID));
            res->p=NULL;
            res->lineno=l;
            res->nr_childs=0;
            res->clkind=0;
            res->kind=3;
            res->v=v;
            res->flags=ASTFLAG_ISLEX|ASTFLAG_LEX_VAL;
            return (ast_base*)res; 
            }
ast_base* new_ast_SEMI(int l){
                AST_SEMI* res=(AST_SEMI*)palloc(sizeof(AST_SEMI));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=4;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_COMMA(int l){
                AST_COMMA* res=(AST_COMMA*)palloc(sizeof(AST_COMMA));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=5;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_ASSIGNOP(int l){
                AST_ASSIGNOP* res=(AST_ASSIGNOP*)palloc(sizeof(AST_ASSIGNOP));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=6;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_RELOP_GT(int l){
                AST_RELOP* res=(AST_RELOP*)palloc(sizeof(AST_RELOP));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=7;
                res->flags=ASTFLAG_ISLEX|ASTFLAG_LEXBR;
                return (ast_base*)res; 
                }
ast_base* new_ast_RELOP_LT(int l){
                AST_RELOP* res=(AST_RELOP*)palloc(sizeof(AST_RELOP));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=1;
                res->kind=7;
                res->flags=ASTFLAG_ISLEX|ASTFLAG_LEXBR;
                return (ast_base*)res; 
                }
ast_base* new_ast_RELOP_GE(int l){
                AST_RELOP* res=(AST_RELOP*)palloc(sizeof(AST_RELOP));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=2;
                res->kind=7;
                res->flags=ASTFLAG_ISLEX|ASTFLAG_LEXBR;
                return (ast_base*)res; 
                }
ast_base* new_ast_RELOP_LE(int l){
                AST_RELOP* res=(AST_RELOP*)palloc(sizeof(AST_RELOP));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=3;
                res->kind=7;
                res->flags=ASTFLAG_ISLEX|ASTFLAG_LEXBR;
                return (ast_base*)res; 
                }
ast_base* new_ast_RELOP_EQ(int l){
                AST_RELOP* res=(AST_RELOP*)palloc(sizeof(AST_RELOP));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=4;
                res->kind=7;
                res->flags=ASTFLAG_ISLEX|ASTFLAG_LEXBR;
                return (ast_base*)res; 
                }
ast_base* new_ast_RELOP_NE(int l){
                AST_RELOP* res=(AST_RELOP*)palloc(sizeof(AST_RELOP));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=5;
                res->kind=7;
                res->flags=ASTFLAG_ISLEX|ASTFLAG_LEXBR;
                return (ast_base*)res; 
                }
ast_base* new_ast_PLUS(int l){
                AST_PLUS* res=(AST_PLUS*)palloc(sizeof(AST_PLUS));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=8;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_MINUS(int l){
                AST_MINUS* res=(AST_MINUS*)palloc(sizeof(AST_MINUS));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=9;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_STAR(int l){
                AST_STAR* res=(AST_STAR*)palloc(sizeof(AST_STAR));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=10;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_DIV(int l){
                AST_DIV* res=(AST_DIV*)palloc(sizeof(AST_DIV));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=11;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_AND(int l){
                AST_AND* res=(AST_AND*)palloc(sizeof(AST_AND));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=12;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_OR(int l){
                AST_OR* res=(AST_OR*)palloc(sizeof(AST_OR));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=13;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_DOT(int l){
                AST_DOT* res=(AST_DOT*)palloc(sizeof(AST_DOT));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=14;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_NOT(int l){
                AST_NOT* res=(AST_NOT*)palloc(sizeof(AST_NOT));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=15;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_TYPE_INT(int l){
                AST_TYPE* res=(AST_TYPE*)palloc(sizeof(AST_TYPE));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=16;
                res->flags=ASTFLAG_ISLEX|ASTFLAG_LEXBR;
                return (ast_base*)res; 
                }
ast_base* new_ast_TYPE_FLOAT(int l){
                AST_TYPE* res=(AST_TYPE*)palloc(sizeof(AST_TYPE));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=1;
                res->kind=16;
                res->flags=ASTFLAG_ISLEX|ASTFLAG_LEXBR;
                return (ast_base*)res; 
                }
ast_base* new_ast_LP(int l){
                AST_LP* res=(AST_LP*)palloc(sizeof(AST_LP));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=17;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_RP(int l){
                AST_RP* res=(AST_RP*)palloc(sizeof(AST_RP));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=18;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_LB(int l){
                AST_LB* res=(AST_LB*)palloc(sizeof(AST_LB));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=19;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_RB(int l){
                AST_RB* res=(AST_RB*)palloc(sizeof(AST_RB));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=20;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_LC(int l){
                AST_LC* res=(AST_LC*)palloc(sizeof(AST_LC));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=21;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_RC(int l){
                AST_RC* res=(AST_RC*)palloc(sizeof(AST_RC));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=22;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_STRUCT(int l){
                AST_STRUCT* res=(AST_STRUCT*)palloc(sizeof(AST_STRUCT));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=23;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_RETURN(int l){
                AST_RETURN* res=(AST_RETURN*)palloc(sizeof(AST_RETURN));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=24;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_IF(int l){
                AST_IF* res=(AST_IF*)palloc(sizeof(AST_IF));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=25;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_ELSE(int l){
                AST_ELSE* res=(AST_ELSE*)palloc(sizeof(AST_ELSE));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=26;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_WHILE(int l){
                AST_WHILE* res=(AST_WHILE*)palloc(sizeof(AST_WHILE));
                res->p=NULL;
                res->lineno=l;
                res->nr_childs=0;
                res->clkind=0;
                res->kind=27;
                res->flags=ASTFLAG_ISLEX;
                return (ast_base*)res; 
                }
ast_base* new_ast_Program(int l,ast_base* ExtDefList){
AST_Program* res=(AST_Program*)palloc(sizeof(AST_Program));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=0;
                    res->kind=28;
                    res->flags=0;
                    res->ExtDefList = (AST_ExtDefList*)ExtDefList;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_ExtDefList(int l,ast_base* ExtDef,ast_base* ExtDefList){
AST_ExtDefList* res=(AST_ExtDefList*)palloc(sizeof(AST_ExtDefList));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=2;
                    res->clkind=0;
                    res->kind=29;
                    res->flags=0;
                    res->ExtDef = (AST_ExtDef*)ExtDef;
res->ExtDefList = (AST_ExtDefList*)ExtDefList;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_ExtDef_Var(int l,ast_base* Specifier,ast_base* ExtDecList,ast_base* SEMI){
AST_ExtDef_Var* res=(AST_ExtDef_Var*)palloc(sizeof(AST_ExtDef_Var));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=0;
                    res->kind=30;
                    res->flags=0;
                    res->Specifier = (AST_Specifier*)Specifier;
res->ExtDecList = (AST_ExtDecList*)ExtDecList;
res->SEMI = (AST_SEMI*)SEMI;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_ExtDef_MayStruct(int l,ast_base* Specifier,ast_base* SEMI){
AST_ExtDef_MayStruct* res=(AST_ExtDef_MayStruct*)palloc(sizeof(AST_ExtDef_MayStruct));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=2;
                    res->clkind=1;
                    res->kind=30;
                    res->flags=0;
                    res->Specifier = (AST_Specifier*)Specifier;
res->SEMI = (AST_SEMI*)SEMI;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_ExtDef_Fn(int l,ast_base* Specifier,ast_base* FunDec,ast_base* CompSt){
AST_ExtDef_Fn* res=(AST_ExtDef_Fn*)palloc(sizeof(AST_ExtDef_Fn));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=2;
                    res->kind=30;
                    res->flags=0;
                    res->Specifier = (AST_Specifier*)Specifier;
res->FunDec = (AST_FunDec*)FunDec;
res->CompSt = (AST_CompSt*)CompSt;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_ExtDecList_0(int l,ast_base* VarDec,ast_base* COMMA,ast_base* ExtDecList){
AST_ExtDecList_0* res=(AST_ExtDecList_0*)palloc(sizeof(AST_ExtDecList_0));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=0;
                    res->kind=31;
                    res->flags=0;
                    res->VarDec = (AST_VarDec*)VarDec;
res->COMMA = (AST_COMMA*)COMMA;
res->ExtDecList = (AST_ExtDecList*)ExtDecList;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_ExtDecList_1(int l,ast_base* VarDec){
AST_ExtDecList_1* res=(AST_ExtDecList_1*)palloc(sizeof(AST_ExtDecList_1));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=1;
                    res->kind=31;
                    res->flags=0;
                    res->VarDec = (AST_VarDec*)VarDec;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Specifier_Ty(int l,ast_base* TYPE){
AST_Specifier_Ty* res=(AST_Specifier_Ty*)palloc(sizeof(AST_Specifier_Ty));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=0;
                    res->kind=32;
                    res->flags=0;
                    res->TYPE = (AST_TYPE*)TYPE;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Specifier_Struct(int l,ast_base* StructSpecifier){
AST_Specifier_Struct* res=(AST_Specifier_Struct*)palloc(sizeof(AST_Specifier_Struct));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=1;
                    res->kind=32;
                    res->flags=0;
                    res->StructSpecifier = (AST_StructSpecifier*)StructSpecifier;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_StructSpecifier_Ref(int l,ast_base* STRUCT,ast_base* Tag){
AST_StructSpecifier_Ref* res=(AST_StructSpecifier_Ref*)palloc(sizeof(AST_StructSpecifier_Ref));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=2;
                    res->clkind=0;
                    res->kind=33;
                    res->flags=0;
                    res->STRUCT = (AST_STRUCT*)STRUCT;
res->Tag = (AST_Tag*)Tag;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_StructSpecifier_Def(int l,ast_base* STRUCT,ast_base* OptTag,ast_base* LC,ast_base* DefList,ast_base* RC){
AST_StructSpecifier_Def* res=(AST_StructSpecifier_Def*)palloc(sizeof(AST_StructSpecifier_Def));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=5;
                    res->clkind=1;
                    res->kind=33;
                    res->flags=0;
                    res->STRUCT = (AST_STRUCT*)STRUCT;
res->OptTag = (AST_OptTag*)OptTag;
res->LC = (AST_LC*)LC;
res->DefList = (AST_DefList*)DefList;
res->RC = (AST_RC*)RC;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_OptTag(int l,ast_base* ID){
AST_OptTag* res=(AST_OptTag*)palloc(sizeof(AST_OptTag));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=0;
                    res->kind=34;
                    res->flags=0;
                    res->ID = (AST_ID*)ID;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Tag(int l,ast_base* ID){
AST_Tag* res=(AST_Tag*)palloc(sizeof(AST_Tag));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=0;
                    res->kind=35;
                    res->flags=0;
                    res->ID = (AST_ID*)ID;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_VarDec_Var(int l,ast_base* ID){
AST_VarDec_Var* res=(AST_VarDec_Var*)palloc(sizeof(AST_VarDec_Var));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=0;
                    res->kind=36;
                    res->flags=0;
                    res->ID = (AST_ID*)ID;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_VarDec_Array(int l,ast_base* VarDec,ast_base* LB,ast_base* INT,ast_base* RB){
AST_VarDec_Array* res=(AST_VarDec_Array*)palloc(sizeof(AST_VarDec_Array));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=4;
                    res->clkind=1;
                    res->kind=36;
                    res->flags=0;
                    res->VarDec = (AST_VarDec*)VarDec;
res->LB = (AST_LB*)LB;
res->INT = (AST_INT*)INT;
res->RB = (AST_RB*)RB;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_FunDec_HasArg(int l,ast_base* ID,ast_base* LP,ast_base* VarList,ast_base* RP){
AST_FunDec_HasArg* res=(AST_FunDec_HasArg*)palloc(sizeof(AST_FunDec_HasArg));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=4;
                    res->clkind=0;
                    res->kind=37;
                    res->flags=0;
                    res->ID = (AST_ID*)ID;
res->LP = (AST_LP*)LP;
res->VarList = (AST_VarList*)VarList;
res->RP = (AST_RP*)RP;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_FunDec_NoArg(int l,ast_base* ID,ast_base* LP,ast_base* RP){
AST_FunDec_NoArg* res=(AST_FunDec_NoArg*)palloc(sizeof(AST_FunDec_NoArg));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=1;
                    res->kind=37;
                    res->flags=0;
                    res->ID = (AST_ID*)ID;
res->LP = (AST_LP*)LP;
res->RP = (AST_RP*)RP;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_VarList_0(int l,ast_base* ParamDec,ast_base* COMMA,ast_base* VarList){
AST_VarList_0* res=(AST_VarList_0*)palloc(sizeof(AST_VarList_0));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=0;
                    res->kind=38;
                    res->flags=0;
                    res->ParamDec = (AST_ParamDec*)ParamDec;
res->COMMA = (AST_COMMA*)COMMA;
res->VarList = (AST_VarList*)VarList;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_VarList_1(int l,ast_base* ParamDec){
AST_VarList_1* res=(AST_VarList_1*)palloc(sizeof(AST_VarList_1));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=1;
                    res->kind=38;
                    res->flags=0;
                    res->ParamDec = (AST_ParamDec*)ParamDec;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_ParamDec(int l,ast_base* Specifier,ast_base* VarDec){
AST_ParamDec* res=(AST_ParamDec*)palloc(sizeof(AST_ParamDec));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=2;
                    res->clkind=0;
                    res->kind=39;
                    res->flags=0;
                    res->Specifier = (AST_Specifier*)Specifier;
res->VarDec = (AST_VarDec*)VarDec;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_CompSt(int l,ast_base* LC,ast_base* DefList,ast_base* StmtList,ast_base* RC){
AST_CompSt* res=(AST_CompSt*)palloc(sizeof(AST_CompSt));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=4;
                    res->clkind=0;
                    res->kind=40;
                    res->flags=0;
                    res->LC = (AST_LC*)LC;
res->DefList = (AST_DefList*)DefList;
res->StmtList = (AST_StmtList*)StmtList;
res->RC = (AST_RC*)RC;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_StmtList(int l,ast_base* Stmt,ast_base* StmtList){
AST_StmtList* res=(AST_StmtList*)palloc(sizeof(AST_StmtList));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=2;
                    res->clkind=0;
                    res->kind=41;
                    res->flags=0;
                    res->Stmt = (AST_Stmt*)Stmt;
res->StmtList = (AST_StmtList*)StmtList;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Stmt_Expr(int l,ast_base* Exp,ast_base* SEMI){
AST_Stmt_Expr* res=(AST_Stmt_Expr*)palloc(sizeof(AST_Stmt_Expr));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=2;
                    res->clkind=0;
                    res->kind=42;
                    res->flags=0;
                    res->Exp = (AST_Exp*)Exp;
res->SEMI = (AST_SEMI*)SEMI;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Stmt_Comp(int l,ast_base* CompSt){
AST_Stmt_Comp* res=(AST_Stmt_Comp*)palloc(sizeof(AST_Stmt_Comp));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=1;
                    res->kind=42;
                    res->flags=0;
                    res->CompSt = (AST_CompSt*)CompSt;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Stmt_Ret(int l,ast_base* RETURN,ast_base* Exp,ast_base* SEMI){
AST_Stmt_Ret* res=(AST_Stmt_Ret*)palloc(sizeof(AST_Stmt_Ret));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=2;
                    res->kind=42;
                    res->flags=0;
                    res->RETURN = (AST_RETURN*)RETURN;
res->Exp = (AST_Exp*)Exp;
res->SEMI = (AST_SEMI*)SEMI;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Stmt_If(int l,ast_base* IF,ast_base* LP,ast_base* Exp,ast_base* RP,ast_base* Stmt){
AST_Stmt_If* res=(AST_Stmt_If*)palloc(sizeof(AST_Stmt_If));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=5;
                    res->clkind=3;
                    res->kind=42;
                    res->flags=0;
                    res->IF = (AST_IF*)IF;
res->LP = (AST_LP*)LP;
res->Exp = (AST_Exp*)Exp;
res->RP = (AST_RP*)RP;
res->Stmt = (AST_Stmt*)Stmt;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Stmt_Ife(int l,ast_base* IF,ast_base* LP,ast_base* Exp,ast_base* RP,ast_base* Stmt,ast_base* ELSE,ast_base* Stmt1){
AST_Stmt_Ife* res=(AST_Stmt_Ife*)palloc(sizeof(AST_Stmt_Ife));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=7;
                    res->clkind=4;
                    res->kind=42;
                    res->flags=0;
                    res->IF = (AST_IF*)IF;
res->LP = (AST_LP*)LP;
res->Exp = (AST_Exp*)Exp;
res->RP = (AST_RP*)RP;
res->Stmt = (AST_Stmt*)Stmt;
res->ELSE = (AST_ELSE*)ELSE;
res->Stmt1 = (AST_Stmt*)Stmt1;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Stmt_While(int l,ast_base* WHILE,ast_base* LP,ast_base* Exp,ast_base* RP,ast_base* Stmt){
AST_Stmt_While* res=(AST_Stmt_While*)palloc(sizeof(AST_Stmt_While));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=5;
                    res->clkind=5;
                    res->kind=42;
                    res->flags=0;
                    res->WHILE = (AST_WHILE*)WHILE;
res->LP = (AST_LP*)LP;
res->Exp = (AST_Exp*)Exp;
res->RP = (AST_RP*)RP;
res->Stmt = (AST_Stmt*)Stmt;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_DefList(int l,ast_base* Def,ast_base* DefList){
AST_DefList* res=(AST_DefList*)palloc(sizeof(AST_DefList));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=2;
                    res->clkind=0;
                    res->kind=43;
                    res->flags=0;
                    res->Def = (AST_Def*)Def;
res->DefList = (AST_DefList*)DefList;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Def(int l,ast_base* Specifier,ast_base* DecList,ast_base* SEMI){
AST_Def* res=(AST_Def*)palloc(sizeof(AST_Def));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=0;
                    res->kind=44;
                    res->flags=0;
                    res->Specifier = (AST_Specifier*)Specifier;
res->DecList = (AST_DecList*)DecList;
res->SEMI = (AST_SEMI*)SEMI;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_DecList_0(int l,ast_base* Dec,ast_base* COMMA,ast_base* DecList){
AST_DecList_0* res=(AST_DecList_0*)palloc(sizeof(AST_DecList_0));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=0;
                    res->kind=45;
                    res->flags=0;
                    res->Dec = (AST_Dec*)Dec;
res->COMMA = (AST_COMMA*)COMMA;
res->DecList = (AST_DecList*)DecList;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_DecList_1(int l,ast_base* Dec){
AST_DecList_1* res=(AST_DecList_1*)palloc(sizeof(AST_DecList_1));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=1;
                    res->kind=45;
                    res->flags=0;
                    res->Dec = (AST_Dec*)Dec;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Dec_Simple(int l,ast_base* VarDec){
AST_Dec_Simple* res=(AST_Dec_Simple*)palloc(sizeof(AST_Dec_Simple));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=0;
                    res->kind=46;
                    res->flags=0;
                    res->VarDec = (AST_VarDec*)VarDec;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Dec_WithInit(int l,ast_base* VarDec,ast_base* ASSIGNOP,ast_base* Exp){
AST_Dec_WithInit* res=(AST_Dec_WithInit*)palloc(sizeof(AST_Dec_WithInit));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=1;
                    res->kind=46;
                    res->flags=0;
                    res->VarDec = (AST_VarDec*)VarDec;
res->ASSIGNOP = (AST_ASSIGNOP*)ASSIGNOP;
res->Exp = (AST_Exp*)Exp;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Assign(int l,ast_base* Exp,ast_base* ASSIGNOP,ast_base* Exp1){
AST_Exp_Assign* res=(AST_Exp_Assign*)palloc(sizeof(AST_Exp_Assign));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=0;
                    res->kind=47;
                    res->flags=0;
                    res->Exp = (AST_Exp*)Exp;
res->ASSIGNOP = (AST_ASSIGNOP*)ASSIGNOP;
res->Exp1 = (AST_Exp*)Exp1;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_And(int l,ast_base* Exp,ast_base* AND,ast_base* Exp1){
AST_Exp_And* res=(AST_Exp_And*)palloc(sizeof(AST_Exp_And));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=1;
                    res->kind=47;
                    res->flags=0;
                    res->Exp = (AST_Exp*)Exp;
res->AND = (AST_AND*)AND;
res->Exp1 = (AST_Exp*)Exp1;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Or(int l,ast_base* Exp,ast_base* OR,ast_base* Exp1){
AST_Exp_Or* res=(AST_Exp_Or*)palloc(sizeof(AST_Exp_Or));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=2;
                    res->kind=47;
                    res->flags=0;
                    res->Exp = (AST_Exp*)Exp;
res->OR = (AST_OR*)OR;
res->Exp1 = (AST_Exp*)Exp1;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Rel(int l,ast_base* Exp,ast_base* RELOP,ast_base* Exp1){
AST_Exp_Rel* res=(AST_Exp_Rel*)palloc(sizeof(AST_Exp_Rel));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=3;
                    res->kind=47;
                    res->flags=0;
                    res->Exp = (AST_Exp*)Exp;
res->RELOP = (AST_RELOP*)RELOP;
res->Exp1 = (AST_Exp*)Exp1;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Plus(int l,ast_base* Exp,ast_base* PLUS,ast_base* Exp1){
AST_Exp_Plus* res=(AST_Exp_Plus*)palloc(sizeof(AST_Exp_Plus));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=4;
                    res->kind=47;
                    res->flags=0;
                    res->Exp = (AST_Exp*)Exp;
res->PLUS = (AST_PLUS*)PLUS;
res->Exp1 = (AST_Exp*)Exp1;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Minus(int l,ast_base* Exp,ast_base* MINUS,ast_base* Exp1){
AST_Exp_Minus* res=(AST_Exp_Minus*)palloc(sizeof(AST_Exp_Minus));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=5;
                    res->kind=47;
                    res->flags=0;
                    res->Exp = (AST_Exp*)Exp;
res->MINUS = (AST_MINUS*)MINUS;
res->Exp1 = (AST_Exp*)Exp1;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Mul(int l,ast_base* Exp,ast_base* STAR,ast_base* Exp1){
AST_Exp_Mul* res=(AST_Exp_Mul*)palloc(sizeof(AST_Exp_Mul));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=6;
                    res->kind=47;
                    res->flags=0;
                    res->Exp = (AST_Exp*)Exp;
res->STAR = (AST_STAR*)STAR;
res->Exp1 = (AST_Exp*)Exp1;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Div(int l,ast_base* Exp,ast_base* DIV,ast_base* Exp1){
AST_Exp_Div* res=(AST_Exp_Div*)palloc(sizeof(AST_Exp_Div));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=7;
                    res->kind=47;
                    res->flags=0;
                    res->Exp = (AST_Exp*)Exp;
res->DIV = (AST_DIV*)DIV;
res->Exp1 = (AST_Exp*)Exp1;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_P(int l,ast_base* LP,ast_base* Exp,ast_base* RP){
AST_Exp_P* res=(AST_Exp_P*)palloc(sizeof(AST_Exp_P));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=8;
                    res->kind=47;
                    res->flags=0;
                    res->LP = (AST_LP*)LP;
res->Exp = (AST_Exp*)Exp;
res->RP = (AST_RP*)RP;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Neg(int l,ast_base* MINUS,ast_base* Exp){
AST_Exp_Neg* res=(AST_Exp_Neg*)palloc(sizeof(AST_Exp_Neg));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=2;
                    res->clkind=9;
                    res->kind=47;
                    res->flags=0;
                    res->MINUS = (AST_MINUS*)MINUS;
res->Exp = (AST_Exp*)Exp;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Not(int l,ast_base* NOT,ast_base* Exp){
AST_Exp_Not* res=(AST_Exp_Not*)palloc(sizeof(AST_Exp_Not));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=2;
                    res->clkind=10;
                    res->kind=47;
                    res->flags=0;
                    res->NOT = (AST_NOT*)NOT;
res->Exp = (AST_Exp*)Exp;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Call(int l,ast_base* ID,ast_base* LP,ast_base* Args,ast_base* RP){
AST_Exp_Call* res=(AST_Exp_Call*)palloc(sizeof(AST_Exp_Call));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=4;
                    res->clkind=11;
                    res->kind=47;
                    res->flags=0;
                    res->ID = (AST_ID*)ID;
res->LP = (AST_LP*)LP;
res->Args = (AST_Args*)Args;
res->RP = (AST_RP*)RP;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_CallV(int l,ast_base* ID,ast_base* LP,ast_base* RP){
AST_Exp_CallV* res=(AST_Exp_CallV*)palloc(sizeof(AST_Exp_CallV));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=12;
                    res->kind=47;
                    res->flags=0;
                    res->ID = (AST_ID*)ID;
res->LP = (AST_LP*)LP;
res->RP = (AST_RP*)RP;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Arr(int l,ast_base* Exp,ast_base* LB,ast_base* Exp1,ast_base* RB){
AST_Exp_Arr* res=(AST_Exp_Arr*)palloc(sizeof(AST_Exp_Arr));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=4;
                    res->clkind=13;
                    res->kind=47;
                    res->flags=0;
                    res->Exp = (AST_Exp*)Exp;
res->LB = (AST_LB*)LB;
res->Exp1 = (AST_Exp*)Exp1;
res->RB = (AST_RB*)RB;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Fld(int l,ast_base* Exp,ast_base* DOT,ast_base* ID){
AST_Exp_Fld* res=(AST_Exp_Fld*)palloc(sizeof(AST_Exp_Fld));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=14;
                    res->kind=47;
                    res->flags=0;
                    res->Exp = (AST_Exp*)Exp;
res->DOT = (AST_DOT*)DOT;
res->ID = (AST_ID*)ID;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Var(int l,ast_base* ID){
AST_Exp_Var* res=(AST_Exp_Var*)palloc(sizeof(AST_Exp_Var));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=15;
                    res->kind=47;
                    res->flags=0;
                    res->ID = (AST_ID*)ID;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Int(int l,ast_base* INT){
AST_Exp_Int* res=(AST_Exp_Int*)palloc(sizeof(AST_Exp_Int));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=16;
                    res->kind=47;
                    res->flags=0;
                    res->INT = (AST_INT*)INT;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Exp_Float(int l,ast_base* FLOAT){
AST_Exp_Float* res=(AST_Exp_Float*)palloc(sizeof(AST_Exp_Float));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=17;
                    res->kind=47;
                    res->flags=0;
                    res->FLOAT = (AST_FLOAT*)FLOAT;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Args_0(int l,ast_base* Exp,ast_base* COMMA,ast_base* Args){
AST_Args_0* res=(AST_Args_0*)palloc(sizeof(AST_Args_0));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=3;
                    res->clkind=0;
                    res->kind=48;
                    res->flags=0;
                    res->Exp = (AST_Exp*)Exp;
res->COMMA = (AST_COMMA*)COMMA;
res->Args = (AST_Args*)Args;
                    return (ast_base*)res; 
                    }
ast_base* new_ast_Args_1(int l,ast_base* Exp){
AST_Args_1* res=(AST_Args_1*)palloc(sizeof(AST_Args_1));
                    res->p=NULL;
                    res->lineno=l;
                    res->nr_childs=1;
                    res->clkind=1;
                    res->kind=48;
                    res->flags=0;
                    res->Exp = (AST_Exp*)Exp;
                    return (ast_base*)res; 
                    }
