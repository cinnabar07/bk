#ifndef ASTSTRUCT_H
#define ASTSTRUCT_H
#include "ast_base.h"

typedef struct AST_INT {
    AST_HEADER;
    int v;
} AST_INT;

typedef struct AST_FLOAT {
    AST_HEADER;
    float v;
} AST_FLOAT;

typedef struct AST_ID {
    AST_HEADER;
    char* v;
} AST_ID;

typedef struct AST_SEMI {
    AST_HEADER;
} AST_SEMI;

typedef struct AST_COMMA {
    AST_HEADER;
} AST_COMMA;

typedef struct AST_ASSIGNOP {
    AST_HEADER;
} AST_ASSIGNOP;

typedef struct AST_RELOP {
    AST_HEADER;
} AST_RELOP;

typedef struct AST_PLUS {
    AST_HEADER;
} AST_PLUS;

typedef struct AST_MINUS {
    AST_HEADER;
} AST_MINUS;

typedef struct AST_STAR {
    AST_HEADER;
} AST_STAR;

typedef struct AST_DIV {
    AST_HEADER;
} AST_DIV;

typedef struct AST_AND {
    AST_HEADER;
} AST_AND;

typedef struct AST_OR {
    AST_HEADER;
} AST_OR;

typedef struct AST_DOT {
    AST_HEADER;
} AST_DOT;

typedef struct AST_NOT {
    AST_HEADER;
} AST_NOT;

typedef struct AST_TYPE {
    AST_HEADER;
} AST_TYPE;

typedef struct AST_LP {
    AST_HEADER;
} AST_LP;

typedef struct AST_RP {
    AST_HEADER;
} AST_RP;

typedef struct AST_LB {
    AST_HEADER;
} AST_LB;

typedef struct AST_RB {
    AST_HEADER;
} AST_RB;

typedef struct AST_LC {
    AST_HEADER;
} AST_LC;

typedef struct AST_RC {
    AST_HEADER;
} AST_RC;

typedef struct AST_STRUCT {
    AST_HEADER;
} AST_STRUCT;

typedef struct AST_RETURN {
    AST_HEADER;
} AST_RETURN;

typedef struct AST_IF {
    AST_HEADER;
} AST_IF;

typedef struct AST_ELSE {
    AST_HEADER;
} AST_ELSE;

typedef struct AST_WHILE {
    AST_HEADER;
} AST_WHILE;

typedef struct AST_ExtDef {
    AST_HEADER;
    union{
        ast_base* child[1]; // child number is unk
        struct { struct AST_Specifier* Specifier;
struct AST_ExtDecList* ExtDecList;
struct AST_SEMI* SEMI;
 } bVar;
        struct { struct AST_Specifier* Specifier;
struct AST_SEMI* SEMI;
 } bMayStruct;
        struct { struct AST_Specifier* Specifier;
struct AST_FunDec* FunDec;
struct AST_CompSt* CompSt;
 } bFn;
    };
} AST_ExtDef;

typedef struct AST_ExtDecList {
    AST_HEADER;
    union{
        ast_base* child[1]; // child number is unk
        struct { struct AST_VarDec* VarDec;
struct AST_COMMA* COMMA;
struct AST_ExtDecList* ExtDecList;
 } b0;
        struct { struct AST_VarDec* VarDec;
 } b1;
    };
} AST_ExtDecList;

typedef struct AST_Specifier {
    AST_HEADER;
    union{
        ast_base* child[1]; // child number is unk
        struct { struct AST_TYPE* TYPE;
 } bTy;
        struct { struct AST_StructSpecifier* StructSpecifier;
 } bStruct;
    };
} AST_Specifier;

typedef struct AST_StructSpecifier {
    AST_HEADER;
    union{
        ast_base* child[1]; // child number is unk
        struct { struct AST_STRUCT* STRUCT;
struct AST_Tag* Tag;
 } bRef;
        struct { struct AST_STRUCT* STRUCT;
 /* may null */ 
struct AST_OptTag* OptTag;
struct AST_LC* LC;
 /* may null */ 
struct AST_DefList* DefList;
struct AST_RC* RC;
 } bDef;
    };
} AST_StructSpecifier;

