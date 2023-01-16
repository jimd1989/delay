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
  warnx("  interprets ' 1.5 _.4+'");
  compile(&c, "' 1.5 _.4+'", true);
  f = interpret(&i);
  if (f != 1.1f) {
    warnx("     ! expected 1.1f; got %f", f);
  }
}
