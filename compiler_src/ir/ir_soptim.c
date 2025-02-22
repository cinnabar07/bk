#include "ir_soptim.h"
#include "bb.h"
static const term_type flip_tt[]={0,CC_LE,CC_GE,CC_LT,CC_GT,CC_NE,CC_EQ};
static void flip_ifcond(fndef* fd){
    for(int i=0;i<fd->bb.size;++i){
        BB* bb=PA_AT(fd->bb,BB,i);
        if(bb->tt==0) continue;
        if(bb->tt<=T_BR){
            bb->tt=flip_tt[bb->tt];
            BB* oy=bb->t_br.yes;
            bb->t_br.yes=bb->t_br.no;
            bb->t_br.no=oy;
        }
    }
}
static int inline_tramp_bb(BB** t){
    if((*t)->ir.size==0 && (*t)->tt==T_JMP){
        *t = (*t)->t_jmp.next;
        return 1;
    }
    return 0;
}
// c = ... jmp TB, inlink TB.term to c
static int inline_term_bb(BB* c){
    BB* n=c->t_jmp.next;
    if(n->ir.size) return 0;
    int chg= (memcmp(&c->t_br,&n->t_br,sizeof(c->t_br)));
    if(!chg) return 0;
    memcpy(&c->t_br,&n->t_br,sizeof(c->t_br));
    return 1;
}

static int optimize_bb_term(fndef* fd){
    int chg=0;
    for(int i=0;i<fd->bb.size;++i){
        BB* bb=PA_AT(fd->bb,BB,i);
        // step1. check all outs
        if(bb->tt==0){
            continue;
        }
        if(bb->tt<=T_BR){
            BB** b1=&bb->t_br.yes;
            BB** b2=&bb->t_br.no;
            chg|=inline_tramp_bb(b1);
            chg|=inline_tramp_bb(b2);
        }else{
            if(bb->tt==T_JMP){
                BB** b=&bb->t_jmp.next;
                chg|=inline_tramp_bb(b);
                // step2. inline term
                chg|=inline_term_bb(bb);
            }else{
                // ret
            }
        }
    }
    return chg;
}
void simp_optimize_fn(fndef* fd){
    // flip_ifcond(fd);
    while(optimize_bb_term(fd));
}
