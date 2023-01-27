#pragma once

#include <unistd.h>

typedef struct InterpolatedFloat {
  float inc;
  float phase;
  float old;
  float new;
  float product;
} InterpolatedFloat;

void setInterpolatedFloat(InterpolatedFloat *, float);
void incFloat(InterpolatedFloat *);
void setInc(InterpolatedFloat *, size_t);
InterpolatedFloat interpolatedFloat(size_t);
