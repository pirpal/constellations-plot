#include "greek.h"
#include "mydivutils.h"
#include <string.h>

const char* GREEK_SHORT_STR[] = {
  "Alp", "Bet", "Gam", "Del", "Eps", "Zet", "Eta", "Het",
  "Iot", "Kap", "Lam", "Mu",  "Nu",  "Xi",  "Omi", "Pi",
  "Rho", "Sig", "Tau", "Ups", "Phi", "Chi", "Psi", "Ome"
};

const char* GREEK_STR[] = {
  "Alpha", "Beta", "Gamma", "Delta", "Epsilon", "Zeta", "Eta", "Heta",
  "Iota", "Kappa", "Lambda", "Mu",  "Nu",  "Xi",  "Omicron", "Pi",
  "Rho", "Sigma", "Tau", "Upsilon", "Phi", "Chi", "Psi", "Omega"
};


const char* U_GREEK_LETTERS[24] = {
  "\U000003b1", // ALPHA   α
  "\U000003b2", // BETA    β 
  "\U000003b3", // GAMMA   γ
  "\U000003b4", // DELTA   δ
  "\U000003b5", // EPSILON ε
  "\U000003b6", // ZETA    ζ 
  "\U000003b7", // ETA     η 
  "\U000003b8", // THETA   θ
  "\U000003b9", // IOTA    ι
  "\U000003ba", // KAPPA   κ
  "\U000003bb", // LAMBDA  λ
  "\U000003bc", // MU      μ
  "\U000003bd", // NU      ν
  "\U000003be", // XI      ξ 
  "\U000003bf", // OMICRON ο
  "\U000003c0", // PI      π
  "\U000003c1", // RHO     ρ
  "\U000003c3", // SIGMA   σ
  "\U000003c4", // TAU     τ 
  "\U000003c5", // UPSILON υ
  "\U000003c6", // PHI     φ
  "\U000003c7", // CHI     χ
  "\U000003c8", // PSI     ψ
  "\U000003c9"  // OMEGA   ω
};


GreekLetter get_letter_index(const char *bayer) {
  for (int i = 0; i < LETTERS_NB; ++i) {
    if (strcmp(GREEK_SHORT_STR[i],  bayer) == 0)
      return i;
  }
  return 0; // ERR 
}


void print_greek(FILE* stream, const GreekLetter g) {
  fprintf(stream, "%s", U_GREEK_LETTERS[g]);
}
