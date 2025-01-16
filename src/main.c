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
    exit(1);
  }
  in_file = fopen(argv[1], "r");

  scanfile();
  return 0;
}
