#ifndef CSV_PARSER_H_
#define CSV_PARSER_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define printline() (printf("\n"));


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
#define HEADER_MAX VAR_MAX

// CONSTELLATIONS ------------------------------------------
typedef enum Constellation {
  And, Ant, Aps, Aql, Aqr, Ara, Ari, Aur,
  Boo,
  Cae, Cam, Cap, Car, Cas, Cen, Cep, Cet, Cha, Cir, CMa,
  CMi, Cnc, Col, Com, CrA, CrB, Crt, Cru, Crv, Cyg,
  Del, Dor, Dra,
  Eql, Eri,
  For,
  Gem, Gru,
  Her, Hor, Hya, Hyi,
  Ind,
  Lac, Leo, Lep, Lib, LMi, Lup, Lyn, Lyr,
  Men, Mic, Mon, Mus,
  Nor,
  Oct, Oph, Ori,
  Pav, Peg, Per, Phe, Pic, PsA, Psc, Pup, Pyx,
  Ret,
  Scl, Sco, Sct, Ser, Sex, Sge, Sgr,
  Tau, Tel, TrA, Tri, Tuc,
  UMa, UMi,
  Vel, Vir, Vol, Vul
} Constellation;
#define CONSTEL_MAX Vul


// STAR ----------------------------------------------------
/* STAR DATA SAMPLE
  +------------------------------------------------------+
  | Data example : Deneb (Alpha Cygni)                   |
  +----------+---------------+---------------------------+
  | id           | 101769:101767 | id  (main:companion)  |
  | hip          | 102098        | HIP catalog id        |
  | hd           | 197345        | HD catalog id         |
  | hr           | 7924          | HR catalog id         |
  | gl           | NULL          | Gliese id             |
  | bf           | 50Alp Cyg     | Bayer/Flamsteed name  |
  | proper       | Deneb         | Proper name           |
  | ra           | 20.690532     | Right ascension J2000 |
  | dec          | 45.280338     | Declination J2000     |
  | dist         | 432.9004      | Distance (parsecs)    |
  | pmra         | 1.56          | Proper motion ra      |
  | pmdec        | 1.55          | Proper motion dec     |
  | rv           | -5.0          | Radial velocity       |
  | mag          | 1.250         | Magnitude             |
  | absmag       | -6.932        | Absolute magnitude    |
  | spect        | A2Ia          | Spectrum Class        |
  | ci           | 0.092         | Color index           |
  | x            |197.250632     | Cartesian x           |
  | y            | -232.113407   | Cartesian y           |
  | z            | 307.600832    | Cartesian z           |
  | vx           | -0.00000133   | Cartesian velocity x  |
  | vy           | 0.00000662    | Cartesian velocity y  |
  | vz           | -0.00000134   | Cartesian velocity z  |
  | rarad        | 5.4167685...  | ra in radians         |
  | decrad       | 0.7902909...  | dec in radians        |
  | pmrarad      | 0.0000000...  | pmra in radians       |
  | pmdecrad     | 0.0000000...  | pmdec in radians      |
  | bayer        |  Alp          | Bayer name            |
  | flam         |  50           | Flamsteed id          |
  | con          |  Cyg          | Constellation         |
  | comp         | 1             | 1 if companion star   |
  | comp_primary | 101767        | id of companion star  |
  | base         | NULL          |                       |
  | lum          | 51617.86...   | Luminosity            |
  | var          | Alp           | Variable              |
  | var_min      | 1.294         | Min variability       |
  | var_max      | 1.224         | Max variablity        |
  +------------------------------------------------------+
*/

#define STAR_MAXCHAR 24
                                            
typedef struct Star {
  uint16_t id;                   // 32263
  char bf[STAR_MAXCHAR];         // 9Alp CMa
  char proper[STAR_MAXCHAR];     // Sirius
  char spect[STAR_MAXCHAR];      // A0m...
  Constellation con;             // CMa
  double ra, dec, dist, mag, ci;
} Star;


// PROTOTYPES ----------------------------------------------
Constellation get_constel(const char *str_constel);

uint8_t count_sep(const char *str, const char sep);

uint8_t *sep_indexes(const char *str, const char sep);

uint8_t *elt_lengths(const char *str, const char sep);

char **new_csv_line(const char *str, const char sep);

Star *new_star(const char **csv_line);

#endif // CSV_PARSER_H_
