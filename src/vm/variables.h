#pragma once

#include <unistd.h>

typedef struct Variables {
  float         * a;
  float         * b;
  float         * c;
  float         * delayVolume;
  float         * feedback;
  float         * sample;
  float         * sampleOld;
  float         * wet;
  size_t        * delay;
  size_t        * phase;
  size_t          tapeLength;
} Variables;

float getA(Variables *);
float getB(Variables *);
float getC(Variables *);
float getDelayVolume(Variables *);
float getFeedback(Variables *);
float getSample(Variables *);
float getSampleOld(Variables *);
float getWet(Variables *);
float getDelay(Variables *);
float getPhase(Variables *);
float getTapeLength(Variables *);
