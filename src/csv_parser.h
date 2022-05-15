#ifndef CSV_PARSER_H_
#define CSV_PARSER_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#define GREEK_IMPLEMENTATION
#include "greek.h"

#define printline() (printf("\n"));

#define PARSEC_TO_LY 3.261563
#define parsecs_to_ly(p) (p * PARSEC_TO_LY);


// CSV HEADERS ---------------------------------------------
typedef enum HygDataHeader {
  ID, HIP, HD, HR, GL, BF, PROPER,
  RA, DEC, DIST, PMRA, PMDEC, RV,
  MAG, ABSMAG, SPECT, CI,
  X, Y, Z, VX, VY, VZ,
  RARAD, DECRAD, PMRARAD, PMDECRAD,
  BAYER, FLAM, CON, COMP, COMP_PRIMARY, BASE,
  LUM, VAR, VAR_MIN, VAR_MAX
} HygDataHeader;
#define HEADER_MAX VAR_MAX // 36 (37 headers)


// CONSTELLATIONS ------------------------------------------
typedef enum Constellation {
  And, Ant, Aps, Aql, Aqr, Ara, Ari, Aur,
  Boo, CMa, CMi, CVn, Cae, Cam, Cap, Car,
  Cas, Cen, Cep, Cet, Cha, Cir, Cnc, Col,
  Com, CrA, CrB, Crt, Cru, Crv, Cyg, Del,
  Dor, Dra, Eql, Eri, For, Gem, Gru, Her,
  Hor, Hya, Hyi, Ind, LMi, Lac, Leo, Lep,
  Lib, Lup, Lyn, Lyr, Men, Mic, Mon, Mus,
  Nor, Oct, Oph, Ori, Pav, Peg, Per, Phe,
  Pic, PsA, Psc, Pup, Pyx, Ret, Scl, Sco,
  Sct, Ser, Sex, Sge, Sgr, Tau, Tel, TrA,
  Tri, Tuc, UMa, UMi, Vel, Vir, Vol, Vul
} Constellation;
#define CONSTEL_MAX Vul // 87 (88 constellations)


// STAR ----------------------------------------------------
#define STAR_MAXCHAR 48
typedef struct Star {
  uint16_t id;
  char bf[STAR_MAXCHAR];
  char bayer[STAR_MAXCHAR];
  char proper[STAR_MAXCHAR];
  char spect[STAR_MAXCHAR];
  Constellation con;
  double ra, dec, dist, mag, ci;
} Star;


// PROTOTYPES ----------------------------------------------
bool has_comp_id(const char *str_id);

char *extract_self_id(const char *str_id);

uint16_t count_sep(const char *str, const char sep);

uint16_t *sep_indexes(const char *str, const char sep);

uint16_t *elt_lengths(const char *str, const char sep);

char **new_csv_line(const char *str, const char sep);

Star *new_star(char **csv_line);

GreekLetter get_letter(const Star *star);

void log_star(FILE *stream, const Star *star);

#endif // CSV_PARSER_H_
