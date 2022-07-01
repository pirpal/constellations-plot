#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "stars.h"
#include "astro_maths.h"


void err_exit(const char* msg) {
  fprintf(stderr, "[ERR] %s\n", msg);
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


int main (void)
{
  print_header("\n  C Constellations Plotter");

  char constel_name[CONSTEL_ABBREV_MAXCHAR];
  printf("  Please enter IAU_ABBREV constellation name ('Cyg')\n");
  printf("  > ");
  fgets(constel_name, 4, stdin);

  float max_mag;
  printf("  Please enter maximum magnitude ('6.0')\n");
  printf("  > ");
  scanf("%f", &max_mag);
  
  clock_t t;
  // start time
  printf("  Counting stars... ");
  t = clock();
  uint16_t stars_nb = count_stars(constel_name, max_mag);
  // stop time
  t = clock() - t;
  double time_elapsed = ((double) t) / CLOCKS_PER_SEC;
  printf("\n  Found %d stars in %s with magnitude <= %.2f\n",
	 stars_nb,
	 constel_name,
	 max_mag);
  printf("  Processed in %.3f.. seconds\n", time_elapsed);

  FILE *stars_log = fopen("stars.log", "w");
  if (stars_log == NULL)
    err_exit("main(): failed to open stars.log");

  printf("  Writing stars to stars.log\n");
  Star** stars = collect_stars(constel_name, max_mag);
  for (uint16_t i = 0; i < stars_nb; ++i) {
    log_star(stars_log, stars[i]);
  }
  printf("  Closing stars.log\n");
  fclose(stars_log);
  
  
  printf("\n");
  return EXIT_SUCCESS;
}