typedef struct AST_VarDec {
    AST_HEADER;
    union{
        ast_base* child[1]; // child number is unk
        struct { struct AST_ID* ID;
 } bVar;
        struct { struct AST_VarDec* VarDec;
struct AST_LB* LB;
struct AST_INT* INT;
struct AST_RB* RB;
 } bArray;
    };
} AST_VarDec;

typedef struct AST_FunDec {
    AST_HEADER;
    union{
        ast_base* child[1]; // child number is unk
        struct { struct AST_ID* ID;
struct AST_LP* LP;
struct AST_VarList* VarList;
struct AST_RP* RP;
 } bHasArg;
        struct { struct AST_ID* ID;
struct AST_LP* LP;
struct AST_RP* RP;
 } bNoArg;
    };
} AST_FunDec;

typedef struct AST_VarList {
    AST_HEADER;
    union{
        ast_base* child[1]; // child number is unk
        struct { struct AST_ParamDec* ParamDec;
struct AST_COMMA* COMMA;
struct AST_VarList* VarList;
 } b0;
        struct { struct AST_ParamDec* ParamDec;
 } b1;
    };
} AST_VarList;

typedef struct AST_Stmt {
    AST_HEADER;
    union{
        ast_base* child[1]; // child number is unk
        struct { struct AST_Exp* Exp;
struct AST_SEMI* SEMI;
 } bExpr;
        struct { struct AST_CompSt* CompSt;
 } bComp;
        struct { struct AST_RETURN* RETURN;
struct AST_Exp* Exp;
struct AST_SEMI* SEMI;
 } bRet;
        struct { struct AST_IF* IF;
struct AST_LP* LP;
struct AST_Exp* Exp;
struct AST_RP* RP;
struct AST_Stmt* Stmt;
 } bIf;
        struct { struct AST_IF* IF;
struct AST_LP* LP;
struct AST_Exp* Exp;
struct AST_RP* RP;
struct AST_Stmt* Stmt;
struct AST_ELSE* ELSE;
struct AST_Stmt* Stmt1;
 } bIfe;
        struct { struct AST_WHILE* WHILE;
struct AST_LP* LP;
struct AST_Exp* Exp;
struct AST_RP* RP;
struct AST_Stmt* Stmt;
 } bWhile;
    };
} AST_Stmt;

typedef struct AST_DecList {
    AST_HEADER;
    union{
        ast_base* child[1]; // child number is unk
        struct { struct AST_Dec* Dec;
struct AST_COMMA* COMMA;
struct AST_DecList* DecList;
 } b0;
        struct { struct AST_Dec* Dec;
 } b1;
    };
} AST_DecList;

typedef struct AST_Dec {
    AST_HEADER;
    union{
        ast_base* child[1]; // child number is unk
        struct { struct AST_VarDec* VarDec;
 } bSimple;
        struct { struct AST_VarDec* VarDec;
struct AST_ASSIGNOP* ASSIGNOP;
struct AST_Exp* Exp;
 } bWithInit;
    };
} AST_Dec;

typedef struct AST_Exp {
    AST_HEADER;
    union{
        ast_base* child[1]; // child number is unk
        struct { struct AST_Exp* Exp;
struct AST_ASSIGNOP* ASSIGNOP;
struct AST_Exp* Exp1;
 } bAssign;
        struct { struct AST_Exp* Exp;
struct AST_AND* AND;
struct AST_Exp* Exp1;
 } bAnd;
        struct { struct AST_Exp* Exp;
struct AST_OR* OR;
struct AST_Exp* Exp1;
 } bOr;
        struct { struct AST_Exp* Exp;
struct AST_RELOP* RELOP;
struct AST_Exp* Exp1;
 } bRel;
        struct { struct AST_Exp* Exp;
struct AST_PLUS* PLUS;
struct AST_Exp* Exp1;
 } bPlus;
        struct { struct AST_Exp* Exp;
struct AST_MINUS* MINUS;
struct AST_Exp* Exp1;
 } bMinus;
        struct { struct AST_Exp* Exp;
struct AST_STAR* STAR;
struct AST_Exp* Exp1;
 } bMul;
        struct { struct AST_Exp* Exp;
struct AST_DIV* DIV;
struct AST_Exp* Exp1;
 } bDiv;
        struct { struct AST_LP* LP;
struct AST_Exp* Exp;
struct AST_RP* RP;
 } bP;
        struct { struct AST_MINUS* MINUS;
struct AST_Exp* Exp;
 } bNeg;
        struct { struct AST_NOT* NOT;
struct AST_Exp* Exp;
 } bNot;
        struct { struct AST_ID* ID;
struct AST_LP* LP;
struct AST_Args* Args;
struct AST_RP* RP;
 } bCall;
        struct { struct AST_ID* ID;
struct AST_LP* LP;
struct AST_RP* RP;
 } bCallV;
        struct { struct AST_Exp* Exp;
struct AST_LB* LB;
struct AST_Exp* Exp1;
struct AST_RB* RB;
 } bArr;
        struct { struct AST_Exp* Exp;
struct AST_DOT* DOT;
struct AST_ID* ID;
 } bFld;
        struct { struct AST_ID* ID;
 } bVar;
        struct { struct AST_INT* INT;
 } bInt;
        struct { struct AST_FLOAT* FLOAT;
 } bFloat;
    };
} AST_Exp;

