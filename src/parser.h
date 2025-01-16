#ifndef PARSER_H
#define PARSER_H

struct ASTnode* mk_ast_node(int op, struct ASTnode* left,
                            struct ASTnode* right, int intvalue);

struct ASTnode* mk_ast_leaf(int op, int intvalue);

struct ASTnode* mk_ast_unary(int op, struct ASTnode* left, int intvalue);

struct ASTnode* bin_expr(int ptp);

int interpret_AST(struct ASTnode* n);

#endif
