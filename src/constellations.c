#include "constellations.h"
#include "split_string.h"

#include "mydivutils.h"

#include <stdlib.h>


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


Constellation *new_constellation(const char* csvline) {
  char** split = new_split(csvline, SEP);
  
  if (!is_constel_shortname(split[IAU_ABBREV]))
    err_exit("new_constellation", "not a constellation short name");
  Constellation *constel = malloc(sizeof(Constellation));
  if (constel == NULL)
    err_exit("new_constellation", "failed to malloc Constellation");
  strcpy(constel->shortname, split[IAU_ABBREV]);
  strcpy(constel->name,      split[CONSTELLATION]);
  strcpy(constel->genitive,  split[GENITIVE]);
  strcpy(constel->meaning,   split[MEANING]);
  free_split(split, CONSTEL_DB_FIELDS_NB);
  return constel;
}


void log_constellation(FILE *stream, const Constellation *con) {
  fprintf(stream,
	  "<Constellation %p> '%s', '%s', '%s', '%s'\n",
	  (void*) con,
	  con->shortname, con->name, con->genitive, con->meaning);
}


char* get_constel_str(const ConstelShort c) {
  char *str = malloc(4 * sizeof(char));
  if (str == NULL)
    err_exit("get_constel_str", "failed to malloc char*");
  strcpy(str, CONSTEL_SHORT_STR[c]);
  return str;
}


Constellation* load_constellations(const char* csvpath) {
  /*
    TODO: check
  */
  FILE* csv = fopen(csvpath, "r");
  if (csv == NULL)
    err_exit("load_constellations", "failed to open CSV file");

  Constellation *constels = malloc(CONSTELLATIONS_NB * sizeof(Constellation));
  if (constels == NULL)
    err_exit("load_constellations", "failed to malloc Constellation*");

  bool headers_passed = false;
  char line[CSV_LINE_MAXCHAR];
  uint8_t constel_count = 0;

  while ((fgets(line, CSV_LINE_MAXCHAR, csv)) != NULL) {
    if (!headers_passed) {
      headers_passed = true;
      continue;
    } else {
      constels[constel_count] = *new_constellation(line);
      constel_count += 1;
    }
  }
  return constels;
}

void log_constels_shorts(FILE* stream) {
  fprintf(stream, "\n  ");
  for(uint8_t i = 0; i < CONSTELLATIONS_NB; ++i) {
    if (i == 0)
      fprintf(stream, "\n  ");
    if (i % 11 == 0) {
      fprintf(stream, "\n  ");
    }
    fprintf(stream, "%s ", CONSTEL_SHORT_STR[i]);
  }
  fprintf(stream, "\n");
}
