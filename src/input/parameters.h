#pragma once

#include <unistd.h>

#define PARAMETERS_HEAP_SIZE (size_t)128
#define PARAMETERS_INTERPOLATION_FRAMES (size_t)256
#define PARAMETERS_MAX_DELAY (float)10.0f
#define PARAMETERS_PHASE_SIZE (size_t)16
#define PARAMETERS_SAMPLE_RATE (size_t)31250

typedef struct Parameters {
  size_t        heapSize;
  size_t        phaseSize;
  size_t        interpolationFrames;
  size_t        sampleRate;
  float         maxDelay;
} Parameters;

/* Will eventually take argc, argv as input */
Parameters parameters(void);
