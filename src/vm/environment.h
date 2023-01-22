#pragma once

#include "../input/variables.h"

typedef struct Environment {
  float   chan;
  float   rate;
  float * a;
  float * b;
  float * c;
  float * feedback;
  float * pan;
  float * delayTime;
  float * volume;
  float * wetness;
  float * currentSample;
  float * otherSample;
} Environment;

Environment environment(Variables *);
