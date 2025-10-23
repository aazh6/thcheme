#ifndef _DYSTR_H
#define _DYSTR_H

#define DEFAULT_CAP 10
#define NULLCHECK(ptr, fun) if (!(ptr)) { fprintf(stderr, "%s: out of memory\n", #fun); exit(1); }

typedef struct {
    unsigned int len;
    unsigned int cap;
    char *val;
} Dystr_t;

void init_dystr(Dystr_t **dystr);
void dystr_append(Dystr_t *dystr, const char ch);
void dystr_cp(char **buf, const Dystr_t *dystr);
void destroy_dystr(Dystr_t **dystr);

#endif