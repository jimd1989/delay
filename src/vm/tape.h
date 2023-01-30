#pragma once

#include <unistd.h>

typedef struct Tape {
  size_t          size;
  float           oldDelayOffset;
  float           fadeInc;
  float           fadePhase;
  float           product;
  float         * data;
} Tape;

float ReadTape(Tape *, size_t);
void writeTape(Tape *, float, float);
void setDelay(Tape *, float, float);
void killTape(Tape *);
Tape tape(float, size_t, float);
