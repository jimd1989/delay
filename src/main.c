#include "input/parameters.h"
#include "input/repl.h"

int main(void) {
  Parameters p = parameters();
  repl(p);
  return 0;
}
