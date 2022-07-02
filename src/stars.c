#include "astro_maths.h"
#include "constellations.h"
#include "greek.h"
#include "mydivutils.h"
#include "split_string.h"
#include "stars.h"
//#include <stdbool.h>

#define U_BLACK_STAR "\U00002605"  // '★'

//--------------------------------------------------------------
// Static funcitons
//--------------------------------------------------------------

static bool constel_in_line(const char *con, const char *line) {
  /*
     Build a formatted string to surround CON with commas;
     Return true if pattern ",CON," is found in LINE */
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
  /*
    Return a pointer to Star* struct dynamically
    allocated with SPLIT

  */
  Star *star = malloc(sizeof(Star));
  if (star == NULL)
    err_exit("new_star", "failed to malloc Star");

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
   free_split(split, STARS_DB_FIELDS_NB);
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
      free_split(split, STARS_DB_FIELDS_NB);
    }
  }
  fclose(db);
  return stars;
}

void log_star(FILE *stream, const Star *star) {
  
  /* 
     <Star 0x012abc> 66 Alpha Geminorum, Castor, Gemini
     RA: 
     36744,66Alp Gem,Alp,Castor,A2Vm,Gem,7.576634,31.888276,15.5958,1.580,0.034
  */
  HmsCoords* ra_hms = degrees_to_hms(star->ra);
  // print greek letter if any (star->bayer)
  fprintf(stream, "\n\n| Star    | <%p>", (void*) star);
  fprintf(stream, "\n| id      | %d", star->id);

  if (strcmp(star->bayer, "") != 0) {
    uint8_t index = get_letter_index(star->bayer);
    fprintf(stream,
	    "\n| bayer   | %s %ld",
	    star->bayer, U_GREEK_LETTERS[index]);
  }
  fprintf(stream, "\n| RA      | ");
  log_hms_coords(stream, ra_hms);
  fprintf(stream, ", %.5f", star->ra);
  free(ra_hms);
  ra_hms = NULL;

  if (star->dec < 0.0) {
    fprintf(stream, "\n| dec     | %.5f°", star->dec);
  } else {
    fprintf(stream, "\n| dec     | +%.5f°", star->dec);
  } 

  fprintf(stream, "\n| dist p  | %.2f parsecs", star->dist);
  fprintf(stream,
	  "\n| dist ly | %.2f light years",
	  star->dist * PARSECS_TO_LY);
  fprintf(stream, "\n| mag     | %.2f",   star->mag);
  fprintf(stream, "\n| ci      | %.2f", star->ci);
  fprintf(stream, "\n| spect   | '%s'",   star->spect);
  fprintf(stream, "\n");
}


void free_stars(Star** stars_array) {
  for (size_t i = 0; i < sizeof(stars_array); ++i) {
    free(stars_array[i]);
  }
  free(stars_array);
}


/* void print_greek_bayer(FILE* stream, const Star *star) { */
/*     fprintf(stream, ""); */
/* } */
