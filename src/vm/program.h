#pragma once

#include "cell.h"

#define PROGRAM_SIZE (size_t)256

typedef struct Program {
  size_t        size;
  VmCell        data[PROGRAM_SIZE];
} Program;