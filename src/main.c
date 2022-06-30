#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stars.h"
#include "astro_maths.h"

int main (void)
{
  printf("C Constellations Plotter\n");

  float deg1 = 1.0;
  float rad_deg1 = deg_to_rad(deg1);
  printf("Found %.7f rad for 1 degree\n", rad_deg1);

  HmsCoords hms;
  hms.h = 12;
  hms.m = 27;
  hms.s = 43;

  log_hms_coords(stdout, &hms);

  float hms_deg = hms_to_degrees(&hms);

  printf("12:27:43 => %.2f°\n", hms_deg);
  
  /* const char *cygnus = "Cyg"; */
  /* const float mmag = 4.0; */

  /* uint16_t nb = count_stars(cygnus, mmag); */
  /* printf("Found %d stars in '%s' with maximum magnitude of %.1f\n", */
  /* 	 nb, cygnus, mmag); */

  /* printf("Collecting stars...\n"); */
  /* Star **cygnus_stars = collect_stars(cygnus, mmag); */
  /* printf("sizeof(cygnus_stars): %d\n", sizeof(cygnus_stars)); */


  /* const char *log_file = "stars_out.log"; */
  /* FILE *stars_out = fopen(log_file, "w"); */
  /* if (stars_out == NULL) { */
  /*   fprintf(stderr, "[ERR] failed to open %s\n", log_file); */
  /*   exit(EXIT_FAILURE); */
  /* } */
  /* printf("Writing stars to %s...\n", log_file); */
  /* for (int i = 0; i < nb; ++i) { */
  /* //for (size_t i = 0; i < sizeof(cygnus_stars); ++i) { */
  /*   log_star(stars_out, cygnus_stars[i]); */
  /* } */
  /* printf("Closing %s...\n", log_file); */
  /* fclose(stars_out); */

  /* printf("Free stars collection and exit\n"); */
  /* free_stars(cygnus_stars); */
  
  return EXIT_SUCCESS;
}
