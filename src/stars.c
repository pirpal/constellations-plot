#include "astro_maths.h"
#include "constellations.h"
#include "greek.h"
#include "mydivutils.h"
#include "split_string.h"
#include "stars.h"

#define U_BLACK_STAR "\U00002605"  // '★'

//--------------------------------------------------------------
// Static funcitons
//--------------------------------------------------------------

static bool constel_in_line(const char *con, const char *line) {
  /*
     Build a formatted string to surround CON with commas;
     Return true if pattern ",CON," is found in line
  */
  char buf[6]; // 6 = 3 letters for CON + 2 commas + last '\0'
  snprintf(buf, 6, ",%s,", con);
  if (strstr(line, buf))
    return true;
  return false;
}


static bool has_companion_id(const char *str_id) {
  /*
    Multiple stars systems have an id field in CSV db as:
    ",12345:67890,"
    where first id is star's id, and the second one is
    the companion star's id.
    Return true if STR_ID matches this pattern
  */
  if (strchr(str_id, ':') != NULL)
    return true;
  return false;
}


static uint16_t get_star_id(const char *str_id) {
  /*
    Check if STR_ID contains a companion star's id.
    Return star's id as integer
   */
  uint16_t id;
  if (has_companion_id(str_id)) {
    char **split = new_split(str_id, ':');
    id = atoi(split[0]);
    free_split(split);
  } else {
    id = atoi(str_id);
  }
  return id;
}


//--------------------------------------------------------------
// Extern functions
//--------------------------------------------------------------
Star* new_star(char **split) {
  /*
    Return a pointer to Star* struct dynamically
    allocated with SPLIT strings array
  */
  Star *star = malloc(sizeof(Star));
  if (star == NULL)
    err_exit("new_star", "failed to malloc Star");

  star->id = get_star_id(split[ID]);

  strcpy(star->bf, split[BF]);
  star->bf[strlen(split[BF])] = '\0';

  strcpy(star->bayer, split[BAYER]);
  star->bayer[strlen(split[BAYER])] = '\0';

  strcpy(star->proper, split[PROPER]);
  star->proper[strlen(split[PROPER])] = '\0';

  strcpy(star->spect, split[SPECT]);
  star->spect[strlen(split[SPECT])] = '\0';

  strcpy(star->con, split[CON]);
  star->con[strlen(split[CON])] = '\0';

  star->ra   = atof(split[RA]);
  star->dec  = atof(split[DEC]);
  star->dist = atof(split[DIST]);
  star->mag  = atof(split[MAG]);
  star->ci   = atof(split[CI]);
  return star;
}


uint16_t count_stars(const char *con, const float max_mag) {
  /*
    Return nb of stars in database:
    - belonging to constellation CON
    - which magnitude is <= MAX_MAG
   */
  uint16_t count = 0;
  FILE *db = fopen(STARS_DB_PATH, "r");
  if (db == NULL)
    err_exit("count_stars", "failed to open db");
  char line[CSV_LINE_MAXCHAR];
  while (fgets(line, sizeof(line), db)) {
    char **split = new_split(line, SEP);
    if (strcmp(con, split[CON]) == 0) {
      float mag = atof(split[MAG]);
      if (mag <= max_mag)
	count += 1;
    }
   free_split(split);
  }
  fclose(db);
  return count;
}


Star** collect_stars(const char *con, const float max_mag) {
  /*
    Return an array of pointers to struct Star
  */
  // count amount of stars and malloc Star array:
  uint16_t stars_nb = count_stars(con, max_mag);
  Star **stars = malloc(stars_nb * sizeof(Star*));
  if (stars == NULL)
    err_exit("collect_stars", "failed to malloc Star*");

  // open db:
  FILE *db = fopen(STARS_DB_PATH, "r");
  if (db == NULL)
    err_exit("collect_stars", "failed to open db");

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
      free_split(split);
    }
  }
  fclose(db);
  return stars;
}

void log_star(FILE *log, const Star *star, const char *genitive) {
  HmsCoords* ra_hms = degrees_to_hms(star->ra);
  fprintf(log, "\n| Star    | <%p>\n", (void*) star);
  fprintf(log, "| id      | %d\n", star->id);

  if (strcmp(star->bf, "") != 0) {
    fprintf(log, "| bf      | %s\n", star->bf);
  }
  if (strcmp(star->bayer, "") != 0) {
    GreekLetter index = get_letter_index(star->bayer);
    fprintf(log, "| bayer   | %s", GREEK_STR[index]);
    fprintf(log, " %s\n", genitive);
  }
  if (strcmp(star->proper, "") != 0) {
    fprintf(log, "| proper  | %s\n", star->proper);
  }
  fprintf(log, "| RA      | ");
  log_hms_coords(log, ra_hms);
  fprintf(log, "\n");
  free(ra_hms);
  ra_hms = NULL;

  if (star->dec < 0.0) {
    fprintf(log, "| dec     | -%.5f°\n", star->dec);
  } else {
    fprintf(log, "| dec     | +%.5f°\n", star->dec);
  } 
  fprintf(log, "| dist p  | %6.2f parsecs\n", star->dist);
  fprintf(log, "| dist ly | %6.2f light years\n", star->dist * PARSECS_TO_LY);
  fprintf(log, "| mag     | %.2f\n",   star->mag);
  fprintf(log, "| ci      | %.2f\n", star->ci);
  fprintf(log, "| spect   | %s\n",   star->spect);
}


void free_stars(Star **stars) {
  for (size_t i = 0; i < sizeof(stars); ++i) {
    free(stars[i]);
  }
  free(stars);
}


