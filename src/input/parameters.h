#pragma once

#include <unistd.h>

#define PARAMETERS_INTERPOLATION_FRAMES (size_t)256
#define PARAMETERS_HEAP_SIZE (size_t)128
#define PARAMETERS_MAX_DELAY (float)10.0f

typedef struct Parameters {
  size_t        heapSize;
  size_t        interpolationFrames;
  float         maxDelay;
} Parameters;

/* Will eventually take argc, argv as input */
Parameters parameters(void);
