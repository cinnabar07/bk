%option yylineno
%{
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif 
#include "ast/ast_base.h"
#include "ast/ast_factory.h"
#include "syntax.tab.h"
#include "stdlib.h"
#include "string.h"

char* pstrdup(const char* str);

extern void lex_err_handler(int,const char*);
int lex_val_INT(int sz,char* c){
    // strtol handles 0x prefix and 0 prefix
    return strtol(c,NULL,0);
}

float lex_val_FLOAT(int sz,char* c){
    return atof(c);
}

char* lex_val_ID(int sz,char* c){
    return pstrdup(c);
}

int yycolumn = 1;

#define YY_USER_ACTION \
  yylloc.first_line = yylloc.last_line = yylineno; \
  yylloc.first_column = yycolumn; \
  yylloc.last_column = yycolumn + yyleng - 1; \
  yycolumn += yyleng;

%}
%%
[ \t\r] {}
\n { yycolumn = 1; }
";" { yylval = new_ast_SEMI(yylineno); return SEMI; }
"," { yylval = new_ast_COMMA(yylineno); return COMMA; }
"=" { yylval = new_ast_ASSIGNOP(yylineno); return ASSIGNOP; }
">" { yylval = new_ast_RELOP_GT(yylineno); return RELOP; }
"<" { yylval = new_ast_RELOP_LT(yylineno); return RELOP; }
">=" { yylval = new_ast_RELOP_GE(yylineno); return RELOP; }
"<=" { yylval = new_ast_RELOP_LE(yylineno); return RELOP; }
"==" { yylval = new_ast_RELOP_EQ(yylineno); return RELOP; }
"!=" { yylval = new_ast_RELOP_NE(yylineno); return RELOP; }
"+" { yylval = new_ast_PLUS(yylineno); return PLUS; }
"-" { yylval = new_ast_MINUS(yylineno); return MINUS; }
"*" { yylval = new_ast_STAR(yylineno); return STAR; }
"/" { yylval = new_ast_DIV(yylineno); return DIV; }
"&&" { yylval = new_ast_AND(yylineno); return AND; }
"||" { yylval = new_ast_OR(yylineno); return OR; }
"." { yylval = new_ast_DOT(yylineno); return DOT; }
"!" { yylval = new_ast_NOT(yylineno); return NOT; }
"int" { yylval = new_ast_TYPE_INT(yylineno); return TYPE; }
"float" { yylval = new_ast_TYPE_FLOAT(yylineno); return TYPE; }
"(" { yylval = new_ast_LP(yylineno); return LP; }
")" { yylval = new_ast_RP(yylineno); return RP; }
"[" { yylval = new_ast_LB(yylineno); return LB; }
"]" { yylval = new_ast_RB(yylineno); return RB; }
"{" { yylval = new_ast_LC(yylineno); return LC; }
"}" { yylval = new_ast_RC(yylineno); return RC; }
"struct" { yylval = new_ast_STRUCT(yylineno); return STRUCT; }
"return" { yylval = new_ast_RETURN(yylineno); return RETURN; }
"if" { yylval = new_ast_IF(yylineno); return IF; }
"else" { yylval = new_ast_ELSE(yylineno); return ELSE; }
"while" { yylval = new_ast_WHILE(yylineno); return WHILE; }
0|[1-9][0-9]*|0[xX][0-9a-fA-F]+|0[0-7]+ { yylval = new_ast_INT(yylineno,lex_val_INT(yyleng,yytext)); return INT; }
[0-9]+"."[0-9]+ { yylval = new_ast_FLOAT(yylineno,lex_val_FLOAT(yyleng,yytext)); return FLOAT; }
[a-zA-Z_][0-9a-zA-Z_]* { yylval = new_ast_ID(yylineno,lex_val_ID(yyleng,yytext)); return ID; }

. {
    lex_err_handler(yylineno,yytext);
}
%%