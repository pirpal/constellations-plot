#include "csv_parser.h"

#define U_BLACK_STAR "\U00002605" // ★ 

static const char* CONSTEL_STR_SHORT[] = {
  "And", "Ant", "Aps", "Aql", "Aqr", "Ara", "Ari", "Aur",
  "Boo", "CMa", "CMi", "CVn", "Cae", "Cam", "Cap", "Car",
  "Cas", "Cen", "Cep", "Cet", "Cha", "Cir", "Cnc", "Col",
  "Com", "CrA", "CrB", "Crt", "Cru", "Crv", "Cyg", "Del",
  "Dor", "Dra", "Eql", "Eri", "For", "Gem", "Gru", "Her",
  "Hor", "Hya", "Hyi", "Ind", "LMi", "Lac", "Leo", "Lep",
  "Lib", "Lup", "Lyn", "Lyr", "Men", "Mic", "Mon", "Mus",
  "Nor", "Oct", "Oph", "Ori", "Pav", "Peg", "Per", "Phe",
  "Pic", "PsA", "Psc", "Pup", "Pyx", "Ret", "Scl", "Sco",
  "Sct", "Ser", "Sex", "Sge", "Sgr", "Tau", "Tel", "TrA",
  "Tri", "Tuc", "UMa", "UMi", "Vel", "Vir", "Vol", "Vul"
};

static const char* CONSTEL_STR_GENITIVES[] = {
  "Andromedae", "Antliae", "Apodis", "Aquilae",
  "Aquarii", "Arae", "Arietis", "Aurigae",
  "Boötis", "Canis Majoris", "Canis Minoris", "Canum Venaticorum",
  "Caeli", "Camelopardalis", "Capricorni", "Carinae",
  "Cassiopeiae", "Centauri", "Cephei", "Ceti",
  "Chamaeleontis", "Circini", "Cancri", "Columbae",
  "Comae Berenices", "Coronae Australis", "Coronae Borealis", "Crateris",
  "Crucis", "Corvi", "Cygni", "Delphini",
  "Doradus", "Draconis", "Equulei", "Eridani",
  "Fornacis", "Geminorum", "Gruis", "Herculis",
  "Horologii", "Hydrae", "Hydri", "Indi",
  "Leonis Minoris", "Lacertae", "Leonis", "Leporis",
  "Librae", "Lupi", "Lyncis", "Lyrae",
  "Mensae", "Microscopii", "Monocerotis", "Muscae",
  "Normae", "Octantis", "Ophiuchi", "Orionis",
  "Pavonis", "Pegasi", "Persei", "Phoenicis",
  "Pictoris", "Piscis Austrini", "Piscium", "Puppis",
  "Pyxidis", "Reticulii", "Sculptoris", "Scorpii",
  "Scuti", "Serpentis", "Sextantis", "Sagittae",
  "Sagittarii", "Tauri", "Telescopii", "Trianguli Australis",
  "Trianguli", "Tucanae", "Ursae Majoris", "Ursae Minoris",
  "Velorum", "Virginis", "Volantis", "Vulpeculae"
};

static const char* GREEK_LETTERS[] = {
  "Alpha", "Beta",    "Gamma",   "Delta", "Epsilon", "Zeta",
  "Eta",   "Theta",   "Iota",    "Kappa", "Lambda",  "Mu",
  "Nu",    "Xi",      "Omicron", "Pi",    "Rho",     "Sigma",
  "Tau",   "Upsilon", "Phi",     "Chi",   "Psi",     "Omega"
};

static const char* GREEK_LETTERS_SHORT[] = {
  "Alp", "Bet", "Gam", "Del", "Eps", "Zet",
  "Eta", "The", "Iot", "Kap", "Lam", "Mu",
  "Nu",  "Xi",  "Omi", "Pi",  "Rho", "Sig",
  "Tau", "Ups", "Phi", "Chi", "Psi", "Ome"
};

static void err_exit(const char *msg) {
  fprintf(stderr, "[ERR] %s\n", msg);
  exit(EXIT_FAILURE);
}

bool has_comp_id(const char *str_id) {
  /* Double star system's id is formatted like:
     'main_star_id:companion_star_id'
  */
  for (size_t i = 0; i < strlen(str_id); ++i) {
    if (str_id[i] == ':')
      return true;
  }
  return false;
}

char *extract_self_id(const char *str_id) {
  uint16_t index = 0;
  for (size_t i = 0; i < strlen(str_id); ++i) {
    if (str_id[i] == ':') {
      index = (uint16_t) i;
      break;
    }
  }
  char *self_id = malloc((index + 1) * sizeof(char));
  if (self_id == NULL)
    err_exit("failed to malloc Star's id");
  memcpy(self_id, &str_id, index);
  self_id[index] = '\0';
  return self_id;
}

Constellation get_constel(const char *str_constel) {
  for (int i = 0; i < CONSTEL_MAX; ++i) {
    if (strcmp(str_constel, CONSTEL_STR_SHORT[i]) == 0) {
      return i;
    }
  }
  return 0;
}

uint16_t count_sep(const char *str, const char sep) {
  uint16_t count = 0;
  for (size_t i = 0; i < strlen(str); ++i) {
    if (str[i] == sep)
      count += 1;
  }
  return count;
}

