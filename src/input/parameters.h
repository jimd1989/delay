#pragma once

#define PARAMETERS_MAX_DELAY (float)10.0f

typedef struct Parameters {
  float maxDelay;
} Parameters;

Parameters parameters(void);