typedef struct AST_Args {
    AST_HEADER;
    union{
        ast_base* child[1]; // child number is unk
        struct { struct AST_Exp* Exp;
struct AST_COMMA* COMMA;
struct AST_Args* Args;
 } b0;
        struct { struct AST_Exp* Exp;
 } b1;
    };
} AST_Args;

typedef struct AST_Program {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct {  /* may null */ 
struct AST_ExtDefList* ExtDefList;
 };
    };
} AST_Program;

typedef struct AST_ExtDefList {
    AST_HEADER;
    union{
        ast_base* child[2];
        struct { struct AST_ExtDef* ExtDef;
 /* may null */ 
struct AST_ExtDefList* ExtDefList;
 };
    };
} AST_ExtDefList;

typedef struct AST_ExtDef_Var {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Specifier* Specifier;
struct AST_ExtDecList* ExtDecList;
struct AST_SEMI* SEMI;
 };
    };
} AST_ExtDef_Var;

typedef struct AST_ExtDef_MayStruct {
    AST_HEADER;
    union{
        ast_base* child[2];
        struct { struct AST_Specifier* Specifier;
struct AST_SEMI* SEMI;
 };
    };
} AST_ExtDef_MayStruct;

typedef struct AST_ExtDef_Fn {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Specifier* Specifier;
struct AST_FunDec* FunDec;
struct AST_CompSt* CompSt;
 };
    };
} AST_ExtDef_Fn;

typedef struct AST_ExtDecList_0 {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_VarDec* VarDec;
struct AST_COMMA* COMMA;
struct AST_ExtDecList* ExtDecList;
 };
    };
} AST_ExtDecList_0;

typedef struct AST_ExtDecList_1 {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_VarDec* VarDec;
 };
    };
} AST_ExtDecList_1;

typedef struct AST_Specifier_Ty {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_TYPE* TYPE;
 };
    };
} AST_Specifier_Ty;

typedef struct AST_Specifier_Struct {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_StructSpecifier* StructSpecifier;
 };
    };
} AST_Specifier_Struct;

typedef struct AST_StructSpecifier_Ref {
    AST_HEADER;
    union{
        ast_base* child[2];
        struct { struct AST_STRUCT* STRUCT;
struct AST_Tag* Tag;
 };
    };
} AST_StructSpecifier_Ref;

typedef struct AST_StructSpecifier_Def {
    AST_HEADER;
    union{
        ast_base* child[5];
        struct { struct AST_STRUCT* STRUCT;
 /* may null */ 
struct AST_OptTag* OptTag;
struct AST_LC* LC;
 /* may null */ 
struct AST_DefList* DefList;
struct AST_RC* RC;
 };
    };
} AST_StructSpecifier_Def;

typedef struct AST_OptTag {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_ID* ID;
 };
    };
} AST_OptTag;

typedef struct AST_Tag {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_ID* ID;
 };
    };
} AST_Tag;

typedef struct AST_VarDec_Var {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_ID* ID;
 };
    };
} AST_VarDec_Var;

