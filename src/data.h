#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#ifndef extern_
  #define extern_ extern
#endif

enum tokens {
  T_EOF, T_PLUS, T_MINUS, T_MULT, T_DIV, T_INTLIT, T_SEMI, T_PRINT
};

struct token {
  int token;
  int value;
};

enum {
  A_ADD, A_SUB, A_MULT, A_DIV, A_INTLIT
};

struct ASTnode {
  int op;
  struct ASTnode* left;
  struct ASTnode* right;
  int value;
};

extern_ int line;
extern_ char tmp;
extern_ struct token token;

extern_ FILE* in_file;
extern_ FILE* out_file;

#define text_len 512
extern_ char text[text_len + 1];

#endif
