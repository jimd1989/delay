#pragma once

#include <stdbool.h>

#include "program.h"
#include "stack.h"

#define COMPILER_DELIMETER '\''

typedef struct Compiler {
  char          * remaining;
  Stack           conditions;
  Stack           loops;
  Program         program;
} Compiler;

bool compile(Compiler *, char *, bool);
Compiler compiler(void);
