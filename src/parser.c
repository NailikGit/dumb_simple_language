#include "lexer.h"
#include <stdlib.h>

enum type {
  num = 1,
  var = 2,
  bin = 3,
};

typedef struct num_expr {
  int val;
} num_expr;

typedef struct var_expr {
  const char* name;
} var_expr;

typedef struct bin_expr {
  char op;
  void* lhs;
  int lht;
  void* rhs;
  int rht;
} bin_expr;

typedef struct {
  void* content;
  int type;
} item;

typedef struct {
  item* items;
} da;

typedef struct call_expr {
  const char* name;
  da args;
} call_expr;

typedef struct prototype {
  const char* name;
  const char** args;
} prototype;

typedef struct function {
  prototype* proto;
  void* body;
  int bt;
} function;

static int cur_tok;
static int get_next_tok() {
  return cur_tok = gettok();
}

void* log_err(const char* str) {
  nob_log(NOB_ERROR, "%s", str);
  return NULL;
}
void* log_err_p(const char* str) {
  return log_err(str);
}

static void* parse_expr(int* i); // fw declaration
// num_expr := number
static void* parse_num_expr() {
  num_expr* r = malloc(sizeof(num_expr));
  r->val = num_val;
  get_next_tok(); // eat number
  return (void*) r;
}
// paren_expr := '(' expr ')'
static void* parse_paren_expr() {
  get_next_tok(); // eat '('
  int t;
  void* v = parse_expr(&t);
  if(!v) return NULL;

  if(cur_tok != ')') return log_err("expected ')'");
  get_next_tok();
  return v;
}

static void* parse_expr(int* i) {
  return NULL;
}
