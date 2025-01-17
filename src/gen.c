#include "gen.h"
#include "cg.h"
#include "data.h"
#include <stdlib.h>

int gen_AST(struct ASTnode* n) {
  int leftreg, rightreg;

  if(n->left) leftreg = gen_AST(n->left);
  if(n->right) rightreg = gen_AST(n->right);

  switch(n->op) {
    case A_ADD:
      return cg_add(leftreg, rightreg);
    case A_SUB:
      return cg_sub(leftreg, rightreg);
    case A_MULT:
      return cg_mul(leftreg, rightreg);
    case A_DIV:
      return cg_div(leftreg, rightreg);
    case A_INTLIT:
      return cg_load(n->value);
    default:
      fprintf(stderr, "[ERROR] unknown AST operator %d\n", n->op);
      exit(1);
  }
}
void gen_preamble() {
  cg_preamble();
}
void gen_postamble() {
  cg_postamble();
}
void gen_free_regs() {
  free_all_registers();
}
void gen_print_int(int reg) {
  cg_print_int(reg);
}
