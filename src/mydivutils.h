#ifndef _MYDIVUTILS_H_
#define _MYDIVUTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define LINE_MAX_CHR 79

#define ptab(s) (fprintf(s, "\t"))
#define pline(s) (fprintf(s, "\n"))
#define pspace(s) (fprintf(s, " "))

extern void pchar_n(FILE* stream, const char c, uint8_t n);

extern void err_exit(const char* fname, const char* msg);


#endif // _MYDIVUTILS_H_
