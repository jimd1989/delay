#pragma once

#include <stdbool.h>

#include "program.h"
#include "stack.h"

#define COMPILER_DELIMETER '\''
#define COMPILER_DEFAULT_PROGZ "'0P{2\\lt-+T{1\\1P}f*x+~T}1+0P}1P{0.5*x0.5*+v*1\\'"
#define COMPILER_DEFAULT_PROGX "'0P{2\\lt-+T{~x~T}~1+%l0P}v*1\\'"
#define COMPILER_DEFAULT_PROGY "'0P{lt-+T{x0P{T}0P{1+l%0P}f*v*1\\'"

#define COMPILER_DEFAULT_PROG "'0P{1+l%3\\0P}T{f*x+~t+T}T{0.5*x0.5*+v*1\\'"

typedef struct Compiler {
  char          * remaining;
  Program       * program;
  Stack           conditions;
  Stack           loops;
} Compiler;

bool compile(Compiler *, char *, bool);
void setCompilerProgram(Compiler *, Program *);
Compiler compiler(Program *);
