#pragma once

#include <unistd.h>

#include "audio_settings.h"

typedef struct DelayBuffer {
  size_t          delay;
  size_t          phase;
  size_t          size;
  float           feedback;
  float           pan;
  float           volume;
  float           wet;
  float         * data;
} DelayBuffer;

typedef struct Delay {
  float         lSample;
  float         rSample;
  DelayBuffer   left;
  DelayBuffer   right;
} Delay;

Delay delay(AudioSettings, float);
void mixDelay(Delay *, float, float);
void killDelay(Delay);
