#ifndef COMMON_H
#define COMMON_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif 

#include "assert.h"
#include "mydefs.h"
#include "utils/alloc.h"
#include "string.h"
#include "stdio.h"
#define CONCAT_IMPL(a,b) a##b
#define CONCAT(a,b) CONCAT_IMPL(a,b)

// #define unreachable() assert(0)
#define unreachable() do{} while(0)
#endif