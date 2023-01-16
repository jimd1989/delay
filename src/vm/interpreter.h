#pragma once

#include "program.h"
#include "stack.h"

typedef struct Interpreter {
  Program       * program;
  Stack           stack;
} Interpreter;

float interpret(Interpreter *);
void setInterpreterProgram(Interpreter *, Program *);
Interpreter interpreter(Program *);
