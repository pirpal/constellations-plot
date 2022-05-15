#include "csv_parser.h"


#define CASTOR "36744;36850;60179;2891;Gl 278A;66Alp Gem;Castor;7.576634;31.888276;15.5958;-206.33;-148.18;6.0;1.580;0.615;A2Vm;0.034;-5.311938;12.130011;8.238737;0.00000983;0.00001645;-0.00000627;1.983558270234413;0.5565554130270287;-0.0000010003160670902778;-0.000000718396911;Alp;66;Gem;1;36744;Gl 278;49.43106869868354;;;"

#define POLLUX "37718;37826;62509;2990;Gl 286;78Bet Gem;Pollux;7.755277;28.026199;10.3584;-625.69;-45.95;3.6;1.160;1.084;K0IIIvar;0.991;-4.055465;8.195180;4.867171;0.00002624;0.00001782;-0.00000031;2.0303268874812184;0.4891494417459975;-0.0000030334307178680563;-0.000000222771886;Bet;78;Gem;1;37718;;32.09223768048434;;;"

#define SEP ';'

int main (void)
{
  printline();

  // ---------------------------------------------
  char **castor_line = new_csv_line(CASTOR, SEP);
  Star *castor = new_star(castor_line);
  log_star(stdout, castor);
  
  // ---------------------------------------------
  char **pollux_line = new_csv_line(POLLUX, SEP);
  Star *pollux = new_star(pollux_line);
  log_star(stdout, pollux);


  // FREE ****************************************
  free(castor);
  for (uint16_t i = 0; i < HEADER_MAX; ++i) {
    free(castor_line[i]);
  }
  free(castor_line);
  castor = NULL;
  castor_line = NULL;

  free(pollux);
  for (uint16_t i = 0; i < HEADER_MAX; ++i) {
    free(pollux_line[i]);
  }
  free(pollux_line);
  pollux = NULL;
  pollux_line = NULL;
  // END FREE ************************************

  printline();
  return EXIT_SUCCESS;
}
