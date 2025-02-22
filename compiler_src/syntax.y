%locations
%{
#define YYSTYPE ast_base* 
#include "lex.yy.c"

extern void yy_err_handler(int,const char*);
void yyerror(const char* msg) {
  yy_err_handler(yylineno,msg);
}

%}

%token INT FLOAT ID SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT TYPE LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT NEG
%left LP RP LB RB DOT

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start Program
%%
Program: ExtDefList { $$ = ast_setroot(new_ast_Program(@$.first_line,$1)); }
;
ExtDefList: ExtDef ExtDefList { $$ = new_ast_ExtDefList(@$.first_line,$1,$2); }
| error ExtDefList { $$ = NULL; }
| { $$ = NULL; }
;
ExtDef: Specifier ExtDecList SEMI { $$ = new_ast_ExtDef_Var(@$.first_line,$1,$2,$3); }
| Specifier SEMI { $$ = new_ast_ExtDef_MayStruct(@$.first_line,$1,$2); }
| Specifier FunDec CompSt { $$ = new_ast_ExtDef_Fn(@$.first_line,$1,$2,$3); }
;
ExtDecList: VarDec COMMA ExtDecList { $$ = new_ast_ExtDecList_0(@$.first_line,$1,$2,$3); }
| VarDec { $$ = new_ast_ExtDecList_1(@$.first_line,$1); }
;
Specifier: TYPE { $$ = new_ast_Specifier_Ty(@$.first_line,$1); }
| StructSpecifier { $$ = new_ast_Specifier_Struct(@$.first_line,$1); }
| error { $$ = NULL; }
;
StructSpecifier: STRUCT Tag { $$ = new_ast_StructSpecifier_Ref(@$.first_line,$1,$2); }
| STRUCT OptTag LC DefList RC { $$ = new_ast_StructSpecifier_Def(@$.first_line,$1,$2,$3,$4,$5); }
;
OptTag: ID { $$ = new_ast_OptTag(@$.first_line,$1); }
| { $$ = NULL; }
| error { $$ = NULL; }
;
Tag: ID { $$ = new_ast_Tag(@$.first_line,$1); }
| error { $$ = NULL; }
;
VarDec: ID { $$ = new_ast_VarDec_Var(@$.first_line,$1); }
| VarDec LB INT RB { $$ = new_ast_VarDec_Array(@$.first_line,$1,$2,$3,$4); }
| error { $$ = NULL; }
;
FunDec: ID LP VarList RP { $$ = new_ast_FunDec_HasArg(@$.first_line,$1,$2,$3,$4); }
| ID LP RP { $$ = new_ast_FunDec_NoArg(@$.first_line,$1,$2,$3); }
| error LP RP { $$ = NULL; }
| error LP VarList RP { $$ = NULL; }
;
VarList: ParamDec COMMA VarList { $$ = new_ast_VarList_0(@$.first_line,$1,$2,$3); }
| ParamDec { $$ = new_ast_VarList_1(@$.first_line,$1); }
;
ParamDec: Specifier VarDec { $$ = new_ast_ParamDec(@$.first_line,$1,$2); }
| error { $$ = NULL; }
;
CompSt: LC DefList StmtList RC { $$ = new_ast_CompSt(@$.first_line,$1,$2,$3,$4); }
;
StmtList: Stmt StmtList { $$ = new_ast_StmtList(@$.first_line,$1,$2); }
| Stmt error StmtList { $$ = NULL; }
| { $$ = NULL; }
;
Stmt: Exp SEMI { $$ = new_ast_Stmt_Expr(@$.first_line,$1,$2); }
| CompSt { $$ = new_ast_Stmt_Comp(@$.first_line,$1); }
| RETURN Exp SEMI { $$ = new_ast_Stmt_Ret(@$.first_line,$1,$2,$3); }
| IF LP Exp RP Stmt %prec LOWER_THAN_ELSE { $$ = new_ast_Stmt_If(@$.first_line,$1,$2,$3,$4,$5); }
| IF LP Exp RP Stmt ELSE Stmt { $$ = new_ast_Stmt_Ife(@$.first_line,$1,$2,$3,$4,$5,$6,$7); }
| WHILE LP Exp RP Stmt { $$ = new_ast_Stmt_While(@$.first_line,$1,$2,$3,$4,$5); }
| WHILE LP error Stmt { $$ = NULL; }
| WHILE error RP Stmt { $$ = NULL; }
| WHILE error LP Exp RP Stmt { $$ = NULL; }
| IF error LP Exp RP Stmt %prec LOWER_THAN_ELSE { $$ = NULL; }
| IF error LP Exp RP Stmt ELSE Stmt { $$ = NULL; }
| IF error Stmt %prec LOWER_THAN_ELSE { $$ = NULL; }
| IF error Stmt ELSE Stmt { $$ = NULL; }
| IF error RP Stmt %prec LOWER_THAN_ELSE { $$ = NULL; }
| IF error RP Stmt ELSE Stmt { $$ = NULL; }
;
DefList: Def DefList { $$ = new_ast_DefList(@$.first_line,$1,$2); }
| error DefList { $$ = NULL; }
| { $$ = NULL; }
;
Def: Specifier DecList SEMI { $$ = new_ast_Def(@$.first_line,$1,$2,$3); }
;
DecList: Dec COMMA DecList { $$ = new_ast_DecList_0(@$.first_line,$1,$2,$3); }
| Dec { $$ = new_ast_DecList_1(@$.first_line,$1); }
;
Dec: VarDec { $$ = new_ast_Dec_Simple(@$.first_line,$1); }
| VarDec ASSIGNOP Exp { $$ = new_ast_Dec_WithInit(@$.first_line,$1,$2,$3); }
;
Exp: Exp ASSIGNOP Exp { $$ = new_ast_Exp_Assign(@$.first_line,$1,$2,$3); }
| Exp AND Exp { $$ = new_ast_Exp_And(@$.first_line,$1,$2,$3); }
| Exp OR Exp { $$ = new_ast_Exp_Or(@$.first_line,$1,$2,$3); }
| Exp RELOP Exp { $$ = new_ast_Exp_Rel(@$.first_line,$1,$2,$3); }
| Exp PLUS Exp { $$ = new_ast_Exp_Plus(@$.first_line,$1,$2,$3); }
| Exp MINUS Exp { $$ = new_ast_Exp_Minus(@$.first_line,$1,$2,$3); }
| Exp STAR Exp { $$ = new_ast_Exp_Mul(@$.first_line,$1,$2,$3); }
| Exp DIV Exp { $$ = new_ast_Exp_Div(@$.first_line,$1,$2,$3); }
| LP Exp RP { $$ = new_ast_Exp_P(@$.first_line,$1,$2,$3); }
| MINUS Exp %prec NEG { $$ = new_ast_Exp_Neg(@$.first_line,$1,$2); }
| NOT Exp { $$ = new_ast_Exp_Not(@$.first_line,$1,$2); }
| ID LP Args RP { $$ = new_ast_Exp_Call(@$.first_line,$1,$2,$3,$4); }
| ID LP RP { $$ = new_ast_Exp_CallV(@$.first_line,$1,$2,$3); }
| Exp LB Exp RB { $$ = new_ast_Exp_Arr(@$.first_line,$1,$2,$3,$4); }
| Exp DOT ID { $$ = new_ast_Exp_Fld(@$.first_line,$1,$2,$3); }
| ID { $$ = new_ast_Exp_Var(@$.first_line,$1); }
| INT { $$ = new_ast_Exp_Int(@$.first_line,$1); }
| FLOAT { $$ = new_ast_Exp_Float(@$.first_line,$1); }
| error { $$ = NULL; }
;
Args: Exp COMMA Args { $$ = new_ast_Args_0(@$.first_line,$1,$2,$3); }
| Exp { $$ = new_ast_Args_1(@$.first_line,$1); }
;

%%