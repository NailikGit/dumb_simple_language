#define extern_
#include "data.h"
#undef extern_
#include "lexer.h"
#include "parser.h"
#include <stdio.h>

char* tokstr[] = {"+", "-", "*", "/", "intlit"};

static void init(const char* filename) {
  line = 0;
  tmp = 0;
  in_file = fopen(filename, "r");
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    fprintf(stderr, "[ERROR] no input file provided");
    return 1;
  }

  init(argv[1]);

  scan(&token);
  struct ASTnode* n = bin_expr();
  printf("%d\n", interpret_AST(n));

  return 0;
}
