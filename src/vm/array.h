#pragma once

#include <unistd.h>

typedef struct Array {
  size_t          size;
  float         * data;
} Array;

float readArray(Array *, size_t);
void writeArray(Array *, size_t, float);
void killArray(Array *);
Array array(size_t);
