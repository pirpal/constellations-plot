#include <criterion/criterion.h>
#include "../src/astro_maths.h"


#define FLOAT_PT_TOLERANCE 0.00001


Test(astro_maths_tests, test_deg_to_rad) {
  float deg0 = 0.0;
  cr_expect(deg_to_rad(deg0) == 0.0, "0° should give 0 rad");
  
  float deg1 = 1.0;
  float expected1 = 0.0174533;
  cr_expect(deg_to_rad(deg1) - expected1 < FLOAT_PT_TOLERANCE,
	    "1° should be equal to 0.0174533 rad");

  float deg180 = 180.0;
  float expected2 = 3.14159;
  cr_expect(deg_to_rad(deg180) - expected2 < FLOAT_PT_TOLERANCE);
  
  float deg360 = 360.0;
  float expected3 = 6.28319;
  cr_expect(deg_to_rad(deg360) - expected3 < FLOAT_PT_TOLERANCE,
	    "360° should be equal to 6.28319 rad");
}


