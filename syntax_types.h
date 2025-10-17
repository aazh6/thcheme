#include <stdio.h>

/* Immediates */
enum Imm_Type {
    FIXNUM, BOOL, CHAR, NIL
};

struct Imm {
    enum Imm_Type type;
    u_int32_t val;
};

/* Expressions */
struct Expr;

enum Expr_Type {
    IMM, PRIMCALL
};

struct Primcall {
    struct Expr *prim;
    struct Expr **args;
    u_int32_t arity;
};

struct Expr {
    enum Expr_Type type;
    union {
        struct Imm *imm;
        struct Primcall *primcall;
    } val;
};