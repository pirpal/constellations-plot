#ifndef SPLIT_STRING_H_
#define SPLIT_STRING_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint16_t tokens_nb(const char *str, const char sep);

char **new_split(const char *str, const char sep);

void free_split(char **split);

void log_split(FILE *stream, char **split);


#endif // SPLIT_STRING_H_
