#include <stdio.h>
#include "constants.h"

typedef unsigned int ptr;

int entry(void);

static void print_ptr(ptr x) {
  if ((x & FX_MASK) == FX_TAG) {
    printf("%d", ((int)x) >> FX_SHIFT);
  } else if (x == BOOL_F) {
    printf("#f");
  } else if (x == BOOL_T) {
    printf("#t");
  } else if ((x & CONST_MASK) == CHAR_TAG) {
    printf("%c", ((int)x) >> CHAR_SHIFT);
  } else if (x == NIL_BITS) {
    printf("()");
  } else {
    printf("<unknown 0x%08x>", x);
  }
  printf("\n");
}

int main(void) {
  print_ptr(entry());
  return 0;
}