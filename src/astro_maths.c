#include "astro_maths.h"
#include <stdint.h>
#include <math.h>

//--------------------------------------------------------------
// Static functions
//--------------------------------------------------------------

uint8_t deg_to_h(float deg) {
  return (uint8_t) deg / HOUR_DEG;
}
                                                                        
uint8_t deg_to_m(float deg) {
  float tmp = (deg / HOUR_DEG) - deg_to_h(deg);
  return (uint8_t) floor(tmp * 60);
}
                                                                        
float deg_to_s(float deg) {
  float tmp = (((deg / HOUR_DEG) - deg_to_h(deg)) * 60) - deg_to_m(deg);
  return tmp * 60;
}


//--------------------------------------------------------------
// Functions
//--------------------------------------------------------------

void log_hms_coords(FILE *stream,const HmsCoords *hms) {
  fprintf(stream,
	 "<HmsCoords %p> %dh %dm %.2fs\n",
	  (void*) hms, hms->h, hms->m, hms->s);
}

float hms_to_degrees(const HmsCoords *hms) {
  return (float) (hms->h * HOUR_DEG + hms->m * MIN_DEG + hms->s * SEC_DEG);
}

HmsCoords degrees_to_hms(float degrees) {
  HmsCoords hms;
  hms.h = deg_to_h(degrees);
  hms.m = deg_to_m(degrees);
  hms.s = deg_to_s(degrees);
  return hms;
}
