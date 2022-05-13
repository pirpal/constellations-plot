#ifndef ASTRO_MATHS_H_
#define ASTRO_MATHS_H_


typedef struct CelestialCoords {
  float ra, dec;
} CelestialCoords;

float delta_ra(float ra, float ra0);
float x_from(const CelestialCoords *coords);
float y_from(const CelestialCoords *coords);

#endif // ASTRO_MATHS_H_
