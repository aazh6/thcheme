#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "parser.h"
#include "dystr.h"

FILE *PARSER_IN;
Token_t *PARSER_TOK;

int isidentch(int ch) { return isalnum(ch) || ISIDENTSYM(ch); }

void takeuntil(Dystr_t *buf, int *ch, int (*fp_pred)(int)) {
    if (buf && ch) {
        do {
            dystr_append(buf,*ch);
            *ch = getc(PARSER_IN);
        } while (fp_pred(*ch));
    }
}

void endtok(Token_t *tok, Token_Type t, Dystr_t *buf, int ch) {
    if (isspace(ch) || ch == ')' || ch == EOF) {
        tok->type = t;
        dystr_cp(&tok->val, buf);
        ungetc(ch, PARSER_IN);
    } else {
        dystr_append(buf, ch);
        fprintf(stderr, "nexttok: unrecognized token \"%s\"\n", buf->val);
        exit(1);
    }
}

void nexttok(Token_t *tok) {
    int ch = getc(PARSER_IN);

    switch (ch) {
        case EOF:
            tok->type = END;
            tok->val = NULL;
            break;
        case '(':
            
            tok->type = LPAREN;
            tok->val = NULL;
            break;
        case ')':
            tok->type = RPAREN;
            tok->val = NULL;
            break;
        default:
            if (isspace(ch)) {
                Dystr_t *buf;
                init_dystr(&buf);
                takeuntil(buf, &ch, isspace);
                tok->type = WHITESPACE;
                tok->val = NULL;
                ungetc(ch, PARSER_IN);
                destroy_dystr(&buf);
            } else if (isdigit(ch)) {
                Dystr_t *buf;
                init_dystr(&buf);
                takeuntil(buf, &ch, isdigit);
                if (ch == '.') 
                    takeuntil(buf, &ch, isdigit);
                endtok(tok, NUMBER, buf, ch);
                destroy_dystr(&buf);
            } else if (isalpha(ch) || ISIDENTSYM(ch)) {
                Dystr_t *buf;
                init_dystr(&buf);
                takeuntil(buf, &ch, isidentch);
                endtok(tok, IDENT, buf, ch);
                destroy_dystr(&buf);
            }
            break;
    }

    char *TOKTYPE_STR[] = { "START", "NUMBER", "IDENT", "WHITESPACE", "LPAREN", "RPAREN", "END" };
    printf("%s\n", TOKTYPE_STR[tok->type]);
}

int consume(Token_Type t, Token_t *tok) {
    if (tok->type == t) {
        nexttok(tok);
        return 1;
    }
    return 0;
}

int expect(Token_Type t, Token_t *tok) {
    if (consume(t, tok)) return 1;
    fprintf(stderr, "expect: encountered unexpected token (expected %d, got %d)\n", t, tok->type);
    return 0;
}

void sexpr(Token_t *tok) {
    if (consume(NUMBER, tok)) {
        ;
    } else if (consume(IDENT, tok)) {
        ;
    } else if (consume(LPAREN, tok)) {
        sexpr(tok);
        while (consume(WHITESPACE, tok)) {
            sexpr(tok);
        }
        expect(RPAREN, tok);
    } else {
        fprintf(stderr, "sexpr: invalid sexpr\n");
        exit(1);
    }
}
