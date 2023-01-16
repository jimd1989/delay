#include <math.h>
#include <stdbool.h>

#include "cell.h"
#include "func.h"
#include "interpreter.h"
#include "program.h"
#include "stack.h"

static void evaluate(Interpreter *, VmCell);
static void evaluateFunc(Interpreter *, VmCell);
static void evaluateExFunc(Interpreter *, VmCell);
static void iPlus(Stack *);
static void iFloor(Stack *);
static void iCeiling(Stack *);

static void evaluate(Interpreter *i, VmCell x) {
  switch (x.type) {
    case VM_CELL_NUM:
      pushStack(&i->stack, x);
      break;
    case VM_CELL_FUNC:
      evaluateFunc(i, x);
      break;
    case VM_CELL_EX_FUNC:
      evaluateExFunc(i, x);
      break;
    case VM_CELL_EMPTY:
      break;
  }
}

static void evaluateFunc(Interpreter *i, VmCell x) {
  switch (x.data.f) {
    case VM_PLUS:
      iPlus(&i->stack);
  }
}

static void evaluateExFunc(Interpreter *i, VmCell x) {
  switch (x.data.g) {
    case VM_EX_FLOOR:
      iFloor(&i->stack);
      break;
    case VM_EX_CEILING:
      iCeiling(&i->stack);
      break;
  }
}

static void iPlus(Stack *s) {
  float x = popStack(s).data.n;
  float y = popStack(s).data.n;
  pushStack(s, number(x + y));
}

static void iFloor(Stack *s) {
  float *f = directNumber(s);
  if (f != NULL) {
    *f = floorf(*f);
  }
}

static void iCeiling(Stack *s) {
  float *f = directNumber(s);
  if (f != NULL) {
    *f = ceilf(*f);
  }
}

float interpret(Interpreter *i) {
  VmCell *x = i->program->data;
  resetProgram(i->program);
  while (!(x->type == VM_CELL_FUNC && x->data.f == VM_END)) {
    evaluate(i, *x);
    x = nextProgramCell(i->program, true);
    if (x == NULL) {
      return 0.0f;
    }
  }
  return popStack(&i->stack).data.n;
}

void setInterpreterProgram(Interpreter *i, Program *p) {
  i->program = p;
}

Interpreter interpreter(Program *p) {
  Interpreter i = {0};
  i.program = p;
  i.stack = stack();
  return i;
}
