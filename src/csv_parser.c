#include "csv_parser.h"

static const char* CONSTEL_STR_SHORT[] = {
  "And", "Ant", "Aps", "Aql", "Aqr", "Ara", "Ari", "Aur",
  "Boo",
  "Cae", "Cam", "Cap", "Car", "Cas", "Cen", "Cep", "Cet", "Cha", "Cir", "CMa",
  "CMi", "Cnc", "Col", "Com", "CrA", "CrB", "Crt", "Cru", "Crv", "Cyg",
  "Del", "Dor", "Dra",
  "Eql", "Eri",
  "For",
  "Gem", "Gru",
  "Her", "Hor", "Hya", "Hyi",
  "Ind",
  "Lac", "Leo", "Lep", "Lib", "LMi", "Lup", "Lyn", "Lyr",
  "Men", "Mic", "Mon", "Mus",
  "Nor",
  "Oct", "Oph", "Ori",
  "Pav", "Peg", "Per", "Phe", "Pic", "PsA", "Psc", "Pup", "Pyx",
  "Ret",
  "Scl", "Sco", "Sct", "Ser", "Sex", "Sge", "Sgr",
  "Tau", "Tel", "TrA", "Tri", "Tuc",
  "UMa", "UMi",
  "Vel", "Vir", "Vol", "Vul"
};

/*static const char* CONSTEL_STR[] = {
  "Andromeda", "Antlia", "Apus", "Aquarius", "Aquila",
  "Ara", "Aries", "Auriga", "Boötes", "Caelum",
  "Camelopardalis", "Cancer", "Canes Venatici", "Canis Major",
  "Canis Minor", "Capricornus", "Carina", "Cassiopeia",
  "Centaurus", "Cepheus", "Cetus", "Chamaeleon", "Circinus",
  "Columba", "Coma Berenices", "Corona Australis",
  "Corona Borealis", "Corvus", "Crater", "Crux", "Cygnus",
  "Delphinus", "Dorado", "Draco", "Equuleus", "Eridanus",
  "Fornax", "Gemini", "Grus", "Hercules", "Horologium",
  "Hydra", "Hydrus", "Indus", "Lacerta", "Leo", "Leo Minor",
  "Lepus", "Libra", "Lupus", "Lynx", "Lyra", "Mensa",
  "Microscopium", "Monoceros", "Musca", "Norma", "Octans",
  "Ophiuchus", "Orion", "Pavo", "Pegasus", "Perseus",
  "Phoenix", "Pictor", "Pisces", "Piscis Austrinus", "Puppis",
  "Pyxis", "Reticulum", "Sagitta", "Sagittarius", "Scorpius",
  "Sculptor", "Scutum", "Serpens", "Sextans", "Taurus",
  "Telescopium", "Triangulum", "Triangulum Australe", "Tucana",
  "Ursa Major", "Ursa Minor", "Vela", "Virgo", "Volans",
  "Vulpecula"
  };*/
/*
static const char* CONSTEL_STR_GENITIVES[] = {
  "Andromedae", "Antliae", "Apodis", "Aquarii", "Aquilae", "Arae",
  "Arietis", "Aurigae", "Boötis", "Caeli", "Camelopardalis",
  "Cancri", "Canum Venaticorum", "Canis Majoris", "Canis Minoris",
  "Capricorni", "Carinae", "Cassiopeiae", "Centauri", "Cephei",
  "Ceti", "Chamaeleontis", "Circini", "Columbae", "Comae Berenices",
  "Coronae Australis", "Coronae Borealis", "Corvi", "Crateris",
  "Crucis", "Cygni", "Delphini", "Doradus", "Draconis", "Equulei",
  "Eridani", "Fornacis", "Geminorum", "Gruis", "Herculis", "Horologii",
  "Hydrae", "Hydri", "Indi", "Lacertae", "Leonis", "Leonis Minoris",
  "Leporis", "Librae", "Lupi", "Lyncis", "Lyrae", "Mensae", "Microscopii",
  "Monocerotis", "Muscae", "Normae", "Octantis", "Ophiuchi", "Orionis",
  "Pavonis", "Pegasi", "Persei", "Phoenicis", "Pictoris", "Piscium",
  "Piscis Austrini", "Puppis", "Pyxidis", "Reticulii", "Sagittae",
  "Sagittarii", "Scorpii", "Sculptoris", "Scuti", "Serpentis",
  "Sextantis", "Tauri", "Telescopii", "Trianguli", "Trianguli Australis",
  "Tucanae", "Ursae Majoris", "Ursae Minoris", "Velorum", "Virginis",
  "Volantis", "Vulpeculae"
};
*/
static void err_exit(const char *msg)
{
  fprintf(stderr, "[ERR] %s\n", msg);
  exit(EXIT_FAILURE);
}

