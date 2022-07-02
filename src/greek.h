#ifndef GREEK_H_
#define GREEK_H_

#include <stdint.h>
#include <stdio.h>
#include <wchar.h>


typedef enum GreekLetter {
  ALPHA, BETA,    GAMMA,   DELTA, EPSILON, ZETA,
  ETA,   THETA,   IOTA,    KAPPA, LAMBDA,  MU,
  NU,    XI,      OMICRON, PI,    RHO,     SIGMA,
  TAU,   UPSILON, PHI,     CHI,   PSI,     OMEGA
} GreekLetter;
#define MAX_LETTER OMEGA // [23] (24 letters)

extern const wchar_t U_GREEK_LETTERS[24];

uint8_t get_letter_index(const char* bayer);

void print_greek(FILE* stream, const GreekLetter g);

#endif // GREEK_H_
