#pragma once

#include "../input/variables.h"
#include "array.h"
#include "environment.h"
#include "program.h"
#include "stack.h"

typedef struct Interpreter {
  Program       * program;
  Environment     environment;
  Stack           stack;
  Array           heap;
  Array           tape;
} Interpreter;

float interpret(Interpreter *);
void setInterpreterProgram(Interpreter *, Program *);
Interpreter interpreter(Variables *, Program *);
