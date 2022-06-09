#ifndef STARS_H_
#define STARS_H_

#include <stdint.h>

#define STAR_MAXCHAR 32

typedef struct Star {
  uint16_t id;
  char bf[STAR_MAXCHAR];
  char bayer[STAR_MAXCHAR];
  char proper[STAR_MAXCHAR];
  char spect[STAR_MAXCHAR];
  Constellation con;
  char bf[STAR_MAXCHAR];
  float ra, dec, dist, mag, ci;
} Star;


#endif // STARS_H_
