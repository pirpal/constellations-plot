#include "stars.h"
#include "split_string.h"
#include <stdbool.h>

//--------------------------------------------------------------
// Static funcitons
//--------------------------------------------------------------
static void err_exit(const char *msg) {
  fprintf(stderr, "[ERR] %s\n",msg);
  exit(EXIT_FAILURE);
}


static bool constel_in_line(const char *con, const char *line) {
  /* Returns true if the pattern ',CON,' is found in LINE */
  // build a formatted string to surround CON with commas:
  char buf[6]; // 6 = 3 letters for CON + 2 commas + last '\0'
  snprintf(buf, 6, ",%s,", con);
  if (strstr(line, buf))
    return true;
  return false;
}


static bool has_companion_id(const char *str_id) {
  /*
    Multiple stars systems have an id of the form '12345:67890',
    where first id is star's id, and the second one is the 
    companion star's id.
    Returns true if STR_ID matches this pattern
  */
  if (strchr(str_id, ':') != NULL)
    return true;
  return false;
}


static uint16_t get_star_id(const char *str_id) {
  /*
    Checks if STR_ID contains a companion star's id.
    Returns star's id as integer
   */
  uint16_t id;
  if (has_companion_id(str_id)) {
    char **split = new_split(str_id, ':');
    id = atoi(split[0]);
    free_split(split, 2);
  } else {
    id = atoi(str_id);
  }
  return id;
}


//--------------------------------------------------------------
// Extern functions
//--------------------------------------------------------------
Star* new_star(char **split) {
  /* Returns a pointer to a dynamically allocated Star struct */
  Star *star = malloc(sizeof(Star));
  if (star == NULL)
    err_exit("new_star(): failed to malloc Star");
  star->id = get_star_id(split[ID]);
  strcpy(star->bf,     split[BF]);
  strcpy(star->bayer,  split[BAYER]);
  strcpy(star->proper, split[PROPER]);
  strcpy(star->spect,  split[SPECT]);
  strcpy(star->con,    split[CON]);
  star->ra   = atof(split[RA]);
  star->dec  = atof(split[DEC]);
  star->dist = atof(split[DIST]);
  star->mag  = atof(split[MAG]);
  star->ci   = atof(split[CI]);
  return star;
}


uint16_t count_stars(const char *con, const float max_mag) {
  /*
    Returns nb of stars in database:
    - belonging to constellation CON
    - which magnitude is <= MAX_MAG
   */
  uint16_t count = 0;
  FILE *db = fopen(STARS_DB_PATH, "r");
  if (db == NULL)
    err_exit("count_stars(): failed to open db");
  char line[CSV_LINE_MAXCHAR];
  while (fgets(line, sizeof(line), db)) {
    char **split = new_split(line, SEP);
    if (strcmp(con, split[CON]) == 0) {
      float mag = atof(split[MAG]);
      if (mag <= max_mag)
	count += 1;
    }
   free_split(split, STARS_DB_FIELDS_NB);
  }
  fclose(db);
  return count;
}


Star** collect_stars(const char *con, const float max_mag) {
  /* Returns an array of pointers to struct Star */
  // count amount of stars and malloc Star array:
  uint16_t stars_nb = count_stars(con, max_mag);
  Star **stars = malloc(stars_nb * sizeof(Star*));
  if (stars == NULL)
    err_exit("collect_stars(): failed to malloc Star*");
  // open db:
  FILE *db = fopen(STARS_DB_PATH, "r");
  if (db == NULL)
    err_exit("collect_stars(): failed to open db");
  char line[CSV_LINE_MAXCHAR];
  bool header_passed = false;
  uint16_t stars_count = 0;
  while (fgets(line, sizeof(line), db)) {
    // skip first line (CSV headers):
    if (!header_passed) {
      header_passed = true;
      continue;
    }
    // find constellation in line:
    if (constel_in_line(con, line)) {
      char **split = new_split(line, SEP);
      // find mag
      if (atof(split[MAG]) <= max_mag) {
	stars[stars_count] = new_star(split);
	stars_count += 1;                   	
      }
      free_split(split, STARS_DB_FIELDS_NB);
    }
  }
  fclose(db);
  return stars;
}

void log_star(FILE *stream, const Star *star) {
  fprintf(stream, "\n<Star %p> bf: '%s', proper: '%s', con: '%s')\n",
	  (void*) star, star->bf, star->proper, star->con);
  fprintf(stream, "RA:  %8.5f\nDEC: %8.5f\n",
	  star->ra, star->dec);
  fprintf(stream, "DIST: %.2f parsecs, %.2f light years\n",
	  star->dist, star->dist * PARSECS_TO_LY);
  fprintf(stream, "MAG: %.2f, CI: %.2f, SPECT: '%s'\n",
	  star->mag, star->ci, star->spect);
}


void free_stars(Star** stars_array) {
  for (size_t i = 0; i < sizeof(stars_array); ++i) {
    free(stars_array[i]);
  }
  free(stars_array);
}
