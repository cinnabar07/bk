#include "ast/ast_base.h"
#include "ast/ast_printer.h"
#include "codegen/mips.h"
#include "ir/ir_soptim.h"
#include "mydefs.h"
#include "parse/ast2sem.h"
#include "stdio.h"
#include "utils/alloc.h"
void print_fn(fndef *fd);
extern FILE *iof;

static int err = 0;

static int E_reported[4096];
static int Eptr;

void lex_err_handler(int line, const char *msg) {
  printf("Error at Line %d: Mysterious characters '%s'\n", line, msg);
  err = 1;
  E_reported[Eptr++] = line;
}

void yy_err_handler(int line, const char *msg) {
  for (int i = 0; i < Eptr; ++i)
    if (E_reported[i] == line)
      return;
  printf("Error at Line %d: %s\n", line, msg);
  err = 1;
}

void sem_err_handler(int line, int ty, const char *msg) {
  for (int i = 0; i < Eptr; ++i)
    if (E_reported[i] == line)
      return;
  E_reported[Eptr++] = line;
  printf("Error type %d at Line %d: %s\n", ty, line, msg);
  err = 1;
}

extern int yyparse();
extern void yyrestart(FILE *);
ast_base *ast_root;

static inline void escape_fn(fndef *fd);

#define WRITE_IR 0

int main(int argc, char **argv) {
  if (argc < 2) {
    return 1;
  }
  FILE *f = fopen(argv[1], "r");
  if (!f) {
    perror(argv[1]);
    return 1;
  }

  pzone_create(NULL);

  yyrestart(f);
  yyparse();
  if (err)
    return 1;

  visit_program((AST_Program *)ast_root, 1);
  if (err)
    return 1;

  for (int i = 2; i < E.fdefs.size; ++i) { // skip read and write
    fndef *fd = PA_AT(E.fdefs, fndef, i);
    simp_optimize_fn(fd);
    escape_fn(fd);
  }

  if (WRITE_IR) {
    if (argc >= 4)
      iof = fopen(argv[3], "w");
    else
      iof = stdout;
    for (int i = 2; i < E.fdefs.size; ++i) { // skip read and write
      fndef *fd = PA_AT(E.fdefs, fndef, i);
      print_fn(fd);
    }
  }
  
  if (argc >= 3)
    cg_iof = fopen(argv[2], "w");
  else
    cg_iof = stdout;
  cg_boot();
  for (int i = 2; i < E.fdefs.size; ++i) { // skip read and write
    fndef *fd = PA_AT(E.fdefs, fndef, i);
    cg_fn(fd);
  }
  return 0;
}

static int ectr = 0;

static inline char *get_anon_name() {
  char buf[16];
  sprintf(buf, "_av_%d", ++ectr);
  return pstrdup(buf);
}
const char *bad_names[] = {"main",   "LABEL", "FUNCTION", "GOTO", "IF",
                           "RETURN", "DEC",   "ARG",      "CALL", "PARAM",
                           "READ",   "WRITE", NULL};
static inline int check_name(const char *name) {
  for (int i = 0; bad_names[i]; ++i) {
    if (strcmp(bad_names[i], name) == 0) {
      return 1;
    }
  }
  return 0;
}
static inline void escape_fn(fndef *fd) {
  for (int i = 0; i < fd->vars.size; ++i) {
    var *v = PA_AT(fd->vars, var, i);
    if (!check_name(v->name))
      continue;
    v->name = get_anon_name();
  }
}
