#ifndef STARS_H_
#define STARS_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

//--------------------------------------------------------------
// CSV database path and constants
//--------------------------------------------------------------
#define STARS_DB_PATH "/home/pirpal/C/Projects/constellations-plot/db/hyg_light.csv"
/* This is a reworked db I've rewritten from original full db;
   it contains only 11 fields, corresponding to the Star struct
   as defined in src/stars.h:
   id, bf, bayer, proper, spect, con, ra, dec, dist, mag, ci
   This lighter db is only 6.8 MB, versus 32.0 MB for the original db.
*/
#define SEP ','
#define CSV_LINE_MAXCHAR 256

typedef enum LightDbHeader {
  ID, BF, BAYER, PROPER, SPECT, CON, RA, DEC, DIST, MAG, CI
} LightDbHeader;

#define STARS_DB_FIELDS_NB 11

//--------------------------------------------------------------
// Star struct and constants
//--------------------------------------------------------------
#define STAR_MAXCHAR 32          // for Star string fields
#define CONSTEL_ABBREV_MAXCHAR 4 // 3 letters ("Cyg") + last '\0'

// for conversion of star's distance from parsecs to light years
#define PARSECS_TO_LY 3.261563

typedef struct Star {               // Example (Sirius)
  uint16_t id;                      // '32263'
  char bf[STAR_MAXCHAR];            // '9Alp CMa'
  char bayer[STAR_MAXCHAR];         // 'Alp'
  char proper[STAR_MAXCHAR];        // 'Sirius'
  char spect[STAR_MAXCHAR];         // 'A0m...'
  char con[CONSTEL_ABBREV_MAXCHAR]; // 'CMa'
  double ra, dec, dist, mag, ci;    // 6.75248, -16.71611, 2.6371, -1.440, 0.009
} Star;


//----------------------------------------------------------------
// Functions prototypes
//----------------------------------------------------------------
Star* new_star(char **split);

uint16_t count_stars(const char *con, const float max_mag);

Star** collect_stars(const char *con, const float max_mag);

void log_star(FILE *stream, const Star *star, const char *genitive);

void free_stars(Star **stars);

#endif // STARS_H_
