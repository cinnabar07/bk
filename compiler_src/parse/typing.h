#ifndef TYPING_H
#define TYPING_H
#include"../utils/parray.h"
enum typekind{
    TY_INT,
    TY_FLOAT,
    TY_ARRAY,
    TY_STRUCT,
    TY_ERROR
};
typedef struct type{
    enum typekind ty;
    union
    {
        struct { int sz; struct type *chd; } array; // array child
        struct structdef *sdef; // struct def
    };
} type;

typedef struct structfld{
    char* name;
    type* ty;
    int offset;
} structfld;

typedef struct structdef{
    char* name;
    parray fields; // structfld 
    int size;
} structdef;

typedef struct fndef{
    char* name;
    type* ret_ty;
    parray arg_ty; // type* 
    parray arg_vars; // ! shared var reference
    parray bb; // BB
    parray vars; // var*
} fndef;

typedef struct var{
    union{
        struct {char* name; type* ty;}; // parser
        struct {char* vname; int off; int moff; /* moff: TODO */}; // codegen
    };
} var;

typedef struct env{
    parray vars; // var
} env;

typedef struct rootEnv{
    parray sdefs; // structdef
    parray fdefs; // fndef
    parray envstack; // env
} rootEnv;

type* type_new_struct(structdef* sd);
type* type_new_arr(type* inner,int siz);
int type_size(type* ty);
int type_comp(type* lhs,type* rhs);
type* type_unify(type* lhs,type* rhs);

const char* type_debug(type* ty);
extern rootEnv E;
extern env* CE;
void init_typing();
type* type_getPrim(enum typekind ty);
structfld* structfld_def(structdef* c,char* name,type* ty);
structdef* structdef_def(char* name);
structfld* structdef_queryfld(structdef* sd,char* name);
fndef* fndef_def(char* name,type* ret_ty);
void fndef_addarg(fndef* fdef,var* v);
var* var_def(char* name,type* ty);
env* env_new();
void env_push();
void env_pop();
structdef* structdef_query(char* name);
var* var_query_recur(const char* name);
// query var in current ctx
var* var_query(const char* name);
fndef* fndef_query(const char* name);

struct BB* fndef_bbnew(fndef* fdef);

#define TY_ISERR(t) ((t)->ty==TY_ERROR)
#define TY_ISPTR(t) ((t)->ty==TY_ARRAY || (t)->ty==TY_STRUCT)
#endif