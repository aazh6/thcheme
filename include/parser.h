#ifndef _PARSER_H
#define _PARSER_H

#include "dystr.h"

#define ISIDENTSYM(ch) strchr("!$%&*+-./:<=>\?@^_~", ch)

typedef enum {
    START, NUMBER, IDENT, WHITESPACE, LPAREN, RPAREN, END
} Token_Type;

typedef struct Token {
    Token_Type type;
    char *val;
} Token_t;

struct Sexpr_List;

typedef struct Sexpr {
    enum { ATOM, EXPR } type;
    struct Sexpr_List *val;
} Sexpr_t;

typedef struct Sexpr_Node {
    Sexpr_t *car;
    struct Sexpr_Node *cdr;
} Sexpr_Node_t;

typedef struct Sexpr_List {
    Sexpr_Node_t *head;
    Sexpr_Node_t *tail;
} Sexpr_List_t;

int isidentch(int ch);
void takeuntil(Dystr_t *buf, int *ch, int (*fp_pred)(int));
void endtok(Token_t *tok, Token_Type t, Dystr_t *buf, int ch);
void nexttok(Token_t *tok);
int consume(Token_Type t, Token_t *tok);
int expect(Token_Type t, Token_t *tok);
void sexpr(Token_t *tok);

extern FILE *PARSER_IN;

#endif