uint16_t *sep_indexes(const char *str, const char sep) {
  uint16_t sep_nb = count_sep(str, sep);
  uint16_t *indexes = malloc(sep_nb * sizeof(uint16_t));
  if (indexes == NULL)
    err_exit("failed to malloc uint16_t[]");
  int count = 0;
  for (size_t i = 0; i < strlen(str); ++i) {
    if (str[i] == sep) {
      indexes[count] = i;
      count += 1;
    }
  }
  return indexes;
}

uint16_t *elt_lengths(const char *str, const char sep) {
  uint16_t sep_nb = count_sep(str, sep);
  uint16_t elt_nb = sep_nb + 1;
  uint16_t *indexes = sep_indexes(str, sep);
  uint16_t *lengths = malloc(elt_nb * sizeof(uint16_t));
  if (lengths == NULL)
    err_exit("failed to malloc lengths");

  for (uint16_t i = 0; i < elt_nb + 1; ++i) {
    if (i == 0) { // first element
      lengths[i] = indexes[0];
    } else if (i == sep_nb) { // last element
      lengths[i] = (uint16_t) strlen(str) - indexes[sep_nb - 1] - 1;
    } else { // default
      lengths[i] = indexes[i] - indexes[i - 1] - 1;
    }
  }
  free(indexes);
  return lengths;
}

char **new_csv_line(const char *str, const char sep) {
  uint16_t sep_nb = count_sep(str, sep);
  uint16_t elt_nb = sep_nb + 1;

  uint16_t *indexes = sep_indexes(str, sep);
  uint16_t *lengths = elt_lengths(str, sep);

  char **line = malloc(elt_nb * sizeof(char*));
  if (line == NULL)
    err_exit("failed to malloc char** csv line");

  for (uint16_t i = 0; i < elt_nb; ++i) {
    // malloc each string token with extra space for termination char '\0'
    line[i] = malloc((lengths[i] + 1) * sizeof(char));
    if (line[i] == NULL)
      err_exit("failed to malloc token char*");

    uint16_t start = i == 0 ? 0 : indexes[i - 1] + 1;
    if (lengths[i] == 0) {
      memcpy(line[i], &"", 0);
    } else {
	memcpy(line[i], &str[start], lengths[i]);
    }
    line[i][lengths[i]] = '\0';
  }
  free(indexes);
  free(lengths);
  return line;
}

Star *new_star(char **csv_line) {
  Star *star = malloc(sizeof(Star*));
  if (star == NULL)
    err_exit("failed to malloc Star*");

  uint8_t bf_len = (uint8_t) strlen(csv_line[BF]);
  memcpy(star->bf, csv_line[BF], bf_len);
  star->bf[bf_len] = '\0';

  uint8_t bayer_len = (uint8_t) strlen(csv_line[BAYER]);
  memcpy(star->bayer, csv_line[BAYER], bayer_len);
  star->bayer[bayer_len] = '\0';

  uint8_t proper_len = (uint8_t) strlen(csv_line[PROPER]);
  memcpy(star->proper, csv_line[PROPER], proper_len);
  star->proper[proper_len] = '\0';
                                           
  uint8_t spect_len = (uint8_t) strlen(csv_line[SPECT]);
  memcpy(star->spect, csv_line[SPECT], spect_len);
  star->spect[spect_len] = '\0';
                                           
  if (has_comp_id(csv_line[ID])) {
    char *self_id = extract_self_id(csv_line[ID]);
    star->id = atoi(self_id);
    free(self_id);
  } else {
    star->id = atoi(csv_line[ID]);
  }
  star->ra   = atof(csv_line[RA]);
  star->dec  = atof(csv_line[DEC]);
  star->dist = atof(csv_line[DIST]);
  star->mag  = atof(csv_line[MAG]);
  star->ci   = atof(csv_line[CI]);
  star->con  = get_constel(csv_line[CON]);
                                           
  return star;                               
}

GreekLetter get_letter(const Star *star) {
  for (uint16_t i = 0; i < MAX_LETTER; ++i) {
    if (strcmp(star->bayer, GREEK_LETTERS_SHORT[i]) == 0)
      return i;
  }
  return ALPHA;
}

void log_star(FILE *stream, const Star *star) {
  GreekLetter letter = get_letter(star);
  double dist_ly = parsecs_to_ly(star->dist);
  fprintf(stream,
	  "\n%s %s %s\n",
	  U_BLACK_STAR,
	  GREEK_LETTERS[letter],
	  CONSTEL_STR_GENITIVES[star->con]);
  fprintf(stream, "  id ........... %d\n", star->id);
  fprintf(stream, "  bf ........... %s\n", star->bf);
  fprintf(stream, "  bayer ........ %s\n", star->bayer);
  fprintf(stream, "  proper ....... %s\n", star->proper);
  fprintf(stream, "  dist (parsecs) %.3f\n", star->dist);
  fprintf(stream, "  dist (ly) .... %.3f\n", dist_ly);
  fprintf(stream, "  ra  (J2000) .. %.6f\n", star->ra);
  fprintf(stream, "  dec (J2000) .. %.6f\n", star->dec);
  fprintf(stream, "  spect ........ %s\n", star->spect);
  fprintf(stream, "  mag .......... %.2f\n", star->mag);
}

