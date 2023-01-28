#pragma once

#include <unistd.h>

#define INTERPOLATE(O, N, P) (((1.0f - P) * O) + ((1.0f - (1.0f - P)) * N))

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
