#ifndef GEN_H
#define GEN_H
#include "data.h"

int gen_AST(struct ASTnode* n);
void gen_preamble();
void gen_postamble();
void gen_free_regs();
void gen_print_int(int reg);

#endif
