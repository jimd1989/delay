#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "array.h"

float readArray(Array *a, float f) {
  size_t n = (size_t)f;
  return a->data[n % a->size];
}

void writeArray(Array *a, float n, float f) {
  size_t i = (size_t)n;
  float r = n - i;
  if (a->isTape) {
    if (f) {
      a->data[ i      % a->size] += f * r;
      a->data[(i + 1) % a->size] += f * (1.0f - r);
    } else {
      a->data[i % a->size] = 0.0f;
    }
  } else {
    a->data[i % a->size] = f;
  }
}

void killArray(Array *a) {
  free(a->data);
}

Array array(size_t size, bool isTape) {
  Array a = {0};
  a.isTape = isTape;
  a.size = size;
  a.data = calloc(size, sizeof(float));
  return a;
}
