#include "input/parameters.h"
#include "input/repl.h"

#ifdef TEST
  #include "test/test.h"
#endif

int main(void) {
  #ifdef TEST
    test();
  #else
    Parameters p = parameters();
    repl(p);
  #endif
  return 0;
}
