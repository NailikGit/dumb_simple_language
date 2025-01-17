#include "stmt.h"
#define extern_
#include "data.h"
#undef extern_
#include "lexer.h"
#include "gen.h"
#include <stdio.h>

char* tokstr[] = {"+", "-", "*", "/", "intlit"};

static void init(const char* filename) {
  line = 0;
  tmp = 0;
  in_file = fopen(filename, "r");
  out_file = fopen("out.asm", "w");
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    fprintf(stderr, "[ERROR] no input file provided");
    return 1;
  }

  init(argv[1]);

  scan(&token);
  gen_preamble();
  statements();
  gen_postamble();

  fclose(in_file);
  fclose(out_file);

  return 0;
}
