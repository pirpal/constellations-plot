#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "astro_maths.h"
#include "constellations.h"
#include "mydivutils.h"
#include "stars.h"


int main (void)
{
  // Load constellations
  printf("Loading constellations...\n");
  Constellation **constels = load_constellations(CONSTELLATIONS_DB_PATH);
  
  // User input for desired constellation
  /* char constel_name[CONSTEL_ABBREV_MAXCHAR]; */
  /* printf("\n  Please enter IAU_ABBREV constellation name:\n > "); */
  /* fgets(constel_name, 4, stdin); */
  /* if (!is_constel_shortname(constel_name)) */
  /*   err_exit("main", "Not a valid constellation name"); */
  char *constel_name = "And";

  Constellation *selected_const;
  for (uint8_t i = 0; i < CONSTELLATIONS_NB; ++i) {
    if (strcmp(constel_name, constels[i]->shortname) == 0) {
      selected_const = constels[i];
      break;
    }
  }
  if (selected_const == NULL)
    err_exit("main", "Constellation not found");
  printf("Selected constellation: %s\n", selected_const->name);

  // User input for maxmimum magnitude
  /* float max_mag; */
  /* printf("  Please enter maximum magnitude ('6.0')\n"); */
  /* printf("  > "); */
  /* scanf("%f", &max_mag); */
  float max_mag = 4.0;

  printf("Counting stars... ");
  uint16_t stars_nb = count_stars(constel_name, max_mag);
  printf("Found %d stars in %s with magnitude <= %.2f\n",
	 stars_nb,
	 constel_name,
	 max_mag);
  
  if (stars_nb > 0) {
    // writing stars to file if any
    // opening output file
    FILE *stars_log = fopen("stars.log", "w");
    if (stars_log == NULL)
      err_exit("main", "failed to open stars.log");
                                                              
    printf("Writing stars to stars.log...\n");
    Star** stars = collect_stars(constel_name, max_mag);
    for (uint16_t i = 0; i < stars_nb; ++i) {
      log_star(stars_log, stars[i], selected_const->genitive);
    }
    free_stars(stars);
    printf("Closing stars.log...\n");
    fclose(stars_log);
  } else {
    printf("No stars found in %s for max_mag = %.2f",
	   selected_const->name,
	   max_mag);
  }
  printf("Freeing constellations...\n");
  free_constellations(constels);
                                                           
  printf("Exiting...\n");
  return EXIT_SUCCESS;
}
