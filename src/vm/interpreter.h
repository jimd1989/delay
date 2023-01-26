#pragma once

#include "../input/variables.h"
#include "array.h"
#include "environment.h"
#include "program.h"
#include "stack.h"

typedef struct Interpreter {
  float           l;
  float           r;
  Program       * program;
  Environment     environment;
  Stack           stack;
  Array           heap;
  Array           phase;
  Array           tape;
} Interpreter;

void interpret(Interpreter *);
void setInterpreterProgram(Interpreter *, Program *);
void killInterpreter(Interpreter *);
Interpreter interpreter(Variables *, Program *);
