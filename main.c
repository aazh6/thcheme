#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "constants.h"
#include "syntax_types.h"

bool valid_fixnum(u_int32_t x) {
    int bits = WORD_SIZE * 8 - FX_SHIFT;
    int lower =  -pow(2, bits - 1);
    int upper = pow(2, bits - 1) - 1;
    int s_x = (int)x;

    return lower <= s_x && s_x <= upper;
}

u_int32_t immediate_rep(struct Imm *imm) {
    switch (imm->type) {
        case FIXNUM:
            return valid_fixnum(imm->val) ? imm->val << FX_SHIFT : -1;
        case BOOL:
            return imm->val ? BOOL_T : BOOL_F;
        case CHAR:
            return isascii(imm->val) ? (imm->val << CHAR_SHIFT) + CHAR_TAG : -1;
        case NIL:
            return NIL_BITS;
        default:
            return -1;
    }
}

void emit_imm(FILE *out, struct Imm *imm) {
    u_int32_t res = immediate_rep(imm);
    if (res != -1) {
        fprintf(stderr, "\tmov\tw0, #%d", res);
    } else {
        fprintf(stderr, "Cannot find valid representation for immediate value: %X\n", imm->val);
        exit(1);
    }
}

void emit_primcall(FILE *out, struct Primcall *primcall) {
    
}

void emit_expr(FILE *out, u_int32_t stack_index, struct Expr *expr) {
    switch (expr->type) {
        case IMM:
            emit_imm(out, expr->val.imm);
            break;
        case PRIMCALL:
            emit_primcall(out, expr->val.primcall);
            break;
        default:
            fputs(stderr, "Invalid expression type\n");
            exit(1);
    }
}

int main(int argc, char* argv[]) {
    FILE *out = fopen("assembly.s", "w");

    // Header
    fputs(out, "\t.section\t__TEXT,__text,regular,pure_instructions\n");
    fputs(out, "\t.build_version macos, 15, 0\tsdk_version 15, 5\n");
    fputs(out, "\t.globl _entry\n");
    fputs(out, "\t.p2align\t2\n");
    fputs(out, "_entry:\n");

    // Expression
    

    // Footer
    fputs(out, "\tret\n");
    fputs(out, ".subsections_via_symbols\n");

    fclose(out);
    return 0;
}