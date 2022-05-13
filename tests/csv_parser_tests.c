#include <criterion/criterion.h>
#include "../src/csv_parser.h"


#define SEP ';'

#define QUICK_BROWN_FOX "the;quick;brown;fox;jumps;over;the;lazy;dog" // 8 sep
const uint8_t QUICK_BROWN_FOX_INDEXES[8] = { 3, 9, 15, 19, 25, 30, 34, 39 };
const uint8_t QUICK_BROWN_FOX_LEN[9] = { 3, 5, 5, 3, 5, 4, 3, 4, 3 };

#define EMPTY_FIELDS "a;;line;with;;empty;;fields" // 7 sep
const uint8_t EMPTY_FIELDS_INDEXES[7] = { 1, 2, 7, 12, 13, 19, 20 };
const uint8_t EMPTY_FIELDS_LEN[8] = { 1, 0, 4, 4, 0, 5, 0, 6 };

#define EMPTY_FIRST_LAST ";first;and;last;fields;are;empty;" // 7 sep
const uint8_t EMPTY_FIRST_LAST_INDEXES[7] = { 0, 6, 10, 15, 22, 26, 32 };
const uint8_t EMPTY_FIRST_LAST_LEN[8] = { 0, 5, 3, 4, 6, 3, 5, 0 };

#define ALL_EMPTY ";;;;;" // 5 sep
const uint8_t ALL_EMPTY_INDEXES[5] = { 0, 1, 2, 3, 4 };
const uint8_t ALL_EMPTY_LEN[6] = { 0, 0, 0, 0, 0, 0 };


Test(test_csv_parser, test_count_sep) {
  cr_expect(count_sep(QUICK_BROWN_FOX, SEP) == 8);
  cr_expect(count_sep(EMPTY_FIELDS, SEP) == 7);
  cr_expect(count_sep(EMPTY_FIRST_LAST, SEP) == 7);
}

Test(test_csv_parser, test_sep_indexes) {
  uint8_t *indexes = sep_indexes(QUICK_BROWN_FOX, SEP);
  for (uint8_t i = 0; i < count_sep(QUICK_BROWN_FOX, SEP); ++i) {
    cr_expect(indexes[i] == QUICK_BROWN_FOX_INDEXES[i]);
  }
  free(indexes);
}

Test(test_csv_parser, test_empty_fields_indexes) {
  uint8_t *indexes = sep_indexes(EMPTY_FIELDS, SEP);
  for (uint8_t i = 0; i < count_sep(EMPTY_FIELDS, SEP); ++i) {
    cr_expect(indexes[i] == EMPTY_FIELDS_INDEXES[i]);
  }
  free(indexes);
}

Test(test_csv_parser, test_empty_first_last_indexes) {
  uint8_t *indexes = sep_indexes(EMPTY_FIRST_LAST, SEP);
  for (uint8_t i = 0; i < count_sep(EMPTY_FIRST_LAST, SEP); ++i) {
    cr_expect(indexes[i] == EMPTY_FIRST_LAST_INDEXES[i]);
  }
  free(indexes);
}

Test(test_csv_parser, test_all_empty_indexes) {
  uint8_t *indexes = sep_indexes(ALL_EMPTY, SEP);
  for (uint8_t i = 0; i < count_sep(ALL_EMPTY, SEP); ++i) {
    cr_expect(indexes[i] == ALL_EMPTY_INDEXES[i]);
  }
  free(indexes);
}

Test(test_csv_parser, test_elt_lengths_a) {
  uint8_t sep_nb = count_sep(QUICK_BROWN_FOX, SEP);
  uint8_t *lengths = elt_lengths(QUICK_BROWN_FOX, SEP);
  for (uint8_t i = 0; i < (sep_nb + 1); ++i) {
    cr_expect(lengths[i] == QUICK_BROWN_FOX_LEN[i]);
  }
  free(lengths);
}

Test(test_csv_parser, test_elt_lengths_b) {
  uint8_t sep_nb = count_sep(EMPTY_FIRST_LAST, SEP);
  uint8_t *lengths = elt_lengths(EMPTY_FIRST_LAST, SEP);
  for (uint8_t i = 0; i < (sep_nb + 1); ++i) {
    cr_expect(lengths[i] == EMPTY_FIRST_LAST_LEN[i]);
  }
  free(lengths);
}

Test(test_csv_parser, test_elt_lengths_c) {
  uint8_t sep_nb = count_sep(ALL_EMPTY, SEP);
  uint8_t *lengths = elt_lengths(ALL_EMPTY, SEP);
  for (uint8_t i = 0; i < (sep_nb + 1); ++i) {
    cr_expect(lengths[i] == ALL_EMPTY_LEN[i]);
  }
  free(lengths);
}
