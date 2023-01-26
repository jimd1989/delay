#include "cell.h"
#include "compiler.h"
#include "dsp.h"
#include "interpreter.h"
#include "test.h"

void test(void) {
  testCell();
  testCompiler();
  testDsp();
  testInterpreter();
}
