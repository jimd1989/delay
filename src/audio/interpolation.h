#pragma once

#include <unistd.h>

#define INTERPOLATION_LENGTH 32.0f
#define INTERPOLATION_INC (1.0f / INTERPOLATION_LENGTH)
#define INTERPOLATE(O, N, P) (((1.0f - P) * O) + ((1.0f - (1.0f - P)) * N))

typedef struct InterpolatedFloat {
  float phase;
  float old;
  float new;
} InterpolatedFloat;

typedef struct InterpolatedInt {
  float         phase;
  size_t        old;
  size_t        new;
} InterpolatedInt;

void setFloat(InterpolatedFloat *, float);
float getFloat(InterpolatedFloat *);
void setInt(InterpolatedInt *, size_t);
size_t getInt(InterpolatedInt *);
