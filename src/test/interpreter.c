#include <err.h>
#include <stdbool.h>

#include "../audio/audio_settings.h"
#include "../input/parameters.h"
#include "../vm/compiler.h"
#include "../vm/interpreter.h"
#include "../vm/program.h"
#include "interpreter.h"

void testInterpreter(void) {
  AudioSettings a = {0};
  Parameters par = parameters();
  Variables v = {0};
  float f = 0.0f;
  Program p = program();
  Compiler c = compiler(&p);
  Interpreter i = {0};
  par.maxDelay = 1.0f;
  a.rate = 128;
  a.chan = 2;
  v = variables(par, a, NULL, NULL);
  i = interpreter(&v, &p);
  warnx("interpreter");
  warnx("  'T129 1.0}T1{' = 1.0f");
  compile(&c, "'T129 1.0}T1{'", false);
  f = interpret(&i);
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  'H100 .5}H101 1.5}H101{H100{-' = 1.0f");
  compile(&c, "'H100 .5}H101 1.5}H101{H100{-'", false);
  f = interpret(&i);
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  ' 8.5 _.5+2^1+3%%2*2/3-`' = 1.0f");
  compile(&c, "' 8.5 _.5+2^1+3%2*2/3-`'", false);
  f = interpret(&i);
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  '1 2 3 4 2#+2\\**27/' = 1.0f");
  compile(&c, "'1 2 3 4 2#+2\\**27/'", false);
  f = interpret(&i);
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  '9 10~-' = 1.0f");
  compile(&c, "'9 10~-'", false);
  f = interpret(&i);
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  '1 2@[1@|4@&3@^2@]' = 1.0f");
  compile(&c, "'1 2@[1@|4@&3@^2@]'", false);
  f = interpret(&i);
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  'z128/' = 1.0f");
  compile(&c, "'z128/'", false);
  f = interpret(&i);
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
}
