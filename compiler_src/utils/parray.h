#ifndef PARRAY_H
#define PARRAY_H
#include"../common.h"

typedef struct parray{
    void** data;
    int size;
    int cap;
} parray;

static inline void pa_init(parray* a){
    a->size=a->cap=0;
    a->data=(void*)0;
}

static inline void* pa_at(parray* a,int idx){
    return a->data[idx];
}

static inline void pa_expand(parray* a,int tgt){
    if(tgt<=a->cap) return;
    int rtgt=a->cap;
    if(rtgt==0) rtgt=8;
    while(rtgt<tgt) rtgt<<=1;
    a->data=prealloc(a->data,rtgt*sizeof(void*),a->cap*sizeof(void*));
    a->cap=rtgt;
}

static inline void** pa_wr_slot(parray* a){
    pa_expand(a,a->size+1);
    return &a->data[a->size];
}

static inline void pa_wr_fini(parray* a){
    a->size+=1;
}

static inline void pa_push(parray* a,void* elem){
    *pa_wr_slot(a)=elem;
    pa_wr_fini(a);
}

static inline void* pa_pop(parray* a){
    a->size-=1;
    return pa_at(a,a->size);
}

static inline void pa_reset(parray* a){
    a->size=0;
}

static inline void* pa_back(parray* a){
    return pa_at(a,a->size-1);
}

static inline void* pa_search(parray* a,unsigned long foff,const char* tgt,int* resid){
    for(int i=0;i<a->size;++i){
        char* elem=(char*)pa_at(a,i);
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

#define PA_INIT(a) pa_init(&(a))
#define PA_PUSH(a,ty,lv) pa_push(&(a),lv)
#define PA_AT(a,ty,idx) ((ty*)pa_at(&(a),idx))
#define PA_POP(a,ty) ((ty*)pa_pop(&(a)))
#define PA_BACK(a,ty) ((ty*)pa_back(&(a)))
#define PA_WRSLOT(a,ty) ((ty**)pa_wr_slot(&(a)))
#define PA_WREND(a) pa_wr_fini(&(a))
#define PA_SEARCH2(a,ty,key,resid) ((ty*)pa_search(&(a),(unsigned long)(&(((ty*)0)->name)),key,resid))
#define PA_SEARCH(a,ty,key) PA_SEARCH2(a,ty,key,NULL)


#endif