typedef struct AST_VarDec_Array {
    AST_HEADER;
    union{
        ast_base* child[4];
        struct { struct AST_VarDec* VarDec;
struct AST_LB* LB;
struct AST_INT* INT;
struct AST_RB* RB;
 };
    };
} AST_VarDec_Array;

typedef struct AST_FunDec_HasArg {
    AST_HEADER;
    union{
        ast_base* child[4];
        struct { struct AST_ID* ID;
struct AST_LP* LP;
struct AST_VarList* VarList;
struct AST_RP* RP;
 };
    };
} AST_FunDec_HasArg;

typedef struct AST_FunDec_NoArg {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_ID* ID;
struct AST_LP* LP;
struct AST_RP* RP;
 };
    };
} AST_FunDec_NoArg;

typedef struct AST_VarList_0 {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_ParamDec* ParamDec;
struct AST_COMMA* COMMA;
struct AST_VarList* VarList;
 };
    };
} AST_VarList_0;

typedef struct AST_VarList_1 {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_ParamDec* ParamDec;
 };
    };
} AST_VarList_1;

typedef struct AST_ParamDec {
    AST_HEADER;
    union{
        ast_base* child[2];
        struct { struct AST_Specifier* Specifier;
struct AST_VarDec* VarDec;
 };
    };
} AST_ParamDec;

typedef struct AST_CompSt {
    AST_HEADER;
    union{
        ast_base* child[4];
        struct { struct AST_LC* LC;
 /* may null */ 
struct AST_DefList* DefList;
 /* may null */ 
struct AST_StmtList* StmtList;
struct AST_RC* RC;
 };
    };
} AST_CompSt;

typedef struct AST_StmtList {
    AST_HEADER;
    union{
        ast_base* child[2];
        struct { struct AST_Stmt* Stmt;
 /* may null */ 
struct AST_StmtList* StmtList;
 };
    };
} AST_StmtList;

typedef struct AST_Stmt_Expr {
    AST_HEADER;
    union{
        ast_base* child[2];
        struct { struct AST_Exp* Exp;
struct AST_SEMI* SEMI;
 };
    };
} AST_Stmt_Expr;

typedef struct AST_Stmt_Comp {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_CompSt* CompSt;
 };
    };
} AST_Stmt_Comp;

typedef struct AST_Stmt_Ret {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_RETURN* RETURN;
struct AST_Exp* Exp;
struct AST_SEMI* SEMI;
 };
    };
} AST_Stmt_Ret;

typedef struct AST_Stmt_If {
    AST_HEADER;
    union{
        ast_base* child[5];
        struct { struct AST_IF* IF;
struct AST_LP* LP;
struct AST_Exp* Exp;
struct AST_RP* RP;
struct AST_Stmt* Stmt;
 };
    };
} AST_Stmt_If;

typedef struct AST_Stmt_Ife {
    AST_HEADER;
    union{
        ast_base* child[7];
        struct { struct AST_IF* IF;
struct AST_LP* LP;
struct AST_Exp* Exp;
struct AST_RP* RP;
struct AST_Stmt* Stmt;
struct AST_ELSE* ELSE;
struct AST_Stmt* Stmt1;
 };
    };
} AST_Stmt_Ife;

typedef struct AST_Stmt_While {
    AST_HEADER;
    union{
        ast_base* child[5];
        struct { struct AST_WHILE* WHILE;
struct AST_LP* LP;
struct AST_Exp* Exp;
struct AST_RP* RP;
struct AST_Stmt* Stmt;
 };
    };
} AST_Stmt_While;

typedef struct AST_DefList {
    AST_HEADER;
    union{
        ast_base* child[2];
        struct { struct AST_Def* Def;
 /* may null */ 
struct AST_DefList* DefList;
 };
    };
} AST_DefList;

typedef struct AST_Def {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Specifier* Specifier;
struct AST_DecList* DecList;
struct AST_SEMI* SEMI;
 };
    };
} AST_Def;

typedef struct AST_DecList_0 {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Dec* Dec;
struct AST_COMMA* COMMA;
struct AST_DecList* DecList;
 };
    };
} AST_DecList_0;

typedef struct AST_DecList_1 {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_Dec* Dec;
 };
    };
} AST_DecList_1;

