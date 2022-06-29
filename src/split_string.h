#ifndef SPLIT_STRING_H_
#define SPLIT_STRING_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//void err_exit(const char *msg);

//uint16_t count_sep(const char *str, const char sep);

//uint16_t *sep_indexes(const char *str, const char sep);

//uint16_t *tokens_lengths(const char *str, const char sep);

uint16_t tokens_nb(const char *str, const char sep);

char **new_split(const char *str, const char sep);

void free_split(char **split, uint16_t tok_nb);

void log_split(FILE *stream, char **split, uint16_t tok_nb);


#endif // SPLIT_STRING_H_