Constellation get_constel(const char *str_constel)
{
  for (int i = 0; i < CONSTEL_MAX; ++i) {
    if (strcmp(str_constel, CONSTEL_STR_SHORT[i]) == 0) {
      return i;
    }
  }
  return 0;
}

uint8_t count_sep(const char *str, const char sep)
{
  uint8_t count = 0;
  for (size_t i = 0; i < strlen(str); ++i) {
    if (str[i] == sep)
      count += 1;
  }
  return count;
}

uint8_t *sep_indexes(const char *str, const char sep)
{
  uint8_t sep_nb = count_sep(str, sep);
  uint8_t *indexes = malloc(sep_nb * sizeof(uint8_t));
  if (indexes == NULL)
    err_exit("failed to malloc uint8_t[]");
  int count = 0;
  for (size_t i = 0; i < strlen(str); ++i) {
    if (str[i] == sep) {
      indexes[count] = i;
      count += 1;
    }
  }
  return indexes;
}

uint8_t *elt_lengths(const char *str, const char sep)
{
  uint8_t sep_nb = count_sep(str, sep);
  uint8_t elt_nb = sep_nb + 1;
  uint8_t *indexes = sep_indexes(str, sep);
  uint8_t *lengths = malloc(elt_nb * sizeof(uint8_t));
  if (lengths == NULL)
    err_exit("failed to malloc lengths");

  for (uint8_t i = 0; i < elt_nb + 1; ++i) {
    if (i == 0) { // first element
      lengths[i] = indexes[0];
    } else if (i == sep_nb) { // last element
      lengths[i] = (uint8_t) strlen(str) - indexes[sep_nb - 1] - 1;
    } else { // default
      lengths[i] = indexes[i] - indexes[i - 1] - 1;
    }
  }
  free(indexes);
  return lengths;
}

char **new_csv_line(const char *str, const char sep)
{
  uint8_t sep_nb = count_sep(str, sep);
  uint8_t elt_nb = sep_nb + 1;

  uint8_t *indexes = sep_indexes(str, sep);
  uint8_t *lengths = elt_lengths(str, sep);

  if (indexes == NULL || lengths == NULL)
    err_exit("failed to create indexes or lengths");

  // malloc a char* for each token
  char **line = malloc((sep_nb + 1) * sizeof(char*));
  if (line == NULL)
    err_exit("failed to malloc char** line");

  for (uint8_t i = 0; i < elt_nb; ++i) {
    // malloc each string token with extra space for termination char '\0'
    line[i] = malloc((lengths[i] + 1) * sizeof(char));
    if (line[i] == NULL)
      err_exit("failed to malloc token char*");

    uint8_t start = (i == 0) ? 0 : indexes[i - 1] + 1;
    memcpy(line[i], &str[start], lengths[i]);
    line[i][lengths[i]] = '\0';
  }
  free(indexes);
  free(lengths);
  return line;
}

Star *new_star(const char **csv_line)
{
  Star *star = malloc(sizeof(Star*));
  if (star == NULL)
    err_exit("failed to malloc Star*");
                                           
  memcpy(star->bf,
         csv_line[BF],
         strlen(csv_line[BF]));
                                           
  memcpy(star->proper,
         csv_line[PROPER],
         strlen(csv_line[PROPER]));
                                           
  memcpy(star->spect,
         csv_line[SPECT],
         strlen(csv_line[SPECT]));
                                           
  star->id   = atoi(csv_line[ID]);
  star->ra   = atof(csv_line[RA]);
  star->dec  = atof(csv_line[DEC]);
  star->dist = atof(csv_line[DIST]);
  star->mag  = atof(csv_line[MAG]);
  star->ci   = atof(csv_line[CI]);
  star->con  = get_constel(csv_line[CON]);
                                           
  return star;                               
}

