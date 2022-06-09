#include "csv-parsing.h"


void newline(void) {
  printf("\n");
}


#define DB_PATH "/home/peio/C/Projects/constellations-plot/db/hygdata_light.csv"

int main (void)
{
  newline();
  printf("C Constellations Plotter");
  newline();

  FILE *out_svg = fopen("out.svg", "w");
  if (out_svg == NULL)
    err_exit("failed to create new out.svg file");

  // Collect a set of stars:
  float max_mag = 2.0f;

  FILE *db = fopen(DB_PATH, "r");
  if (db == NULL)
    err_exit("failed to open DB_PATH");

  char *line = NULL;
  

  

  fclose(db);
  fclose(out_svg);
  
  newline();
  return EXIT_SUCCESS;
}
