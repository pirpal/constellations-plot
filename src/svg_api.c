#define _GNU_SOURCE /* for use of asprintf function */
#include <stdlib.h>
#include <stdio.h>
#include "svg_api.h"


static void err_exit(const char *msg) {
  printf("%s\n", msg);
  exit(EXIT_FAILURE);
}

void add_xml_markup(FILE *f, const float xml_v, const char *encoding) {
   fprintf(f,
	   "<?xml version=\"%.1f\" encoding=\"%s\" ?>",
	   xml_v, encoding);
}

void add_open_svg_markup(FILE *f, const int w, const int h) {
  fprintf(f,
	  "<svg %s height=\"%d\" width=\"%d\" ",
	  SVG_VERSION, w, h);
}

void add_xmlns_links(FILE *f) {
  fprintf(f,
	  "xmlns=\"%s\" xmlns:ev=\"%s\" xmlns:xlink=\"%s\" >",
	  XMLNS, XMLNS_EV, XMLNS_XLINK);
}

bool in_range(const int color) {
  return (color >= 0 && color <= 255);
}

bool valid_rgb(const RgbColor *c) {
  if (!in_range(c->red) || !in_range(c->green) || !in_range(c->blue))
    return false;
  return true;
}

char *rgb_string(const RgbColor c) {
  if (!valid_rgb(&c))
    err_exit("Bad RGB color value");
  char *s;
  if (asprintf(&s, "rgb(%d,%d,%d)", c.red, c.green, c.blue) < 0)
    err_exit("Err: asprintf in rgb_string()");
  return s;
}

void add_rect(FILE *f, const SvgRect *rect) {
  char *fill_c = rgb_string(rect->fill);
  if (fill_c == NULL) { err_exit("Err: rgb_string(RgbColor)"); }
  
  char *stroke_c = rgb_string(rect->stroke);
  if (stroke_c == NULL) { err_exit("Err: rgb_string(RgbColor)"); }

  fprintf(f,
          "<rect x=\"%.1f\" y=\"%.1f\" rx=\"%.1f\" ry=\"%.1f\" ",
          rect->x, rect->y, rect->rx, rect->ry);
  fprintf(f,
	  "width=\"%.1f\" height=\"%.1f\" ",
	  rect->w, rect->h);
  fprintf(f,
          "fill=\"%s\" stroke=\"%s\" stroke-width=\"%.1f\" />",
          fill_c, stroke_c, rect->stroke_w);

  free(fill_c);
  free(stroke_c);
}

void add_circle(FILE *f, const SvgCircle *circle) {
  char *stroke_c = rgb_string(circle->stroke);                         
  if (stroke_c == NULL)
    err_exit("failed to malloc stroke rgb_string");

  char *fill_c = rgb_string(circle->fill);                         
  if (fill_c == NULL)
    err_exit("failed to malloc fill rgb_string");
  
  fprintf(f,
          "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" \n",
          circle->cx, circle->cy, circle->r);
  fprintf(f,
          "style=\"stroke:%s fill:%s stroke-width:%d\" />",
          stroke_c, fill_c, circle->stroke_w);
  free(stroke_c);
  free(fill_c);
}

void add_line(FILE *f, const SvgLine *line) {
  char *stroke_c = rgb_string(line->stroke);
  if (stroke_c == NULL) { err_exit("Err: rgb_string(RgbColor)"); }
  fprintf(f,
	  "<line x1=\"%.1f\" y1=\"%.1f\" x2=\"%.1f\" y2=\"%.1f\" ",
	  line->x1, line->y1, line->x2, line->y2);
  fprintf(f,
	  "stroke=\"%s\" stroke-width=\"%.1f\" />",
	  stroke_c, line->stroke_w);
  free(stroke_c);
}

void add_text(FILE *f, const SvgText *svg_text, const SvgFont *font) {
  char *fill_c = rgb_string(svg_text->fill);
  if (fill_c == NULL) { err_exit("Err: rgb_string()"); }
  fprintf(f,
	  "<text x=\"%.1f\" y=\"%1f\" font-family=\"%s\" font-size=\"%d\" >",
	  svg_text->x, svg_text->y, font->family, font->size);
  fprintf(f, "%s", svg_text->text);
  fprintf(f, "</text>");
}

void add_close_svg_markup(FILE *f) {
  fprintf(f, "</svg>");
}

