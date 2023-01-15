#include <ctype.h>
#include <err.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cell.h"
#include "compiler.h"
#include "program.h"
#include "stack.h"

#define IS_EOF(S) (*(S) == '\0')
#define IS_DELIMETER(S) (*(S) == COMPILER_DELIMETER || IS_EOF(S))

static void eatWhitespace(Compiler *);
static bool compileInstruction(Compiler *, bool);
static bool endCompilation(Compiler *, bool);

static void eatWhitespace(Compiler *c) {
  while (isblank(*c->remaining)) {
    c->remaining++;
  }
}

static bool compileInstruction(Compiler *c, bool verbose) {
  VmCell *x = NULL;
  x = nextProgramCell(&c->program, verbose);
  if (x == NULL) {
    return false;
  }
  /* Check for special instructions: ? : ; ( ) */
  /* else */
  c->remaining = parseCell(x, c->remaining);
  eatWhitespace(c);
  return true;
}

static bool endCompilation(Compiler *c, bool verbose) {
  VmCell *x = NULL;
  x = nextProgramCell(&c->program, verbose);
  if (x == NULL) {
    return false;
  }
  *x = endProgram();
  return true;
}

bool compile(Compiler *c, char *input, bool verbose) {
  resetProgramWrite(&c->program);
  c->remaining = input;
  eatWhitespace(c);
  if (IS_EOF(c->remaining) || !IS_DELIMETER(c->remaining)) {
    if (verbose) {
      warnx("programs must start with delimeter %c", COMPILER_DELIMETER);
    }
    return false;
  }
  c->remaining++;
  eatWhitespace(c);
  while (!IS_DELIMETER(c->remaining)) {
    if(!compileInstruction(c, verbose)) {
      return false;
    }
  }
  if (IS_EOF(c->remaining)) {
    if (verbose) {
      warnx("programs must end with delimeter %c", COMPILER_DELIMETER);
    }
    return false;
  }
  c->remaining++;
  return endCompilation(c, verbose);
}

Compiler compiler(void) {
  Compiler c = {0};
  c.remaining = NULL;
  c.conditions = stack();
  c.loops = stack();
  c.program = program();
  return c;
}
