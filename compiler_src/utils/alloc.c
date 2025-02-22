#define _GNU_SOURCE
#include "string.h"
#include<malloc.h>
#include"../common.h"

#undef prealloc
#undef palloc

typedef struct chunk_hdr{
    u32 allocated;
    u32 avail;
    void* ident;
    struct zone_chunk* next;
} chunk_hdr;

#define CHUNK_SIZE (8*1024*1024)
#define CHUNK_BUF_SIZE (CHUNK_SIZE-sizeof(chunk_hdr))

typedef struct zone_chunk{
    chunk_hdr hdr;
    char buf[CHUNK_BUF_SIZE];
} zone_chunk;

static zone_chunk* current_zone;

static zone_chunk* alloc_chunk(zone_chunk* next,void* ident);

void* palloc(u32 size){
    size=(size+15)&(~(u32)15);
    // fallback
    if(!current_zone || size>CHUNK_BUF_SIZE)
        return malloc(size);
    if(size>current_zone->hdr.avail){
        current_zone=alloc_chunk(current_zone,current_zone->hdr.ident);
    }
    char* res=current_zone->buf+current_zone->hdr.allocated;
    current_zone->hdr.allocated+=size;
    current_zone->hdr.avail-=size;
    return res;
}

void* prealloc(void* old,u32 newsize,u32 oldsize){
    void* new=palloc(newsize);
    if(old)
        memcpy(new,old,oldsize);
    return new;
}

static zone_chunk* alloc_chunk(zone_chunk* next,void* ident){
    zone_chunk* res=(zone_chunk*)malloc(sizeof(zone_chunk));
    res->hdr.next=next;
    res->hdr.allocated=0;
    res->hdr.avail=sizeof(res->buf);
    res->hdr.ident=ident;
    return res;
}

void* pzone_create(void* ident){
    current_zone=alloc_chunk(NULL,ident);
    return current_zone;
}

char* pstrdup(const char* c){
    #ifdef OPTIMIZE_STRDUP
    int l=strlen(c);
    void* r=palloc(l+1);
    memcpy(r,c,l+1);
    return (char*)r;
    #else
    return strdup(c);
    #endif
}
