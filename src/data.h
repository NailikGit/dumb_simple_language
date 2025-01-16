#include <stdio.h>
#ifndef extern_
  #define extern_ extern
#endif
enum tokens {
  T_PLUS, T_MINUS, T_MULT, T_DIV, T_INTLIT
};

struct token {
  char token;
  int value;
};

extern_ int line;
extern_ char tmp;
extern_ FILE* in_file;
