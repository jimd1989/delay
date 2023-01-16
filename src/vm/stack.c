#include <err.h>

#include "cell.h"
#include "stack.h"

float *directNumber(Stack *s) {
  return s->head > 0 ? &s->data[s->head - 1].data.n : NULL;
}

VmCell popStack(Stack *s) {
  VmCell empty = {0};
  return s->head > 0 ? s->data[--s->head] : empty;
}

void pushStack(Stack *s, VmCell c) {
  if (s->head >= s->size) {
    errx(-1, "stack overflow: %u", (unsigned int)s->size);
  } else {
    s->data[s->head++] = c;
  }
}

Stack stack(void) {
  Stack s = {0};
  s.size = STACK_SIZE;
  return s;
}
