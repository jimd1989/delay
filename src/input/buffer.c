#include "buffer.h"

Buffer buffer(void) {
  Buffer b = {0};
  b.size = BUFFER_SIZE;
  b.remaining = b.data;
  return b;
}
