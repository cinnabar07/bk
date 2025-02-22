#ifndef SCM_H
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif 
#include "string.h"
#define SCM_H
void sem_err_handler(int line,int ty,const char* msg);
static inline char* gen_anon(ast_base* node){
	static int uctr=0;
	char buf[32];
	sprintf(buf,"_A_%d_%d",node->lineno,++uctr);
	return pstrdup(buf);
}

#define ABASE ((ast_base*)node)
#define ANON_NAME gen_anon(ABASE)

enum ETypes{
	ERR_NOVAR=1,
	ERR_NOFN,
	ERR_DUPVAR,
	ERR_DUPFN,
	ERR_ASSTY,
	ERR_ASSRV,
	ERR_BINTY,
	ERR_RETTY,
	ERR_ARG,
	ERR_ABASETY, // error ty [x]
	ERR_FNTY, // error ty (..)
	ERR_AINDTY, // arr [ error ty ]
	ERR_STRUTY, // error ty . field
	ERR_NOFLD,
	ERR_DUPFLD, // dup fld or unsupp init
	ERR_DUPSTRU,
	ERR_NOSTRU
};

#define REPORT_ERR(errtype) sem_err_handler(node->lineno,errtype,"error")
#define ERROR_ON(cond,errtype) if(cond) REPORT_ERR(errtype)

extern fndef* rm_fndef;

#endif