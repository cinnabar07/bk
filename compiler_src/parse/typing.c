#include "typing.h"
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif 
#include "string.h"
#include "../ir/bb.h"

type* type_new_struct(structdef* sd){
    PNEW(type,res);
    res->ty=TY_STRUCT;
    res->sdef=sd;
    return res;
}

type* type_new_arr(type* inner,int siz){
    assert(0 && "array is not supported");
    PNEW(type,res);
    res->ty=TY_ARRAY;
    res->array.chd=inner;
    res->array.sz=siz;
    return res;
}

int type_size(type* ty){
    switch (ty->ty)
    {
    case TY_INT:
    case TY_FLOAT:
    return 4;
    
    case TY_STRUCT:
    return ty->sdef->size;

    case TY_ARRAY:
    return ty->array.sz*type_size(ty->array.chd);
    case TY_ERROR:
    return 4;
    }
    unreachable();
    return 4;
}
static int get_arr_btype(type* aty,type** out){
    int i=0;
    while(aty->ty==TY_ARRAY){
        aty=aty->array.chd;
        ++i;
    }
    if(out) *out=aty;
    return i;
}
type* type_unify(type* lhs,type* rhs){
    if(lhs->ty==TY_ERROR || rhs->ty==TY_ERROR){
        return type_getPrim(TY_ERROR);
    }
    if(lhs->ty!=rhs->ty){
        return NULL;
    }
    switch (lhs->ty)
    {
    case TY_INT:
    case TY_FLOAT:
        return lhs;
    
    case TY_ARRAY:{
        // check dim and base type
        type* lb,*rb;
        int ld=get_arr_btype(lhs,&lb);
        int rd=get_arr_btype(rhs,&rb);
        if(ld!=rd){
            // dim mismatch
            return NULL;
        }
        if(type_unify(lb,rb)){
            return lhs;
        }else{
            // base mismatch and is not TY_ERR
            return NULL;
        }
    }

    case TY_STRUCT:
    if(lhs->sdef==rhs->sdef){
        return lhs;
    }else{
        return NULL;
    }
    case TY_ERROR:
    {
        unreachable();
    }
    
    }
    // unreachable
    return NULL;
}

// check whether two types are compt
int type_comp(type* lhs,type* rhs){
    if(lhs->ty!=rhs->ty) return 0;
    // two incomplete types are not equ
    if(lhs->ty==TY_ERROR) return 0;
    switch (lhs->ty)
    {
    case TY_INT:
    case TY_FLOAT:
        return 1;
    
    case TY_ARRAY:
    return type_comp(lhs->array.chd,rhs->array.chd);

    case TY_STRUCT:
    return lhs->sdef==rhs->sdef;
    case TY_ERROR:
    return 0;
    }
    // unreachable
    return 0;
}

const char* type_debug(type* ty){
    char buf[128];
    switch (ty->ty)
    {
    case TY_INT:
        return "int";
    case TY_FLOAT:
        return "float";
    case TY_ARRAY:
        sprintf(buf,"(%s) [%d]",type_debug(ty->array.chd),ty->array.sz);
        return "<array>"; //strdup(buf);
    case TY_STRUCT:
        sprintf(buf,"struct %s",ty->sdef->name);
        return ty->sdef->name; // strdup(buf);
    case TY_ERROR:
        return "<error>";
    }
    unreachable();
    return "<error>";
}

static type ty_int,ty_float,ty_err;
rootEnv E;
env* CE;

static void init_rootenv(){
    PA_INIT(E.sdefs);
    PA_INIT(E.fdefs);
    PA_INIT(E.envstack);
    env_push();
}

void init_typing(){
    ty_int.ty=TY_INT;
    ty_float.ty=TY_FLOAT;
    ty_err.ty=TY_ERROR;
    init_rootenv();
}

type* type_getPrim(enum typekind ty){
    switch (ty)
    {
    case TY_INT:
        return &ty_int;
    case TY_FLOAT:
        return &ty_float;
    case TY_ERROR:
        return &ty_err;    
    default:
        return NULL;
    }
}

structfld* structfld_def(structdef* c,char* name,type* ty){
    assert(c->size<=1024);
    PNEW(structfld,res);
    res->name=name;
    res->ty=ty;
    res->offset=c->size;
    c->size+=type_size(ty);
    PA_PUSH(c->fields,structfld,res);
    return res;
}

structdef* structdef_def(char* name){
    PNEW(structdef,res);
    res->name=name;
    PA_INIT(res->fields);
    res->size=0;
    PA_PUSH(E.sdefs,structdef,res);
    return res;
}

structfld* structdef_queryfld(structdef* sd,char* name){
    return PA_SEARCH(sd->fields,structfld,name);
}

fndef* fndef_def(char* name,type* ret_ty){
    PNEW(fndef,res);
    res->name=name;
    res->ret_ty=ret_ty;
    PA_INIT(res->arg_ty);
    PA_INIT(res->arg_vars);
    PA_INIT(res->bb);
    PA_INIT(res->vars);
    PA_PUSH(E.fdefs,fndef,res);
    return res;
}

BB* fndef_bbnew(fndef* fdef){
    BB* bb=BB_new();
	PA_PUSH(fdef->bb,BB,bb);
    return bb;
}

void fndef_addarg(fndef* fdef,var* v){
    assert(fdef->arg_vars.size<=16);
    PA_PUSH(fdef->arg_ty,type,v->ty);
    PA_PUSH(fdef->arg_vars,var,v);
}

extern fndef *rm_fndef;

var* var_def(char* name,type* ty){
    PNEW(var,res);
    res->name=name;
    res->ty=ty;
    PA_PUSH(CE->vars,var,res);
    if(rm_fndef)
        PA_PUSH(rm_fndef->vars,var,res);
    return res;
}

env* env_new(){
    PNEW(env,res);
    PA_INIT(res->vars);
    return res;
}

void env_push(){
    CE=env_new();
    PA_PUSH(E.envstack,env,CE);
}

void env_pop(){
    PA_POP(E.envstack,env);
    CE=PA_BACK(E.envstack,env);
}

structdef* structdef_query(char* name){
    return PA_SEARCH(E.sdefs,structdef,name);
}

var* env_query_var(env* e,const char* name){
    return PA_SEARCH(e->vars,var,name);
}

var* var_query_recur(const char* name){
    var* res=NULL;
    for(int i=E.envstack.size-1;i>=0;--i){
        env* e=PA_AT(E.envstack,env,i);
        if((res=env_query_var(e,name))) break;
    }
    return res;
}

// query var in current ctx
var* var_query(const char* name){
    return env_query_var(CE,name);
}

fndef* fndef_query(const char* name){
    return PA_SEARCH(E.fdefs,fndef,name);
}