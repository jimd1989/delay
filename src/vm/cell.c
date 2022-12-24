#include "cell.h"

#include <ctype.h>

#define IS_NUM(C) ((C) == '_' || (C) == '.' || isdigit((C)))
#define TO_INT(C) ((int)(C) - 48)

char *numCell(char *s, VmCell *c) {
  int divisor = 1;
  int sign = 1;
  int n = 0;
  int decimalPlace = 0;
  while (IS_NUM(*s) && decimalPlace < 6) {
    if (*s == '_') {
      sign = -1;
    } else if (*s == '.') {
      decimalPlace = 1;
    } else {
      n *= 10;
      n += TO_INT(*s);
      if (decimalPlace) {
        divisor *= 10;
        decimalPlace++;
      }
    }
    s++;
  }
  c->type = VM_CELL_NUM;
  c->data.n = (float)(n * sign) / (float)divisor;
  return s;
}

VmCell cell(void) {
  VmCell c = {0};
  return c;
}
