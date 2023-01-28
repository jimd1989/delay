#include <stdlib.h>
#include <unistd.h>

#include "../input/interpolation.h"
#include "array.h"

float readArray(Array *a, float f) {
  size_t n = (size_t)f;
  float r = f - n;
  float x = a->data[n     % a->size];
  float y = a->data[(n+1) % a->size];
  return INTERPOLATE(x, y, r);
}

void writeArray(Array *a, size_t n, float f) {
  a->data[n % a->size] = f;
}

void killArray(Array *a) {
  free(a->data);
}

Array array(size_t size) {
  Array a = {0};
  a.size = size;
  a.data = calloc(size, sizeof(float));
  return a;
}
