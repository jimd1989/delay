#include <ctype.h>
#include <stdint.h>

#include "cell.h"
#include "func.h"

#define IS_NUM(C) ((C) == '_' || (C) == '.' || isdigit((C)))
#define TO_INT(C) ((int)(C) - 48)

static char *numCell(VmCell *, char *);
static char *funcCell(VmCell *, char *);

static char *numCell(VmCell *c, char *s) {
  int64_t divisor = 1;
  int64_t sign = 1;
  int64_t n = 0;
  int64_t decimalPlace = 0;
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
  c->data.n = (double)(n * sign) / (double)divisor;
  return s;
}

static char *funcCell(VmCell *c, char *s) {
  if (*s == VM_EXTEND) {
    c->type = VM_CELL_EX_FUNC;
    s++;
  } else {
    c->type = VM_CELL_FUNC;
  }
  c->data.f = *s;
  return ++s;
}

char *parseCell(VmCell *c, char *s) {
  return IS_NUM(*s) ? numCell(c, s) : funcCell(c, s);
}

VmCell endProgram(void) {
  VmCell c = {0};
  c.type = VM_CELL_FUNC;
  c.data.f = VM_END;
  return c;
}

VmCell number(float f) {
  VmCell c = {0};
  c.type = VM_CELL_NUM;
  c.data.n = f;
  return c;
}

VmCell address(Array *a) {
  VmCell c = {0};
  c.type = VM_CELL_NUM;
  c.data.p = a;
  return c;
}

VmCell cell(void) {
  VmCell c = {0};
  return c;
}
