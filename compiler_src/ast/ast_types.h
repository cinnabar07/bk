#ifndef ASTTY_H
#define ASTTY_H
extern const char* const ATY_NAME[49];
extern const char* const ATY_INT_2NAME[1];
extern const char* const ATY_FLOAT_2NAME[1];
extern const char* const ATY_ID_2NAME[1];
extern const char* const ATY_SEMI_2NAME[1];
extern const char* const ATY_COMMA_2NAME[1];
extern const char* const ATY_ASSIGNOP_2NAME[1];
extern const char* const ATY_RELOP_2NAME[6];
extern const char* const ATY_PLUS_2NAME[1];
extern const char* const ATY_MINUS_2NAME[1];
extern const char* const ATY_STAR_2NAME[1];
extern const char* const ATY_DIV_2NAME[1];
extern const char* const ATY_AND_2NAME[1];
extern const char* const ATY_OR_2NAME[1];
extern const char* const ATY_DOT_2NAME[1];
extern const char* const ATY_NOT_2NAME[1];
extern const char* const ATY_TYPE_2NAME[2];
extern const char* const ATY_LP_2NAME[1];
extern const char* const ATY_RP_2NAME[1];
extern const char* const ATY_LB_2NAME[1];
extern const char* const ATY_RB_2NAME[1];
extern const char* const ATY_LC_2NAME[1];
extern const char* const ATY_RC_2NAME[1];
extern const char* const ATY_STRUCT_2NAME[1];
extern const char* const ATY_RETURN_2NAME[1];
extern const char* const ATY_IF_2NAME[1];
extern const char* const ATY_ELSE_2NAME[1];
extern const char* const ATY_WHILE_2NAME[1];
extern const char* const ATY_Program_2NAME[1];
extern const char* const ATY_ExtDefList_2NAME[1];
extern const char* const ATY_ExtDef_2NAME[3];
extern const char* const ATY_ExtDecList_2NAME[2];
extern const char* const ATY_Specifier_2NAME[2];
extern const char* const ATY_StructSpecifier_2NAME[2];
extern const char* const ATY_OptTag_2NAME[1];
extern const char* const ATY_Tag_2NAME[1];
extern const char* const ATY_VarDec_2NAME[2];
extern const char* const ATY_FunDec_2NAME[2];
extern const char* const ATY_VarList_2NAME[2];
extern const char* const ATY_ParamDec_2NAME[1];
extern const char* const ATY_CompSt_2NAME[1];
extern const char* const ATY_StmtList_2NAME[1];
extern const char* const ATY_Stmt_2NAME[6];
extern const char* const ATY_DefList_2NAME[1];
extern const char* const ATY_Def_2NAME[1];
extern const char* const ATY_DecList_2NAME[2];
extern const char* const ATY_Dec_2NAME[2];
extern const char* const ATY_Exp_2NAME[18];
extern const char* const ATY_Args_2NAME[2];
extern const char * const* ATY_2ND[49];

enum AST_ENUM_TY{
    ATY_nil,
    ATY_INT,
    ATY_FLOAT,
    ATY_ID,
    ATY_SEMI,
    ATY_COMMA,
    ATY_ASSIGNOP,
    ATY_RELOP,
    ATY_PLUS,
    ATY_MINUS,
    ATY_STAR,
    ATY_DIV,
    ATY_AND,
    ATY_OR,
    ATY_DOT,
    ATY_NOT,
    ATY_TYPE,
    ATY_LP,
    ATY_RP,
    ATY_LB,
    ATY_RB,
    ATY_LC,
    ATY_RC,
    ATY_STRUCT,
    ATY_RETURN,
    ATY_IF,
    ATY_ELSE,
    ATY_WHILE,
    ATY_Program,
    ATY_ExtDefList,
    ATY_ExtDef,
    ATY_ExtDecList,
    ATY_Specifier,
    ATY_StructSpecifier,
    ATY_OptTag,
    ATY_Tag,
    ATY_VarDec,
    ATY_FunDec,
    ATY_VarList,
    ATY_ParamDec,
    ATY_CompSt,
    ATY_StmtList,
    ATY_Stmt,
    ATY_DefList,
    ATY_Def,
    ATY_DecList,
    ATY_Dec,
    ATY_Exp,
    ATY_Args
};
enum AST_ENUM_RELOP_BTY{
GT,
LT,
GE,
LE,
EQ,
NE
};
enum AST_ENUM_TYPE_BTY{
INT,
FLOAT
};
enum AST_ENUM_ExtDef_BTY{
ExtDef_Var,
ExtDef_MayStruct,
ExtDef_Fn
};
enum AST_ENUM_ExtDecList_BTY{
ExtDecList_0,
ExtDecList_1
};
enum AST_ENUM_Specifier_BTY{
Specifier_Ty,
Specifier_Struct
};
enum AST_ENUM_StructSpecifier_BTY{
StructSpecifier_Ref,
StructSpecifier_Def
};
enum AST_ENUM_VarDec_BTY{
VarDec_Var,
VarDec_Array
};
enum AST_ENUM_FunDec_BTY{
FunDec_HasArg,
FunDec_NoArg
};
enum AST_ENUM_VarList_BTY{
VarList_0,
VarList_1
};
enum AST_ENUM_Stmt_BTY{
Stmt_Expr,
Stmt_Comp,
Stmt_Ret,
Stmt_If,
Stmt_Ife,
Stmt_While
};
enum AST_ENUM_DecList_BTY{
DecList_0,
DecList_1
};
enum AST_ENUM_Dec_BTY{
Dec_Simple,
Dec_WithInit
};
enum AST_ENUM_Exp_BTY{
Exp_Assign,
Exp_And,
Exp_Or,
Exp_Rel,
Exp_Plus,
Exp_Minus,
Exp_Mul,
Exp_Div,
Exp_P,
Exp_Neg,
Exp_Not,
Exp_Call,
Exp_CallV,
Exp_Arr,
Exp_Fld,
Exp_Var,
Exp_Int,
Exp_Float
};
enum AST_ENUM_Args_BTY{
Args_0,
Args_1
};
#endif