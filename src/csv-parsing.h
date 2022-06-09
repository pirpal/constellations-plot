#ifndef _CSV_PARSING_H
#define _CSV_PARSING_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void err_exit(const char *msg);

uint16_t count_sep(const char *str, const char sep);

uint16_t *sep_indexes(const char *str, const char sep);

uint16_t *tokens_lengths(const char *str, const char sep);

char **split_csv_line(const char *str, const char sep);

void free_split(char **split, uint16_t tok_nb);

#endif // _CSV_PARSING_H
