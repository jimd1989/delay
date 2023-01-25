#include "parameters.h"

Parameters parameters(void) {
  Parameters p = {0};
  p.heapSize = PARAMETERS_HEAP_SIZE;
  p.interpolationFrames = PARAMETERS_INTERPOLATION_FRAMES;
  p.phaseSize = PARAMETERS_PHASE_SIZE;
  p.maxDelay = PARAMETERS_MAX_DELAY;
  return p;
}
