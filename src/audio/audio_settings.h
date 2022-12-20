#pragma once

#include <unistd.h>

typedef struct AudioSettings {
  size_t        bits;
  size_t        bufSizeBytes;
  size_t        bufSizeFrames;
  size_t        chan;
  size_t        rate;
} AudioSettings;

