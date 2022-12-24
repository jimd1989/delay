#pragma once

#include <stdbool.h>
#include <unistd.h>

#include "cell.h"

#define PROGRAM_SIZE (size_t)256

typedef struct Program {
  size_t        size;
  VmCell        data[PROGRAM_SIZE];
} Program;

bool loadProgram(Program *, char *s);
Program program(void);
