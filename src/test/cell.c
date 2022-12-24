#include <err.h>
#include <string.h>

#include "../vm/cell.h"
#include "cell.h"

void testCell(void) {
  VmCell c = cell();
  char *s = "";
  warnx("cell");
  warnx("  parses '1001' correctly");
  c = cell();
  s = numCell("1001", &c);
  if (c.data.n != 1001.0f) {
    warnx("     ! expected 1001.0f; got %f", c.data.n);
  }
  warnx("  parses '1001+' correctly");
  c = cell();
  s = numCell("1001+", &c);
  if (c.data.n != 1001.0f) {
    warnx("     ! expected 1001.0f; got %f", c.data.n);
  }
  if (strcmp(s, "+") != 0) {
    warnx("     ! expected remaining input '+'; got %s", s);
  } 
  warnx("  parses '_1001.0' correctly");
  c = cell();
  s = numCell("_1001", &c);
  if (c.data.n != -1001.0f) {
    warnx("     ! expected -1001.0f; got %f", c.data.n);
  }
  warnx("  parses '1001.000005' correctly");
  c = cell();
  s = numCell("_1001.000005", &c);
  if (c.data.n != -1001.000005f) {
    warnx("     ! expected -1001.000005f; got %f", c.data.n);
  }
}
