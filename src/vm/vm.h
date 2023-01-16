#pragma once

#include "compiler.h"
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
Vm vm(void);
