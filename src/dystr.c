#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dystr.h"

void init_dystr(Dystr_t **dystr) {
    if (dystr) {
        *dystr = malloc(sizeof(*dystr));
        NULLCHECK(*dystr, init_dystr);
        (*dystr)->len = 0;
        (*dystr)->cap = DEFAULT_CAP;
        (*dystr)->val = malloc(DEFAULT_CAP + 1);
        NULLCHECK((*dystr)->val, init_dystr);
        (*dystr)->val[0] = '\0';
    }
}

void dystr_append(Dystr_t *dystr, const char ch) {
    if (dystr) {
        if (dystr->len >= dystr->cap) {
            dystr->cap *= 2;
            dystr->val = realloc(dystr->val, dystr->cap + 1);
            NULLCHECK(dystr->val, dystr_append);
        }

        dystr->val[dystr->len++] = ch;
        dystr->val[dystr->len] = '\0';
    }
}

void dystr_cp(char **buf, const Dystr_t *dystr) {
    if (buf && dystr) {
        *buf = malloc(dystr->len + 1);
        NULLCHECK(*buf, cp_dystr);
        strcpy(*buf, dystr->val);
    }
}

void destroy_dystr(Dystr_t **dystr) {
    if (dystr && *dystr) {
        free((*dystr)->val);
        free(*dystr);
        *dystr = NULL;
    }
}
