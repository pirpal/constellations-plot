#include "math.h"
#include "astro_maths.h"


float delta_ra(float ra, float ra0) {
  return ra - ra0;
}

float x_from(const CelestialCoords *coords) {
  return coords->ra;
}

float y_from(const CelestialCoords *coords) {
  return coords->ra;
}
