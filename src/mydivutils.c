#include "mydivutils.h"

extern void err_exit(const char* fname, const char* msg) {
  /*
    USAGE: err_exit(stderr, "main", "failed to open file")
  */
  fprintf(stderr, "[ERR] in '%s': %s\n", fname, msg);
  exit(EXIT_FAILURE); // 1
}


extern void pchar_n(FILE* stream, const char c, uint8_t n) {
  for (uint8_t i = 0; i < n; ++i)
    fprintf(stream, "%c", c);
}
