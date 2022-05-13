#include "csv_parser.h"

#define TEST_STR "the;quick;brown;fox;jumps;over;the;lazy;dog"
#define SEP ';'

int main (void)
{
  printf("\nC Constellations\n");

  printf("\nCSV parsing tests:\n");
  printf("Test string: '%s'\n", TEST_STR);

  uint8_t sep_nb = count_sep(TEST_STR, SEP);
  uint8_t elt_nb = sep_nb + 1;

  printf("\nSeparators indexes:\n");
  uint8_t *indexes = sep_indexes(TEST_STR, SEP);
  for (uint8_t i = 0; i < sep_nb; ++i) {
    printf("[%d] %d\n", i, indexes[i]);
  }
  free(indexes);

  
  printf("\nTokens lengths\n");
  uint8_t *lengths = elt_lengths(TEST_STR, SEP);
  for (uint8_t i = 0; i < elt_nb; ++i) {
    printf("[%d] %d\n", i, lengths[i]);
  }
  free(lengths);

  printf("\nTokens:\n");
  char **line = new_csv_line(TEST_STR, SEP);
  for (uint8_t i = 0; i < elt_nb; ++i) {
    printf("[%d] '%s'\n", i, line[i]);
  }

  // FREE
  for (uint8_t i = 0; i < elt_nb; ++i) {
    free(line[i]);
  }
  free(line);
  
  printf("\n");
  return EXIT_SUCCESS;
}
