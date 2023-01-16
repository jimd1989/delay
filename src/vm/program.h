#pragma once

#include <stdbool.h>
#include <unistd.h>

#include "cell.h"

#define PROGRAM_SIZE (size_t)256

typedef struct Program {
  size_t        head;
  size_t        size;
  VmCell        data[PROGRAM_SIZE];
} Program;

void resetProgram(Program *);
VmCell *nextProgramCell(Program *, bool);
Program program(void);
