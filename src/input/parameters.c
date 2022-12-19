#include "parameters.h"

Parameters parameters(void) {
  Parameters p = {0};
  p.maxDelay = PARAMETERS_MAX_DELAY;
  return p;
}
