#include "variables.h"

float getA(Variables *v) {
  return *v->a;
}

float getB(Variables *v) {
  return *v->b;
}

float getC(Variables *v) {
  return *v->c;
}

float getDelayVolume(Variables *v) {
  return *v->delayVolume;
}

float getFeedback(Variables *v) {
  return *v->feedback;
}

float getSample(Variables *v) {
  return *v->sample;
}

float getSampleOld(Variables *v) {
  return *v->sampleOld;
}

float getWet(Variables *v) {
  return *v->wet;
}

float getPhase(Variables *v) {
  return (float)*v->phase;
}

float getDelay(Variables *v) {
  return (float)v->tapeLength;
}
