#ifndef CONSTELLATIONS_H_
#define CONSTELLATIONS_H_

#include "stars.h"
#include <stdbool.h>
#include <stdio.h>

//--------------------------------------------------------------
// Constellations short names
//--------------------------------------------------------------
typedef enum ConstelShort {
   And, Ant, Aps, Aqr, Aql, Ara, Ari, Aur,
   Boo, Cae, Cam, Cnc, CVn, CMa, CMi, Cap,
   Car, Cas, Cen, Cep, Cet, Cha, Cir, Col,
   Com, CrA, CrB, Crv, Crt, Cru, Cyg, Del,
   Dor, Dra, Equ, Eri, For, Gem, Gru, Her,
   Hor, Hya, Hyi, Ind, Lac, Leo, LMi, Lep,
   Lib, Lup, Lyn, Lyr, Men, Mic, Mon, Mus,
   Nor, Oct, Oph, Ori, Pav, Peg, Per, Phe,
   Pic, Psc, PsA, Pup, Pyx, Ret, Sge, Sgr,
   Sco, Scl, Sct, Ser, Sex, Tau, Tel, Tri,
   TrA, Tuc, UMa, UMi, Vel, Vir, Vol, Vul
} ConstelShort;

#define CONSTELLATIONS_NB 88

// Array of short names defined in constellations.c
extern const char* CONSTEL_SHORT_STR[CONSTELLATIONS_NB];

//--------------------------------------------------------------
// Constellation DB constants
//--------------------------------------------------------------
#define CONSTELLATIONS_DB_PATH "/home/pirpal/C/Projects/constellations-plot/db/constellations.csv"

typedef enum ConstelCsvHeader {
  INDEX, CONSTELLATION, IAU_ABBREV, OTHER_ABBREV,
  GENITIVE, FAMILY, ORIGIN, MEANING, BRIGHTEST_STAR
} ConstelCsvHeader;

#define CONSTEL_DB_FIELDS_NB 9

#define CONSTEL_MAXCHAR 32


//--------------------------------------------------------------
// struct Constellation
//--------------------------------------------------------------
typedef struct Constellation {
  char shortname[4]; // 3 + '\0'
  char name[CONSTEL_MAXCHAR];
  char genitive[CONSTEL_MAXCHAR];
  char meaning[CONSTEL_MAXCHAR];
} Constellation;


//--------------------------------------------------------------
// Functions prototypes
//--------------------------------------------------------------
bool is_constel_shortname(const char *shortname);

Constellation *new_constellation(const char *shortname);

void log_constellation(FILE *stream, const Constellation *con);



#endif // CONSTELLATIONS_H_
