#include "astro_maths.h"



void log_hms_coords(FILE *stream,const HmsCoords *hms) {
  fprintf(stream,
	 "<HmsCoords %p> %d:%d:%d\n",
	  (void*) hms, hms->h, hms->m, hms->s);
}

float hms_to_degrees(const HmsCoords *hms) {
  return (float) (hms->h * HOUR_DEG + hms->m * MIN_DEG + hms->s * SEC_DEG);
}
