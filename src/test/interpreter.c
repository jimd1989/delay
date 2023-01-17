#include <err.h>
#include <stdbool.h>

#include "../vm/compiler.h"
#include "../vm/interpreter.h"
#include "../vm/program.h"
#include "interpreter.h"

void testInterpreter(void) {
  float f = 0.0f;
  Program p = program();
  Compiler c = compiler(&p);
  Interpreter i = interpreter(&p);
  warnx("interpreter");
  warnx("  '1 2@[1@|4@&3@^2@]' = 1.0f");
  compile(&c, "'1 2@[1@|4@&3@^2@]'", false);
  f = interpret(&i);
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  ' 8.5 _.5+3%%2*2/3-`' = 1.0f");
  compile(&c, "' 8.5 _.5+3%2*2/3-`'", false);
  f = interpret(&i);
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
}
