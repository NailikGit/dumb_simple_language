#include "stmt.h"
#include "data.h"
#include "gen.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

void match(int t, char* what) {
  if(token.token == t) scan(&token);
  else {
    fprintf(stderr, "[ERROR] %s expected on line %d\n", what, line);
    exit(1);
  }
}

void semi() {
  match(T_SEMI, ";");
}

void statements() {
  struct ASTnode* tree;
  int reg;

  while(1) {
    match(T_PRINT, "print");

    tree = bin_expr(0);
    reg = gen_AST(tree);
    gen_print_int(reg);
    gen_free_regs();

    semi();
    if(token.token == T_EOF) return;
  }
}
