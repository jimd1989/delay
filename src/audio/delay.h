#pragma once

#include <unistd.h>

#include "audio_settings.h"

typedef struct DelayBuffer {
  size_t          delay;
  size_t          phase;
  size_t          size;
  float           feedback;
  float           volume;
  float         * data;
} DelayBuffer;

typedef struct Delay {
  DelayBuffer     left;
  DelayBuffer     right;
  float         * output;
} Delay;

Delay delay(AudioSettings, float);
