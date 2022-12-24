#pragma once

#include <unistd.h>

#include "variables.h"

typedef struct Evaluation {
  size_t           depth;
  size_t           head;
  Program       ** program;
  Stack         *  stack;
  Variables        env;
} Evaluation;
