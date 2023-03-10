#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "array.h"
#include "cell.h"
#include "environment.h"
#include "func.h"
#include "interpreter.h"
#include "program.h"
#include "stack.h"

#define MONAD(N, F) static void N(Stack *s) {\
  float *f = directNumber(s);\
  if (f != NULL) {\
    *f = F(*f);\
  }\
}

#define DYAD(N, X, Y, F) static void N(Stack *s) {\
  float Y = popStack(s).data.n;\
  float X = popStack(s).data.n;\
  pushStack(s, number(F));\
}

#define DYNAMIC_VAR(N, V) static void N(Interpreter *i) {\
  pushStack(&i->stack, number(*i->environment.V));\
}

static void evaluate(Interpreter *, VmCell);
static void evaluateFunc(Interpreter *, VmCell);
static void evaluateExFunc(Interpreter *, VmCell);
static void iRead(Interpreter *);
static void iWrite(Interpreter *);
static void iAnd(Stack *);
static void iOr(Stack *);
static void iDrop(Stack *);
static void iDuplicate(Stack *);
static void iSwap(Stack *);
static void iPlus(Stack *);
static void iMinus(Stack *s);
static void iMultiply(Stack *s);
static void iDivide(Stack *s);
static void iPow(Stack *);
static void iModulo(Stack *s);
static void iAbs(Stack *s);
static void iHeap(Interpreter *i);
static void iTape(Interpreter *i);
static void iChan(Interpreter *i);
static void iRate(Interpreter *i);
static void iTapeLength(Interpreter *i);
static void iStackSize(Interpreter *i);
static void iA(Interpreter *i);
static void iB(Interpreter *i);
static void iC(Interpreter *i);
static void iFeedback(Interpreter *i);
static void iPan(Interpreter *i);
static void iDelayTime(Interpreter *i);
static void iVolume(Interpreter *i);
static void iWetness(Interpreter *i);
static void iSample(Interpreter *i);
static void iOtherSample(Interpreter *i);
static void iFloor(Stack *);
static void iCeiling(Stack *);
static void iBitwiseAnd(Stack *s);
static void iBitwiseOr(Stack *s);
static void iXor(Stack *s);
static void iShiftL(Stack *s);
static void iShiftR(Stack *s);

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
    case VM_END:
      break;
    case VM_GOTO:
      break;
    case VM_READ:
      iRead(i);
      break;
    case VM_WRITE:
      iWrite(i);
      break;
    case VM_AND:
      iAnd(&i->stack);
      break;
    case VM_OR:
      iOr(&i->stack);
      break;
    case VM_NOOP:
      break;
    case VM_DROP:
      iDrop(&i->stack);
      break;
    case VM_DUPLICATE:
      iDuplicate(&i->stack);
      break;
    case VM_SWAP:
      iSwap(&i->stack);
      break;
    case VM_PLUS:
      iPlus(&i->stack);
      break;
    case VM_MINUS:
      iMinus(&i->stack);
      break;
    case VM_MULTIPLY:
      iMultiply(&i->stack);
      break;
    case VM_DIVIDE:
      iDivide(&i->stack);
      break;
    case VM_POW:
      iPow(&i->stack);
      break;
    case VM_MODULO:
      iModulo(&i->stack);
      break;
    case VM_ABS:
      iAbs(&i->stack);
      break;
    case VM_IF:
      break;
    case VM_ELSE:
      break;
    case VM_ENDIF:
      break;
    case VM_MARK:
      break;
    case VM_RECALL:
      break;
    case VM_NOT:
      break;
    case VM_LESS:
      break;
    case VM_GREATER:
      break;
    case VM_EQUAL:
      break;
    case VM_SINE:
      break;
    case VM_VAR_A_PARAM:
      iA(i);
      break;
    case VM_VAR_B_PARAM:
      iB(i);
      break;
    case VM_VAR_C_PARAM:
      iC(i);
      break;
    case VM_VAR_FEEDBACK:
      iFeedback(i);
      break;
    case VM_VAR_HEAP:
      iHeap(i);
      break;
    case VM_VAR_TAPE_LENGTH:
      iTapeLength(i);
      break;
    case VM_VAR_CHAN:
      iChan(i);
      break;
    case VM_VAR_PAN:
      iPan(i);
      break;
    case VM_VAR_RANDOM:
      break;
    case VM_VAR_STACK_SIZE:
      iStackSize(i);
      break;
    case VM_VAR_DELAY_TIME:
      iDelayTime(i);
      break;
    case VM_VAR_TAPE:
      iTape(i);
      break;
    case VM_VAR_VOLUME:
      iVolume(i);
      break;
    case VM_VAR_WETNESS:
      iWetness(i);
      break;
    case VM_VAR_SAMPLE:
      iSample(i);
      break;
    case VM_VAR_OTHER_SAMPLE:
      iOtherSample(i);
      break;
    case VM_VAR_RATE:
      iRate(i);
      break;
  }
}

