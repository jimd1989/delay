#include <err.h>
#include <string.h>

#include "../vm/cell.h"
#include "../vm/func.h"
#include "cell.h"

void testCell(void) {
  VmCell c = cell();
  char *s = "";
  warnx("cell");
  warnx("  parses '1001' correctly");
  c = cell();
  s = parseCell(&c, "1001");
  if (c.data.n != 1001.0f) {
    warnx("     ! expected 1001.0f; got %f", c.data.n);
  }
  warnx("  parses '1001+' correctly");
  c = cell();
  s = parseCell(&c, "1001+");
  if (c.data.n != 1001.0f) {
    warnx("     ! expected 1001.0f; got %f", c.data.n);
  }
  if (strcmp(s, "+") != 0) {
    warnx("     ! expected remaining input '+'; got %s", s);
  } 
  warnx("  parses '_1001.0' correctly");
  c = cell();
  s = parseCell(&c, "_1001");
  if (c.data.n != -1001.0f) {
    warnx("     ! expected -1001.0f; got %f", c.data.n);
  }
  warnx("  parses '1001.000005' correctly");
  c = cell();
  s = parseCell(&c, "_1001.000005");
  if (c.data.n != -1001.000005f) {
    warnx("     ! expected -1001.000005f; got %f", c.data.n);
  }
  warnx("  parses '.005' correctly");
  c = cell();
  s = parseCell(&c, ".005");
  if (c.data.n != 0.005f) {
    warnx("     ! expected 0.005f; got %f", c.data.n);
  }
  warnx("  cuts off '_1001.0000005'");
  c = cell();
  s = parseCell(&c, "_1001.0000005");
  if (c.data.n != -1001.0f) {
    warnx("     ! expected -1001.0f; got %f", c.data.n);
  }
  warnx("  parses one function from '\\+=?'");
  c = cell();
  s = parseCell(&c, "\\+=?");
  if (c.data.f != VM_DUPLICATE) {
    warnx("     ! expected duplicate function; got %d", c.data.f);
  }
  if (strcmp(s, "+=?") != 0) {
    warnx("     ! expected remaining input '+=?'; got %s", s);
  } 
}
