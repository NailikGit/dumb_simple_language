#include "data.h"
#include "lexer.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

static char next() {
  char c;

  if(tmp) {
    c = tmp;
    tmp = 0;
    return c;
  }

  c = fgetc(in_file);
  if('\n' == c) line++;

  return c;
}

static void put_back(char c) {
  tmp = c;
}

static char skip() {
  char c = next();

  while(c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f') {
    c = next();
  }

  return c;
}
 
static int chr_pos(char* s, char c) {
  char* p = strchr(s, c);
  return (p ? p - s : -1);
}

static int scan_int(char c) {
  int k, val = 0;

  while((k = chr_pos("0123456789", c)) >= 0) {
    val = val * 10 + k;
    c = next();
  }

  put_back(c);
  return val;
}

int scan(struct token* t) {
  char c = skip();

  switch(c) {
    case EOF:
      t->token = T_EOF;
      return 0;
    case '+':
      t->token = T_PLUS;
      break;
    case '-':
      t->token = T_MINUS;
      break;
    case '*':
      t->token = T_MULT;
      break;
    case '/':
      t->token = T_DIV;
      break;
    default:
      if(isdigit(c)) {
        t->value = scan_int(c);
        t->token = T_INTLIT;
        break;
      }

      printf("Unrecognised character %c on line %d\n", c, line);
      exit(1);
  }

  return 1;
}