static void iRead(Interpreter *i) {
  size_t n = (size_t)popStack(&i->stack).data.n;
  Array *a = popStack(&i->stack).data.p;
  pushStack(&i->stack, number(readArray(a, n)));
}

static void iWrite(Interpreter *i) {
  float f = popStack(&i->stack).data.n;
  size_t n = (size_t)popStack(&i->stack).data.n;
  Array *a = popStack(&i->stack).data.p;
  writeArray(a, n, f);
}

DYAD(iAnd, x, y, (x && y))
DYAD(iOr, x, y, (x || y))
DYAD(iPlus, x, y, x + y)
DYAD(iMinus, x, y, x - y)
DYAD(iMultiply, x, y, x * y)
DYAD(iDivide, x, y, x / y)
DYAD(iPow, x, y, powf(x, y))
DYAD(iModulo, x, y, fmodf(x, y))
MONAD(iAbs, fabsf)

static void iDrop(Stack *s) {
  size_t n = (size_t)popStack(s).data.n;
  while (n > 0 && s->head > 0) {
    (void)popStack(s);
    n--;
  }
}

static void iDuplicate(Stack *s) {
  size_t n = (size_t)popStack(s).data.n;
  VmCell x = popStack(s);
  pushStack(s, x);
  while (n > 0) {
    pushStack(s, x);
    n--;
  }
}

static void iSwap(Stack *s) {
  VmCell y = popStack(s);
  VmCell x = popStack(s);
  pushStack(s, y);
  pushStack(s, x);
}

static void iHeap(Interpreter *i) {
  pushStack(&i->stack, address(&i->heap));
}

static void iTape(Interpreter *i) {
  pushStack(&i->stack, address(&i->tape));
}

static void iChan(Interpreter *i) {
  pushStack(&i->stack, number(i->environment.chan));
}

static void iRate(Interpreter *i) {
  pushStack(&i->stack, number(i->environment.rate));
}

static void iTapeLength(Interpreter *i) {
  pushStack(&i->stack, number(i->tape.size));
}

static void iStackSize(Interpreter *i) {
  pushStack(&i->stack, number(i->stack.head));
}

DYNAMIC_VAR(iA, a)
DYNAMIC_VAR(iB, b)
DYNAMIC_VAR(iC, c)
DYNAMIC_VAR(iFeedback, feedback)
DYNAMIC_VAR(iPan, pan)
DYNAMIC_VAR(iDelayTime, delayTime)
DYNAMIC_VAR(iVolume, volume)
DYNAMIC_VAR(iWetness, wetness)
DYNAMIC_VAR(iSample, currentSample)
DYNAMIC_VAR(iOtherSample, otherSample)

static void evaluateExFunc(Interpreter *i, VmCell x) {
  switch (x.data.g) {
    case VM_EX_LERP:
      break;
    case VM_EX_PAN:
      break;
    case VM_EX_FLOOR:
      iFloor(&i->stack);
      break;
    case VM_EX_CEILING:
      iCeiling(&i->stack);
      break;
    case VM_EX_AND:
      iBitwiseAnd(&i->stack);
      break;
    case VM_EX_OR:
      iBitwiseOr(&i->stack);
      break;
    case VM_EX_XOR:
      iXor(&i->stack);
      break;
    case VM_EX_SHIFTL:
      iShiftL(&i->stack);
      break;
    case VM_EX_SHIFTR:
      iShiftR(&i->stack);
      break;
    case VM_EX_NOT:
      break;
  }
}

MONAD(iFloor, floorf)
MONAD(iCeiling, ceilf)
DYAD(iBitwiseAnd, x, y, (int64_t)x & (int64_t)y)
DYAD(iBitwiseOr, x, y, (int64_t)x | (int64_t)y)
DYAD(iXor, x, y, (int64_t)x ^ (int64_t)y)
DYAD(iShiftL, x, y, (int64_t)x << (int64_t)y)
DYAD(iShiftR, x, y, (int64_t)x >> (int64_t)y)

float interpret(Interpreter *i) {
  VmCell *x = NULL;
  resetProgram(i->program);
  x = nextProgramCell(i->program, true);
  if (x == NULL) {
    return 0.0f;
  }
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

Interpreter interpreter(Variables *v, Program *p) {
  Interpreter i = {0};
  i.program = p;
  i.environment = environment(v);
  i.stack = stack();
  i.heap = array(v->heapSize);
  i.tape = array((size_t)(v->rate * v->maxDelay));
  return i;
}
