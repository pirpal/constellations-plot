#ifndef ASTRO_MATHS_H_
#define ASTRO_MATHS_H_

#include <stdint.h>
#include <stdio.h>

#ifndef M_PI
  #define M_PI 3.141592653
#endif

#define HOUR_DEG (360.0 / 24.0)
#define MIN_DEG  (HOUR_DEG / 60.0)
#define SEC_DEG  (MIN_DEG / 60.0)

#define deg_to_rad(d) (d * (M_PI / 180))

typedef struct HmsCoords {
  uint8_t h, m;
  float s;
} HmsCoords;

void log_hms_coords(FILE *stream,const HmsCoords *hms);

float hms_to_degrees(const HmsCoords *hms);

HmsCoords degrees_to_hms(float degrees);



#endif // ASTRO_MATHS_H_
