#include "cell.h"
#include "stack.h"

float *directNumber(Stack *s) {
  return s->head > 0 ? &s->data[s->head - 1].data.n : NULL;
}

VmCell popStack(Stack *s) {
  return s->head > 0 ? s->data[--s->head] : number(0.0f);
}

void pushStack(Stack *s, VmCell c) {
  if (s->head >= s->size) {
    return;
  } else {
    s->data[s->head++] = c;
  }
}

Stack stack(void) {
  Stack s = {0};
  s.size = STACK_SIZE;
  return s;
}
