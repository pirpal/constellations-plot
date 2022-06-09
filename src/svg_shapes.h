#ifndef _SVG_SHAPES_
#define _SVG_SHAPES_

#include <stdint.h>

typedef struct RgbColor {
  uint8_t red, green, blue;
} RgbColor;


typedef struct SvgRect {
  float x, y, rx, ry, w, h, stroke_w;
  RgbColor fill, stroke;
} SvgRect;


typedef struct SvgLine {
  float x1, y1, x2, y2, stroke_w;
  RgbColor stroke;
} SvgLine;


typedef struct SvgCircle {
  uint16_t cx, cy, r, stroke_w;
  RgbColor fill, stroke;
} SvgCircle;


typedef struct SvgFont {
  char *family;
  int size;
} SvgFont;
 

typedef struct SvgText {
  char *text;
  SvgFont *font;
  float x, y;
  RgbColor fill;
} SvgText;

#endif
