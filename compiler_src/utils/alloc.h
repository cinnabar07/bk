#ifndef MYALLOC_H
#define MYALLOC_H
#include<malloc.h>
#include"../mydefs.h"
void* pzone_create(void* identifier);
#define OPTIMIZE_ALLOC
#define OPTIMIZE_REALLOC
#define OPTIMIZE_STRDUP

#ifdef OPTIMIZE_ALLOC
void* palloc(u32 size);
#else
#define palloc(x) malloc(x)
#endif

char* pstrdup(const char* str);


#ifdef OPTIMIZE_REALLOC
void* prealloc(void* old,u32 newsize,u32 oldsize);
#else
#define prealloc(o,n,os) realloc(o,n)
#endif

#define PNEW(ty,name) ty* name=(ty*)palloc(sizeof(ty)) 
#endif