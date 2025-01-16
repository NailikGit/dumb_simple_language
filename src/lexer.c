#include <stdio.h>
#include <ctype.h>
#include "lexer.h"

static int gettok() {
  static char c = ' ';

  // Skip any whitespace.
  while (isspace(c))
    c = getchar();

  if(isalpha(c)) {
    id_str.count = 0;
    const char buf[] = {c};
    nob_sb_append_cstr(&id_str, buf);

    while (isalnum((c = getchar()))) {
      const char buf[] = {c};
      nob_sb_append_buf(&id_str, buf, 1);
    }

    nob_sb_append_null(&id_str);
    if (strcmp(id_str.items, "fuc") == 0) return tok_fuc;
    return tok_id;
  } 
  if(isdigit(c)) {
    Nob_String_Builder num_str = {0};
    do {
      const char buf[] = {c};
      nob_sb_append_buf(&num_str, buf, 1);
      c = getchar();
    } while (isdigit(c));

    nob_sb_append_null(&num_str);
    num_val = strtod(num_str.items, 0);
    nob_sb_free(num_str);
    return tok_num;
  }
  if(c == '/') {
    c = getchar();
    if(c == '/') {
      do {
        c = getchar();
      } while (c != EOF && c != '\n' && c != '\r');

      if(c != EOF) return gettok();
    }
  }
  if(c == EOF) return tok_eof;
  return c;
}

int main() {
  return 0;
  gettok();
}
