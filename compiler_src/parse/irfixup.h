#ifndef IRFIXH
#define IRFIXH
#include "../ir/bb.h"
#if 0
static inline void fixup_relop(Operand* op){
    return;
}
static inline void fixup_binop(Operand* op){
    return;
}
#else
#define fixup_relop(op) do{}while(0)
#define fixup_binop(op) do{}while(0)
#define fixup_retop(op) do{}while(0)
#define fixup_argop(op) do{}while(0)
#endif
#endif