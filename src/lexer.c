#include "data.h"
#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
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

static int scan_indent(char c, char* buf, int lim) {
  int i = 0;

  while(isalpha(c) || isdigit(c) || c == '_') {
    if(lim - 1 == i) {
      fprintf(stderr, "[ERROR] identifier to long in line %d\n", line);
      exit(1);
    } else if(i < lim - 1) {
      buf[i++] = c;
    }

    c = next();
  }

  put_back(c);
  buf[i] = 0;
  return i;
}

static int keyword(char* s) {
  switch(*s) {
    case 'p':
      if(!strcmp(s, "print")) return T_PRINT;
      break;
  }

  return 0;
}

int scan(struct token* t) {
  char c = skip();

  int token_type;

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
    case ';':
      t->token = T_SEMI;
      break;
    default:
      if(isdigit(c)) {
        t->value = scan_int(c);
        t->token = T_INTLIT;
        break;
      } else if(isalpha(c) || c == '_') {
        scan_indent(c, text, text_len);

        if((token_type = keyword(text))) {
          t->token = token_type;
          break;
        }

        fprintf(stderr, "[ERROR] unrecognised symbol on line %d\n", line);
        exit(1);
      }

      printf("Unrecognised character %c on line %d\n", c, line);
      exit(1);
  }

  return 1;
}
