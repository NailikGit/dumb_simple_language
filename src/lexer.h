#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum tokens {
  T_PLUS, T_MINUS, T_MULT, T_DIV, T_INTLIT
};

struct token {
  char token;
  int value;
};

extern int line;
extern char tmp;
extern FILE* in_file;

int scan(struct token* t);
