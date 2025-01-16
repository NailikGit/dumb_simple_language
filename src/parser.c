#include "data.h"
#include "lexer.h"
#include "parser.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct ASTnode* mk_ast_node(int op, struct ASTnode* left,
                            struct ASTnode* right, int value) {
  struct ASTnode* n;

  n = malloc(sizeof(struct ASTnode));
  assert(n != NULL && "buy more ram lol");

  n->op = op;
  n->left = left;
  n->right = right;
  n->value = value;

  return n;
}

struct ASTnode* mk_ast_leaf(int op, int value) {
  return mk_ast_node(op, NULL, NULL, value);
}

struct ASTnode* mk_ast_unary(int op, struct ASTnode* left, int value) {
  return mk_ast_node(op, left, NULL, value);
}

int arith_op(int tok) {
  switch(tok) {
    case T_PLUS:
      return A_ADD;
    case T_MINUS:
      return A_SUB;
    case T_MULT:
      return A_MULT;
    case T_DIV:
      return A_DIV;
    default:
      fprintf(stderr, "[ERROR] unknown token in arith_op() on line %d\n", line);
      exit(1);
  }
}

static struct ASTnode* primary() {
  struct ASTnode* n;

  switch(token.token) {
    case T_INTLIT:
      n = mk_ast_leaf(A_INTLIT, token.value);
      scan(&token);
      return n;
    default:
      fprintf(stderr, "[ERROR] syntax error on line %d\n", line);
      exit(1);
  }
}

static int opprec[] = {0, 10, 10, 20, 20, 0};
                  // {EOF,  +,  -,  *,  /, INTLIT}

static int op_prec(int token_type) {
  int prec = opprec[token_type];

  if(prec == 0) {
    fprintf(stderr, "[ERROR] syntax error on line %d, token %d\n", line, token_type);
    exit(1);
  }

  return prec;
}

struct ASTnode* bin_expr(int ptp) {
  struct ASTnode *left, *right;
  int token_type;

  left = primary();

  token_type = token.token;
  if(token_type == T_EOF) return left;

  while(op_prec(token_type) > ptp) {
    scan(&token);

    right = bin_expr(op_prec(token_type));

    left = mk_ast_node(arith_op(token_type), left, right, 0);

    token_type = token.token;
    if(token_type == T_EOF) break;
  }

  return left;
}

int interpret_AST(struct ASTnode* n) {
  int leftval, rightval;

  if(n->left) leftval = interpret_AST(n->left);
  if(n->right) rightval = interpret_AST(n->right);

  switch(n->op) {
    case A_ADD:
      return (leftval + rightval);
    case A_SUB:
      return (leftval - rightval);
    case A_MULT:
      return (leftval * rightval);
    case A_DIV:
      return (leftval / rightval);
    case A_INTLIT:
      return n->value;
    default:
      fprintf(stderr, "[ERROR] unknown AST operator %d\n", n->op);
      exit(1);
  }
}

