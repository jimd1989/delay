#pragma once

#include <unistd.h>

#include "../audio/audio.h"
#include "parameters.h"
#include "variables.h"

#define REPL_LINE_SIZE (size_t)4906

typedef struct Repl {
  Variables     lVariables;
  Variables     rVariables;
  Audio         audio;
  char          line[REPL_LINE_SIZE];
} Repl;

void repl(Parameters);
