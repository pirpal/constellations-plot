#ifndef GREEK_H_
#define GREEK_H_

#include <stdint.h>
#include <stdio.h>

#define LETTERS_NB 24

typedef enum GreekLetter {
  ALPHA, BETA,    GAMMA,   DELTA, EPSILON, ZETA,
  ETA,   THETA,   IOTA,    KAPPA, LAMBDA,  MU,
  NU,    XI,      OMICRON, PI,    RHO,     SIGMA,
  TAU,   UPSILON, PHI,     CHI,   PSI,     OMEGA
} GreekLetter;

extern const char* GREEK_SHORT_STR[LETTERS_NB];
extern const char* GREEK_STR[LETTERS_NB];

GreekLetter get_letter_index(const char* bayer);

void print_greek(FILE* stream, const GreekLetter g);

#endif // GREEK_H_
