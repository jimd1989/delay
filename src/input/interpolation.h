#pragma once

#include <unistd.h>

#define INTERPOLATION_LENGTH 256.0f
#define INTERPOLATION_INC (1.0f / INTERPOLATION_LENGTH)
#define INTERPOLATE(O, N, P) (((1.0f - P) * O) + ((1.0f - (1.0f - P)) * N))

/* DEPRECATED */
typedef struct InterpolatedFloat {
  float phase;
  float old;
  float new;
} InterpolatedFloat;

/* DEPRECATED */
typedef struct InterpolatedInt {
  float         phase;
  size_t        old;
  size_t        new;
} InterpolatedInt;

/* DEPRECATED */
void setFloat(InterpolatedFloat *, float);
float getFloat(InterpolatedFloat *);
void setInt(InterpolatedInt *, size_t);
size_t getInt(InterpolatedInt *);

/* Change struct name when all deprecated code is removed. */
typedef struct NewInterpolatedFloat {
  float inc;
  float phase;
  float old;
  float new;
  float product;
} NewInterpolatedFloat;

void setInterpolatedFloat(NewInterpolatedFloat *, float);
void incFloat(NewInterpolatedFloat *);
void setInc(NewInterpolatedFloat *, size_t);
NewInterpolatedFloat interpolatedFloat(size_t);
