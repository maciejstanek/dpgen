#ifndef _ARG_PARSER_H_
#define _ARG_PARSER_H_

#include <stdbool.h>

typedef struct config_t {
  bool repeat;
  bool debug;
  char *file_name;
  int period; // [ns]
} config_t;

void print_help(char *argv0);
void parse_args(int argc, char *argv[], config_t *config);

#endif
