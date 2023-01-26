#pragma once

#include <stdbool.h>

#include "program.h"
#include "stack.h"

#define COMPILER_DELIMETER '\''
#define COMPILER_DEFAULT_PROG "'xv*\\'"

typedef struct Compiler {
  char          * remaining;
  Program       * program;
  Stack           conditions;
  Stack           loops;
} Compiler;

bool compile(Compiler *, char *, bool);
void setCompilerProgram(Compiler *, Program *);
Compiler compiler(Program *);
