#pragma once

#include "program.h"
#include "stack.h"

typedef struct Vm {
  Program         programA;
  Program         programB;
  Program       * program;
  Program       * programOld;
  Stack           stack;
} Vm;
