#include <ctype.h>

#include "cell.h"

#define IS_NUM(C) ((C) == '_' || (C) == '.' || isdigit((C)))
#define TO_INT(C) ((int)(C) - 48)

static char *numCell(VmCell *, char *);
static char *funcCell(VmCell *, char *);

static char *numCell(VmCell *c, char *s) {
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

static char *funcCell(VmCell *c, char *s) {
  c->type = VM_CELL_FUNC;
  c->data.f = *s;
  return ++s;
}

char *parseCell(VmCell *c, char *s) {
  return IS_NUM(*s) ? numCell(c, s) : funcCell(c, s);
}

VmCell cell(void) {
  VmCell c = {0};
  return c;
}
