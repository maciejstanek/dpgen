#include "pattern.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "printer.h"

#define SIGNALS_MAX_COUNT 20
#define PATTERN_MAX_LENGTH 2000

static bool pattern[SIGNALS_MAX_COUNT][PATTERN_MAX_LENGTH];
static int signals[SIGNALS_MAX_COUNT];
static int pattern_len = 0;
static int signals_count = 0;

int get_pattern_len()
{
  return pattern_len;
}

int get_signals_count()
{
  return signals_count;
}

int get_pin_number_at(int sig)
{
  assert(sig < signals_count);
  assert(sig >= 0);

  return signals[sig];
}

bool get_pattern_at(int sig, int time_unit)
{
  assert(sig < signals_count);
  assert(sig >= 0);
  assert(time_unit < pattern_len);
  assert(time_unit >= 0);

  return pattern[sig][time_unit];
}

int load_pattern(const char *file_name)
{
  FILE *f = fopen(file_name, "r");
  if (!f) {
    snprintf(msg_buf, MSG_BUF_MAX, "Could not open '%s' for reading.", file_name);
    print_msg(MSG_ERROR, msg_buf);
    return EXIT_FAILURE;
  }

  if (fscanf(f, "%d", &signals_count) < 0) {
    print_msg(MSG_ERROR, "Failed while reading signals count.");
    return EXIT_FAILURE;
  }
  for (int i = 0; i < signals_count; i++) {
    if (fscanf(f, "%d", &signals[i]) < 0) {
      snprintf(msg_buf, MSG_BUF_MAX, "Failed while reading signal #%d pin.", i);
      print_msg(MSG_ERROR, msg_buf);
      return EXIT_FAILURE;
    }
  }
  int val;
  int val_count = 0;
  while (fscanf(f, "%d", &val) >= 0) {
    if (val != 0 && val != 1) {
      print_msg(MSG_ERROR, "Pattern values can be only either zero or one.");
      return EXIT_FAILURE;
    }
    pattern[val_count % signals_count][val_count / signals_count] = val;
    if (val_count % signals_count == 0) {
      pattern_len++;
    }
    val_count++;
  }
  if (val_count % signals_count) {
    snprintf(msg_buf, MSG_BUF_MAX, "Failed to read value for signal"
     " #%d at time %d. All remaining values at this time are assumed"
     " to be zero.", val_count % signals_count, val_count / signals_count);
    print_msg(MSG_WARNING, msg_buf);
  }
  while (val_count % signals_count) {
    pattern[val_count % signals_count][val_count / signals_count] = 0;
    val_count++;
  }

  if (fclose(f)) {
    snprintf(msg_buf, MSG_BUF_MAX, "Could not close file '%s' after reading.", file_name);
    print_msg(MSG_WARNING, msg_buf);
  }
  return EXIT_SUCCESS;
}

void print_pattern(int chars_per_line)
{
  // TODO: Cleanup this copypasting
  // Vertical bar
  printf("+-");
  for (int i = 0; i < signals_count; i++) {
    if (i) {
      printf("-+-");
    }
    printf("--");
  }
  printf("-+\n");

  // Header
  for (int j = 0; j < pattern_len; j++) {
  }
  printf("| ");
  for (int i = 0; i < signals_count; i++) {
    if (i) {
      printf(" | ");
    }
    printf("%2d", signals[i]);
  }
  printf(" |\n");

  // Vertical bar
  printf("+-");
  for (int i = 0; i < signals_count; i++) {
    if (i) {
      printf("-+-");
    }
    printf("--");
  }
  printf("-+\n");

  // Pattern
  for (int j = 0; j < pattern_len; j++) {
    printf("| ");
    for (int i = 0; i < signals_count; i++) {
      if (i) {
        printf(" | ");
      }
      printf("%2d", pattern[i][j]);
    }
    printf(" |\n");
  }

  // Vertical bar
  printf("+-");
  for (int i = 0; i < signals_count; i++) {
    if (i) {
      printf("-+-");
    }
    printf("--");
  }
  printf("-+\n");
}
