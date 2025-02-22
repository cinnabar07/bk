#ifndef IRBB_H
#define IRBB_H
#include "../utils/parray.h"
#include "../parse/typing.h"
#include "../mydefs.h"
#include "../utils/array.h"
typedef enum binop_type{
    B_ADD,
    B_SUB,
    B_MUL,
    B_DIV
} binop_type;


typedef enum term_type{
    CC_GT=1,
    CC_LT,
    CC_GE,
    CC_LE,
    CC_EQ,
    CC_NE,
    T_RET,
    T_JMP
} term_type;

#define T_BR CC_NE


typedef enum OpType{
    OP_IMM,
    OP_VAR,
    OP_DEREF,
    OP_FN,
    OP_BINOP,
    OP_ERR
} OpType;

typedef struct Operand{
    OpType type;
    union{
        int imm;
        var* var;
        const char* name;
        binop_type binop;
    };
} Operand;

static inline Operand op_imm(int i){
    Operand r;
    r.type=OP_IMM;
    r.imm=i;
    return r;
}

static inline Operand op_var(var* v){
    Operand r;
    r.type=OP_VAR;
    r.var=v;
    return r;
}

typedef struct IFCond{
    term_type op;
    int bbid;
    Operand lhs;
    Operand rhs;
} IFCond;

// basic block
typedef struct BB{
    parray ir; // IRBase
    union{
        // fucking magic to reduce 8bytes size
        struct {term_type tt;int bbid;};
        struct {term_type tt;int bbid;Operand op;} t_ret; // tt==T_RET
        struct {term_type tt;int bbid;struct BB* next;} t_jmp; // tt=T_JMP
        struct {IFCond cond;struct BB* yes; struct BB* no;} t_br; // tt<=T_BR
    };
} BB;

extern BB* bb_curr;

#define BB_setcurr(bb) bb_curr=bb

#define BB_curr() bb_curr

typedef enum IRKind{
    IR_MOV, // out = op0
    IR_BIN, // out = op0 bin(opext) op1
    IR_STR, // out (*x) = op0
    IR_ALLOC, // DEC out op0(const)
    IR_CALL, // IR_WRITE & IR_READ , out = call opext (op0,...)
    IR_NOP
} IRKind;

#define IRHEAD     IRKind kind; \
    u16 ext_cnt; \
    u16 in_cnt

typedef Operand pOperand[1];

typedef struct IRBase{
    IRHEAD;
    Operand out;
    Operand ops[0];
    // EXT_IDX=0
    // IN_IDX=ext_cnt
} IRBase;

typedef struct IRMov{
    IRHEAD;
    Operand out;
    Operand op0;
} IRMov;

typedef struct IRBin{
    IRHEAD;
    Operand out;
    Operand binop;
    Operand op0;
    Operand op1;
} IRBin;

typedef struct IRStr{
    IRHEAD;
    Operand out;
    Operand op0;
} IRStr;

typedef struct IRAlloc{
    IRHEAD;
    Operand out;
    Operand size;
} IRAlloc;

typedef struct IRCall{
    IRHEAD;
    Operand out;
    Operand tgt;
    Operand args[0];
} IRCall;

typedef struct IRNop{
    IRHEAD;
} IRNop;

typedef struct ExprInfo{
    type* ty;
    Operand op;
} ExprInfo;

BB* BB_new();
void BB_end_ret(pOperand v);
void BB_end_jmp(BB* tgt);
void BB_end_br(IFCond* cond,BB* yes,BB* no);

void emit_mov_or_str(pOperand out,pOperand op0);
void emit_bin(pOperand out,binop_type binop,pOperand lhs,pOperand rhs);
void emit_alloc(pOperand out,int size);
// array ExprInfo
void emit_call(pOperand out,const char* tgt,array* args);

#endif