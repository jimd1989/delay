#include <err.h>

#include <stdbool.h>

#include "../vm/compiler.h"
#include "../vm/func.h"
#include "../vm/program.h"
#include "compiler.h"

void testCompiler(void) {
  int n = 0;
  float f = 0.0f;
  Program p = program();
  Compiler c = compiler(&p);
  warnx("compiler");
  warnx("  fails with no opening quote");
  if (compile(&c, "   +'", false)) {
    warnx("     ! compilation succeeded at %s", c.remaining);
  }
  warnx("  fails with no ending quote");
  if (compile(&c, "   '+", false)) {
    warnx("     ! compilation succeeded at %s", c.remaining);
  }
  warnx("  does nothing with empty input");
  if (!compile(&c, "   '   '   ", false)) {
    warnx("     ! compilation failed at %s", c.remaining);
  }
  warnx("  compiles simple program '1.5 2+' correctly");
  if (!compile(&c, "'1.5 2+'", false)) {
    warnx("     ! compilation failed at %s", c.remaining);
  }
  if (c.program->data[0].type != VM_CELL_NUM) {
    warnx("     ! expected number as first instruction");
  }
  if (c.program->data[1].type != VM_CELL_NUM) {
    warnx("     ! expected number as second instruction");
  }
  if (c.program->data[2].type != VM_CELL_FUNC) {
    warnx("     ! expected function as third instruction");
  }
  if (c.program->data[3].type != VM_CELL_FUNC) {
    warnx("     ! expected function as fourth instruction");
  }
  f = c.program->data[0].data.n;
  if (f != 1.5f) {
    warnx("     ! expected 1.5 as first value, got %f", f);
  }
  f = c.program->data[1].data.n;
  if (f != 2.0f) {
    warnx("     ! expected 2.0 as second value, got %f", f);
  }
  n = c.program->data[2].data.f;
  if (n != VM_PLUS) {
    warnx("     ! expected VM_PLUS as third value, got %d", n);
  }
  n = c.program->data[3].data.f;
  if (n != VM_END) {
    warnx("     ! expected VM_END as final value, got %d", n);
  }
  if (*c.remaining != '\0') {
    warnx("     ! expected all input to be read, got %s", c.remaining);
  }
}

