#ifndef GREEK_H_
#define GREEK_H_

typedef enum GreekLetter {
  ALPHA, BETA, GAMMA, DELTA, EPSILON, ZETA,
  ETA, THETA, IOTA, KAPPA, LAMBDA, MU,
  NU, XI, OMICRON, PI,  RHO, SIGMA,
  TAU, UPSILON, PHI, CHI, PSI, OMEGA
} GreekLetter;
#define MAX_LETTER OMEGA // [23] (24 letters)

// Unicode Greek small letters
#define U_ALPHA   "\U000003b1" // α  A  Keyboard input for Emacs
#define U_BETA    "\U000003b2" // β  B  (`M-x set-input-method greek`)
#define U_GAMMA   "\U000003b3" // γ  G
#define U_DELTA   "\U000003b4" // δ  D
#define U_EPSILON "\U000003b5" // ε  E
#define U_ZETA    "\U000003b6" // ζ  Z
#define U_ETA     "\U000003b7" // η  H
#define U_THETA   "\U000003b8" // θ  U
#define U_IOTA    "\U000003b9" // ι  I
#define U_KAPPA   "\U000003ba" // κ  K
#define U_LAMBDA  "\U000003bb" // λ  L
#define U_MU      "\U000003bc" // μ  M
#define U_NU      "\U000003bd" // ν  N
#define U_XI      "\U000003be" // ξ  J
#define U_OMICRON "\U000003bf" // ο  O
#define U_PI      "\U000003c0" // π  P
#define U_RHO     "\U000003c1" // ρ  R
//                "\U000003c2"    ς  W (word end sigma, not used)
#define U_SIGMA   "\U000003c3" // σ  S
#define U_TAU     "\U000003c4" // τ  T
#define U_UPSILON "\U000003c5" // υ  Y
#define U_PHI     "\U000003c6" // φ  F
#define U_CHI     "\U000003c7" // χ  X
#define U_PSI     "\U000003c8" // ψ  C
#define U_OMEGA   "\U000003c9" // ω  V

#endif // GREEK_H_
