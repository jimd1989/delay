#pragma once

#include <unistd.h>

/* Orphan code for now. May be a nice abstraction later. */

#define BUFFER_SIZE (size_t)4096

typedef struct Buffer {
  size_t          len;
  size_t          size;
  char          * remaining;
  char            data[BUFFER_SIZE];
} Buffer;

Buffer buffer(void);
