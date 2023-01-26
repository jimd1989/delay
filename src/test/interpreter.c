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
  warnx("  '1.0 129T}1T{1\\' = 1.0f");
  compile(&c, "'1.0 129T}1T{1\\'", false);
  interpret(&i);
  f = i.l + i.r;
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  '.5 100H}1.5 101H}101H{100H{-1\\' = 1.0f");
  compile(&c, "'.5 100H}1.5 101H}101H{100H{-1\\'", false);
  interpret(&i);
  f = i.l + i.r;
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  ' 8.5 _.5+2^1+3%%2*2/3-`1\\' = 1.0f");
  compile(&c, "' 8.5 _.5+2^1+3%2*2/3-`1\\'", false);
  interpret(&i);
  f = i.l + i.r;
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  '1 2 3 4 2#+2\\**27/1\\' = 1.0f");
  compile(&c, "'1 2 3 4 2#+2\\**27/1\\'", false);
  interpret(&i);
  f = i.l + i.r;
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  '9 10~-1\\' = 1.0f");
  compile(&c, "'9 10~-1\\'", false);
  interpret(&i);
  f = i.l + i.r;
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  '1 2@[1@|4@&3@^2@]1\\' = 1.0f");
  compile(&c, "'1 2@[1@|4@&3@^2@]1\\'", false);
  interpret(&i);
  f = i.l + i.r;
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  'z128/1\\' = 1.0f");
  compile(&c, "'z128/1\\'", false);
  interpret(&i);
  f = i.l + i.r;
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  killInterpreter(&i);
}
