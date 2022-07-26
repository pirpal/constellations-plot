#include "mydivutils.h"
#include <string.h>

extern void err_exit(const char* fname, const char* msg) {
  /*
    USAGE: err_exit("main", "failed to open file")
  */
  fprintf(stderr, "[ERR] in '%s': %s\n", fname, msg);
  exit(EXIT_FAILURE); // 1
}


extern void pchar_n(FILE* stream, const char c, uint8_t n) {
  for (uint8_t i = 0; i < n; ++i)
    fprintf(stream, "%c", c);
}


void print_header(const char* header) {
  printf(" ");
  for (size_t i = 0; i < strlen(header) + 4; ++i)
    printf("-");
  printf(" \n  %s\n", header);
  printf(" ");

  for (size_t i = 0; i < strlen(header) + 4; ++i)
    printf("-");
  printf(" \n");
}
