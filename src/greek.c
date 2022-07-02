#include "greek.h"
#include "mydivutils.h"
#include <string.h>

const char* GREEK_SHORT_STR[] = {
  "Alp", "Bet", "Gam", "Del", "Eps", "Zet", "Eta", "Het",
  "Iot", "Kap", "Lam", "Mu",  "Nu",  "Xi",  "Omi", "Pi",
  "Rho", "Sig", "Tau", "Ups", "Phi", "Chi", "Psi", "Ome"
};


const wchar_t U_GREEK_LETTERS[24] = {
  L'α', // A  ALPHA Keyboard input for Emacs
  L'β', // B  BETA  (`M-x set-input-method greek`)
  L'γ', // G  GAMMA
  L'δ', // D  DELTA
  L'ε', // E  EPSILON
  L'ζ', // Z  ZETA
  L'η', // H  ETA
  L'θ', // U  THETA
  L'ι', // I  IOTA
  L'κ', // K  KAPPA
  L'λ', // L  LAMBDA
  L'μ', // M  MU
  L'ν', // N  MU
  L'ξ', // J  KSI
  L'ο', // O  OMICRON
  L'π', // P  PI
  L'ρ', // R  RHO
  L'σ', // S  SIGMA
  L'τ', // T  TAU
  L'υ', // Y  UPSILON
  L'φ', // F  PHO
  L'χ', // X  KI
  L'ψ', // C  PSI
  L'ω'  // ω  V  OMEGA
  // "\U000003c2", ς  W  (word end sigma, not used)
};


uint8_t get_letter_index(const char* bayer) {
  for (unsigned short i = 0; i < MAX_LETTER; ++i) {
    if (strcmp(GREEK_SHORT_STR[i],  bayer) == 0)
      return i;
  }
  return OMEGA + 1; // ERR 
}


void print_greek(FILE* stream, const GreekLetter g) {
  fprintf(stream, "%ld", U_GREEK_LETTERS[g]);
}
