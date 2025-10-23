#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Please specify a file.\n");
        return 1;
    } else {
        PARSER_IN = fopen(argv[1], "r");
        if (!PARSER_IN) {
            fprintf(stderr, "File does not exist.\n");
            return 1;
        }
        Token_t *tok = malloc(sizeof(*tok));
        NULLCHECK(tok, main);
        nexttok(tok);
        sexpr(tok);
        expect(END, tok);
        return 0;
    }
}