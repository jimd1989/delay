#pragma once

#include <stdbool.h>
#include <unistd.h>

typedef struct Array {
  bool            isTape;
  size_t          size;
  float         * data;
} Array;

float readArray(Array *, float);
void writeArray(Array *, float, float);
void killArray(Array *);
Array array(size_t, bool);
