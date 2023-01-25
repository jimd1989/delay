#pragma once

#include "../input/variables.h"
#include "compiler.h"
#include "interpreter.h"
#include "program.h"

typedef struct Vm {
  Program       * program;
  Program       * programOld;
  Interpreter     interpreter;
  Compiler        compiler;
  Program         programA;
  Program         programB;
} Vm;

void setVmProgram(Vm *, char *);
void killVm(Vm *);
Vm vm(Variables *);
