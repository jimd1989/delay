#include <stdlib.h>
#include <unistd.h>

#include "array.h"

float readArray(Array *a, size_t n) {
  return a->data[n % a->size];
}

void writeArray(Array *a, size_t n, float f) {
  a->data[n % a->size] = f;
}

Array array(size_t size) {
  Array a = {0};
  a.size = size;
  a.data = calloc(size, sizeof(float));
  return a;
}
