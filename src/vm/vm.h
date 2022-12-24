#pragma once

#include <unistd.h>

#include "program.h"
#include "stack.h"

typedef struct Vm {
  size_t        depth;
  size_t        head;
  Program       program;
  Stack         stack;
} Vm;
