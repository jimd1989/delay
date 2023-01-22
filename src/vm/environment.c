#include "../input/variables.h"
#include "environment.h"

Environment environment(Variables *v) {
  Environment e = {0};
  e.chan = v->chan;
  e.rate = v->rate;
  e.a = &v->a.product;
  e.b = &v->b.product;
  e.c = &v->c.product;
  e.feedback = &v->feedback.product;
  e.pan = &v->pan.product;
  e.delayTime = &v->delayTime.product;
  e.volume = &v->volume.product;
  e.wetness = &v->wetness.product;
  e.currentSample = v->currentSample;
  e.otherSample = v->otherSample;
  return e;
}
