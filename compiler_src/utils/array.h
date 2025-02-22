#ifndef UARRAY_H
#define UARRAY_H
#include"../common.h"

typedef struct array{
    char* data;
    int size;
    int cap;
} array;

static inline void array_init(array* a){
    a->size=a->cap=0;
    a->data=(void*)0;
}

static inline void* array_at(array* a,int sz,int idx){
    return a->data+sz*idx;
}

static inline void array_expand(array* a,int esz,int tgt){
    if(tgt<=a->cap) return;
    int rtgt=a->cap;
    if(rtgt==0) rtgt=4;
    while(rtgt<tgt) rtgt<<=1;
    a->data=prealloc(a->data,rtgt*esz,a->cap*esz);
    a->cap=rtgt;
}

static inline void* array_wr_slot(array* a,int sz){
    array_expand(a,sz,a->size+1);
    return array_at(a,sz,a->size);
}

static inline void array_wr_fini(array* a){
    a->size+=1;
}

static inline void array_push(array* a,int sz,void* elem){
    memcpy(array_wr_slot(a,sz),elem,sz);
    array_wr_fini(a);
}

static inline void* array_pop(array* a,int sz){
    a->size-=1;
    return array_at(a,sz,a->size);
}

static inline void array_reset(array* a){
    a->size=0;
}

static inline void* array_back(array* a,int sz){
    return array_at(a,sz,a->size-1);
}

static inline void* array_search(array* a,int sz,unsigned long foff,const char* tgt,int* resid){
    for(int i=0;i<a->size;++i){
        char* elem=(char*)array_at(a,sz,i);
        if(strcmp(*(char**)(elem+foff),tgt)==0){
            if(resid!=NULL){
                *resid=i;
            }
            return elem;
        }
    }
    if(resid!=NULL)
        *resid=-1;
    return NULL;
}

#define ARRAY_PUSH(a,ty,lv) array_push(&(a),sizeof(ty),&(lv))
#define ARRAY_AT(a,ty,idx) ((ty*)array_at(&(a),sizeof(ty),idx))
#define ARRAY_POP(a,ty) ((ty*)array_pop(&(a),sizeof(ty)))
#define ARRAY_BACK(a,ty) ((ty*)array_back(&(a),sizeof(ty)))
#define ARRAY_WRSLOT(a,ty) ((ty*)array_wr_slot(&(a),sizeof(ty)))
#define ARRAY_WREND(a) array_wr_fini(&(a))
#define ARRAY_SEARCH2(a,ty,key,resid) ((ty*)array_search(&(a),sizeof(ty),(unsigned long)(&(((ty*)0)->name)),key,resid))
#define ARRAY_SEARCH(a,ty,key) ARRAY_SEARCH2(a,ty,key,NULL)


#endif
