#include "split_string.h"

#define MYDIVUTILS_IMPLEMENTATION
#include "mydivutils.h"

//----------------------------------------------------------------
// § Static functions
//----------------------------------------------------------------

static uint16_t count_sep(const char *str, const char sep) {
  /* Returns nb of SEP delimiters in STR */
  uint16_t count = 0;
  for (uint16_t i = 0; i < strlen(str); ++i) {
    if (str[i] == sep)
      count += 1;
  }
  return count;
}

static uint16_t *sep_indexes(const char *str, const char sep) {
  /* Returns array of positions of SEP delimiter in STR */
  uint16_t sep_nb = count_sep(str, sep);
  uint16_t *indexes = malloc(sep_nb * sizeof(uint16_t));
  if (indexes == NULL)
    err_exit("sep_indexes", "failed to malloc indexes[]");

  uint16_t count = 0;
  for (uint16_t i = 0; i < strlen(str); ++i) {
    if (str[i] == sep) {
      indexes[count] = i;
      count += 1;
    }
  }
  return indexes;
}

static uint16_t *tokens_lengths(const char *str, const char sep) {
  /* Returns array of STR tokens's lengths */
  uint16_t sep_nb = count_sep(str, sep);
  uint16_t tok_nb = sep_nb + 1;
  uint16_t *indexes = sep_indexes(str, sep);
  uint16_t *lengths = malloc(tok_nb * sizeof(uint16_t));
  if (lengths == NULL)
    err_exit("tokens_lengths", "failed to malloc lengths[]");
  for (uint16_t i = 0; i < tok_nb; ++i) {
    if (i == 0) {             // first token
      lengths[i] = indexes[i];
    } else if (i == sep_nb) { // last token
      lengths[i] = strlen(str) - indexes[i - 1] - 1;
    } else {
      lengths[i] = indexes[i] - indexes[i - 1] - 1;
    }
  }
  free(indexes);
  return lengths;
}

//----------------------------------------------------------------
// § External functions: new_split, free_split
//----------------------------------------------------------------

uint16_t tokens_nb(const char *str, const char sep) {
  /* Returns number of tokens separated by SEP in STR */
  uint16_t sep_nb = count_sep(str, sep);
  return sep_nb + 1;
}


char **new_split(const char *str, const char sep) {
  /* Returns array of STR's string tokens */
  uint16_t sep_nb = count_sep(str, sep);
  uint16_t tok_nb = sep_nb + 1;
                                                 
  uint16_t *indexes = sep_indexes(str, sep);
  uint16_t *lengths = tokens_lengths(str, sep);
                                                 
  char **split = malloc(tok_nb * sizeof(char*));
  if (split == NULL)
    err_exit("new_split", "failed to malloc char** csv line");

  for (uint16_t i = 0; i < tok_nb; ++i) {
    // malloc each string token with extra space for termination char '\0'
    split[i] = malloc((lengths[i] + 1) * sizeof(char));
    if (split[i] == NULL)
      err_exit("new_split", "failed to malloc token char[]");

    uint16_t start = i == 0 ? 0 : indexes[i - 1] + 1;
    if (lengths[i] == 0) {
      memcpy(split[i], &"", 0);
    } else {
        memcpy(split[i], &str[start], lengths[i]);
    }
    split[i][lengths[i]] = '\0';
  }
  free(lengths);
  free(indexes);
  
  return split;
}

void free_split(char **split, uint16_t tok_nb) {
  /* Free memory allocated by `split_csv_line` function */
  for (uint16_t i = 0; i < tok_nb; ++i)
    free(split[i]);
  free(split);
}


void log_split(FILE *stream, char **split, uint16_t tok_nb) {
  for (uint16_t i = 0; i < tok_nb; ++i) {
    fprintf(stream, "[%d] '%s'\n", i, split[i]);
  }
}
