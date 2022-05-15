#include <criterion/criterion.h>

#include "../src/csv_parser.h"

#define POLLUX "37718;37826;62509;2990;Gl 286;78Bet Gem;Pollux;7.755277;28.026199;10.3584;-625.69;-45.95;3.6;1.160;1.084;K0IIIvar;0.991;-4.055465;8.195180;4.867171;0.00002624;0.00001782;-0.00000031;2.0303268874812184;0.4891494417459975;-0.0000030334307178680563;-0.000000222771886;Bet;78;Gem;1;37718;;32.09223768048434;;;"

#define SEP ';'

Test(test_stars, test_new_star) {
  uint8_t sep_nb = count_sep(POLLUX, SEP);
  char **csv_line = new_csv_line(POLLUX, SEP);

  Star *s = new_star(csv_line);
  cr_expect_eq(s->id, atoi(csv_line[ID]));
  cr_expect_eq(strcmp(s->proper, csv_line[PROPER]), 0);
  cr_expect_eq(strcmp(s->bf, csv_line[BF]), 0);
  cr_expect_eq(strcmp(s->spect, csv_line[SPECT]), 0);
  
  for (uint8_t i = 0; i < (sep_nb + 1); ++i) {
    free(csv_line[i]);
  }
  free(csv_line);
  free(s);
}
