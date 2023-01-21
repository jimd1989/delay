#pragma once

#include <unistd.h>

#include "array.h"
#include "program.h"
#include "stack.h"

#define INTERPRETER_HEAP_SIZE (size_t)128

typedef struct Interpreter {
  Program       * program;
  Stack           stack;
  Array           heap;
  Array           tape;
} Interpreter;

float interpret(Interpreter *);
void setInterpreterProgram(Interpreter *, Program *);
Interpreter interpreter(Program *, size_t, size_t);
