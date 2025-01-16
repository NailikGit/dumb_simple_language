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

struct ASTnode* bin_expr() {
  struct ASTnode *n, *left, *right;
  int nodetype;

  left = primary();

  if(token.token == T_EOF) return left;

  nodetype = arith_op(token.token);

  scan(&token);

  right = bin_expr();

  n = mk_ast_node(nodetype, left, right, 0);
  return n;
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
