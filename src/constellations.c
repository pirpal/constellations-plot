#include "constellations.h"
#include "split_string.h"
#include <stdlib.h>


static void err_exit(const char *msg) {
  fprintf(stderr, "[ERR] %s\n", msg);
  exit(EXIT_FAILURE);
}


const char* CONSTEL_SHORT_STR[88] = {
  "And", "Ant", "Aps", "Aqr", "Aql", "Ara", "Ari", "Aur",
  "Boo", "Cae", "Cam", "Cnc", "CVn", "CMa", "CMi", "Cap",
  "Car", "Cas", "Cen", "Cep", "Cet", "Cha", "Cir", "Col",
  "Com", "CrA", "CrB", "Crv", "Crt", "Cru", "Cyg", "Del",
  "Dor", "Dra", "Equ", "Eri", "For", "Gem", "Gru", "Her",
  "Hor", "Hya", "Hyi", "Ind", "Lac", "Leo", "LMi", "Lep",
  "Lib", "Lup", "Lyn", "Lyr", "Men", "Mic", "Mon", "Mus",
  "Nor", "Oct", "Oph", "Ori", "Pav", "Peg", "Per", "Phe",
  "Pic", "Psc", "PsA", "Pup", "Pyx", "Ret", "Sge", "Sgr",
  "Sco", "Scl", "Sct", "Ser", "Sex", "Tau", "Tel", "Tri",
  "TrA", "Tuc", "UMa", "UMi", "Vel", "Vir", "Vol", "Vul"
};


bool is_constel_shortname(const char *shortname) {
  for (uint8_t i = 0; i < CONSTELLATIONS_NB; ++i) {
    if (strcmp(CONSTEL_SHORT_STR[i], shortname) == 0)
      return true;
  }
  return false;
}


Constellation *new_constellation(const char *shortname) {
  if (!is_constel_shortname(shortname))
    err_exit("new_constellation(): not a constellation short name");
  Constellation *constel = malloc(sizeof(Constellation));
  if (constel == NULL)
    err_exit("new_constellation(): failed to malloc Constellation");
  // search in constellations.csv for constellation data
  FILE *db = fopen(CONSTELLATIONS_DB_PATH, "r");
  if (db == NULL)
    err_exit("new_constellation(): failed to open constellations db");
  char line[CSV_LINE_MAXCHAR];
  while (fgets(line, sizeof(line), db)) {
    char **split = new_split(line, SEP);
    if (strcmp(shortname, split[IAU_ABBREV]) == 0) {
      strcpy(constel->shortname, split[IAU_ABBREV]);
      strcpy(constel->name,      split[CONSTELLATION]);
      strcpy(constel->genitive,  split[GENITIVE]);
      strcpy(constel->meaning,   split[MEANING]);
      free_split(split, CONSTEL_DB_FIELDS_NB);
      break;
    }
    if (split != NULL)
      free_split(split, CONSTEL_DB_FIELDS_NB);
  }
  fclose(db);
  return constel;
}


void log_constellation(FILE *stream, const Constellation *con) {
  fprintf(stream,
	  "<Constellation %p> '%s', '%s', '%s', '%s'\n",
	  (void*) con,
	  con->shortname, con->name, con->genitive, con->meaning);
}