typedef struct AST_Dec_Simple {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_VarDec* VarDec;
 };
    };
} AST_Dec_Simple;

typedef struct AST_Dec_WithInit {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_VarDec* VarDec;
struct AST_ASSIGNOP* ASSIGNOP;
struct AST_Exp* Exp;
 };
    };
} AST_Dec_WithInit;

typedef struct AST_Exp_Assign {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Exp* Exp;
struct AST_ASSIGNOP* ASSIGNOP;
struct AST_Exp* Exp1;
 };
    };
} AST_Exp_Assign;

typedef struct AST_Exp_And {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Exp* Exp;
struct AST_AND* AND;
struct AST_Exp* Exp1;
 };
    };
} AST_Exp_And;

typedef struct AST_Exp_Or {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Exp* Exp;
struct AST_OR* OR;
struct AST_Exp* Exp1;
 };
    };
} AST_Exp_Or;

typedef struct AST_Exp_Rel {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Exp* Exp;
struct AST_RELOP* RELOP;
struct AST_Exp* Exp1;
 };
    };
} AST_Exp_Rel;

typedef struct AST_Exp_Plus {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Exp* Exp;
struct AST_PLUS* PLUS;
struct AST_Exp* Exp1;
 };
    };
} AST_Exp_Plus;

typedef struct AST_Exp_Minus {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Exp* Exp;
struct AST_MINUS* MINUS;
struct AST_Exp* Exp1;
 };
    };
} AST_Exp_Minus;

typedef struct AST_Exp_Mul {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Exp* Exp;
struct AST_STAR* STAR;
struct AST_Exp* Exp1;
 };
    };
} AST_Exp_Mul;

typedef struct AST_Exp_Div {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Exp* Exp;
struct AST_DIV* DIV;
struct AST_Exp* Exp1;
 };
    };
} AST_Exp_Div;

typedef struct AST_Exp_P {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_LP* LP;
struct AST_Exp* Exp;
struct AST_RP* RP;
 };
    };
} AST_Exp_P;

typedef struct AST_Exp_Neg {
    AST_HEADER;
    union{
        ast_base* child[2];
        struct { struct AST_MINUS* MINUS;
struct AST_Exp* Exp;
 };
    };
} AST_Exp_Neg;

typedef struct AST_Exp_Not {
    AST_HEADER;
    union{
        ast_base* child[2];
        struct { struct AST_NOT* NOT;
struct AST_Exp* Exp;
 };
    };
} AST_Exp_Not;

typedef struct AST_Exp_Call {
    AST_HEADER;
    union{
        ast_base* child[4];
        struct { struct AST_ID* ID;
struct AST_LP* LP;
struct AST_Args* Args;
struct AST_RP* RP;
 };
    };
} AST_Exp_Call;

typedef struct AST_Exp_CallV {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_ID* ID;
struct AST_LP* LP;
struct AST_RP* RP;
 };
    };
} AST_Exp_CallV;

typedef struct AST_Exp_Arr {
    AST_HEADER;
    union{
        ast_base* child[4];
        struct { struct AST_Exp* Exp;
struct AST_LB* LB;
struct AST_Exp* Exp1;
struct AST_RB* RB;
 };
    };
} AST_Exp_Arr;

typedef struct AST_Exp_Fld {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Exp* Exp;
struct AST_DOT* DOT;
struct AST_ID* ID;
 };
    };
} AST_Exp_Fld;

typedef struct AST_Exp_Var {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_ID* ID;
 };
    };
} AST_Exp_Var;

typedef struct AST_Exp_Int {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_INT* INT;
 };
    };
} AST_Exp_Int;

typedef struct AST_Exp_Float {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_FLOAT* FLOAT;
 };
    };
} AST_Exp_Float;

typedef struct AST_Args_0 {
    AST_HEADER;
    union{
        ast_base* child[3];
        struct { struct AST_Exp* Exp;
struct AST_COMMA* COMMA;
struct AST_Args* Args;
 };
    };
} AST_Args_0;

typedef struct AST_Args_1 {
    AST_HEADER;
    union{
        ast_base* child[1];
        struct { struct AST_Exp* Exp;
 };
    };
} AST_Args_1;
#endif