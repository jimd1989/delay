#include <err.h>

#include "../vm/program.h"
#include "cell.h"
#include "program.h"

void testProgram(void) {
  Program p = program();
  warnx("program");
  warnx("  parses ' _1 2.0001 +1>?'");
  if (!loadProgram(&p, " _1 2.0001 +1>=\n ")) {
    warnx("     ! expected program to load, but it failed");
  }
  if (p.size != 6) {
    warnx("     ! expected program length 6; got %u", (unsigned int)p.size);
  }
  if (p.data[0].type != VM_CELL_NUM || p.data[0].data.n != -1.0f) {
    warnx("     ! expected 1st value of -1.0f; got %f", p.data[0].data.n);
  }
  if (p.data[1].type != VM_CELL_NUM || p.data[1].data.n != 2.0001f) {
    warnx("     ! expected 2nd value of 2.0001f; got %f", p.data[1].data.n);
  }
  if (p.data[2].type != VM_CELL_FUNC || p.data[2].data.f != VM_PLUS) {
    warnx("     ! expected 3rd instruction to be +; got %d", p.data[1].data.f);
  }
  if (p.data[3].type != VM_CELL_NUM || p.data[3].data.n != 1.0f) {
    warnx("     ! expected 4th value of 1.0f; got %f", p.data[3].data.n);
  }
  if (p.data[4].type != VM_CELL_FUNC || p.data[4].data.f != VM_GREATER) {
    warnx("     ! expected 5th instruction to be >; got %d", p.data[4].data.f);
  }
  if (p.data[5].type != VM_CELL_FUNC || p.data[5].data.f != VM_EQUAL) {
    warnx("     ! expected 6th instruction to be =; got %d", p.data[5].data.f);
  }
}
