#define extern_
#include "data.h"
#undef extern_
#include "lexer.h"
#include <stdio.h>

char* tokstr[] = {"+", "-", "*", "/", "intlit"};

static void scanfile() {
  struct token t;

  while(scan(&t)) {
    printf("Token %s", tokstr[t.token]);
    if(t.token == T_INTLIT) printf(", value %d", t.value);
    printf("\n");
  }
}

int main(int argc, char* argv[]) {
  if(argc == 1) {
    fprintf(stderr, "[ERROR] no input file provided");
    return 1;
  }
  line = 0;
  tmp = 0;
  in_file = fopen(argv[1], "r");

  scanfile();
  return 0;
}
