#ifndef SVG_API_H_
#define SVG_API_H_


#include <stdbool.h>
#include "svg_shapes.h"


// XML general constants
#define XML_VERSION 1.0
#define ENCODING "utf-8"
#define BASE_PROFILE "baseProfile=\"full\""
#define SVG_VERSION "version=\"1.1\""
#define XMLNS "http://www.w3.org/2000/svg"
#define XMLNS_EV "http://www.w3.org/2001/xml-events"
#define XMLNS_XLINK "http://www.w3.org/1999/xlink"


bool valid_rgb(const RgbColor *color);

char *rgb_string(const RgbColor c);

void add_xml_markup (FILE *f, const float xml_v, const char *encoding);

void add_open_svg_markup(FILE *f, const int w, const int h);

void add_xmlns_links(FILE *f);

void add_rect(FILE *f, const SvgRect *rect);

void add_line(FILE *f, const SvgLine *line);

void add_circle(FILE *f, const SvgCircle *circle);

void add_text(FILE *f, const SvgText *text, const SvgFont *font);

void add_close_svg_markup(FILE *f);


#endif // SVG_API_H_
