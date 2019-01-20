#include "arg_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "printer.h"

void print_help(char *argv0) {
  fprintf(stderr, "Usage: %s [OPTION...] FILE\n", argv0);
  fprintf(stderr, "Generate a pattern defined in FILE on GPIO.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "OPTION(s):\n");
  fprintf(stderr, "  -f <frequency>   The frequency of the pattern in [Hz].\n");
  fprintf(stderr, "                   Defaults to 1[Hz]. Mutually exclusive with -t.\n");
  fprintf(stderr, "  -t <period>      The period of the pattern in [ns].\n");
  fprintf(stderr, "                   Defaults to 1[s]. Mutually exclusive with -f.\n");
  fprintf(stderr, "  -r               Repeat pattern indefinitely. In case\n");
  fprintf(stderr, "                   it is not present, the pattern is sent\n");
  fprintf(stderr, "                   only once.\n");
  fprintf(stderr, "  -d               Print debug information.\n");
  fprintf(stderr, "  -h               Print this help message.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "The pattern FILE is a space separated list starting with\n");
  fprintf(stderr, "a number N defining an output pins count. Next, N pin\n");
  fprintf(stderr, "numbers are listed. Then, N*T output values are read, where\n");
  fprintf(stderr, "T is the pattern length in some arbitrary time units (defined\n");
  fprintf(stderr, "by OPTIONs -f or -t). In case, the number of values is not\n");
  fprintf(stderr, "divisible by N, it is assumed that all unspecified values are zeros.\n");
  fprintf(stderr, "Each value can be either '0' or '1'.\n");
}

void parse_args(int argc, char *argv[], config_t *config)
{
  config->period = 1000000000; // 10^9 [ns] = 1 [s]
  config->repeat = false;
  config->debug = false;
  bool has_f = false, has_t = false;
  long double f;
  int opt;
  while ((opt = getopt(argc, argv, "hdrf:t:")) != -1) {
    switch (opt) {
    case 'r':
      config->repeat = true;
      break;
    case 'd':
      config->debug = true;
      break;
    case 't':
      has_t = true;
      config->period = atoi(optarg);
      break;
    case 'f':
      has_f = true;
      f = atof(optarg);
      break;
    case 'h':
      print_help(argv[0]);
      exit(EXIT_SUCCESS);
    default:
      print_help(argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  if (has_t && has_f) {
    print_msg(MSG_ERROR, "Options -f and -t are mutually exclusive.");
    print_help(argv[0]);
    exit(EXIT_FAILURE);
  }
  if (!has_t && has_f) {
    if (f == 0) {
      print_msg(MSG_ERROR, "Frequency cannot be zero.");
      print_help(argv[0]);
      exit(EXIT_FAILURE);
    }
    config->period = (int)(1.0L/(f/1000000000.0L)); // 10^9
  }
  if (config->period < (int)(1000000000.0L/230.0L)) {
    print_msg(MSG_WARNING, "According to Intel, GPIO max speed is 230 [Hz].");
  }

  if (optind >= argc) {
    print_msg(MSG_ERROR, "Expected argument after options.");
    print_help(argv[0]);
    exit(EXIT_FAILURE);
  }
  config->file_name = argv[optind];

  if (config->debug) {
    print_msg(MSG_DEBUG, "Using the following configuration:");
    snprintf(msg_buf, MSG_BUF_MAX, "  * repeat: %s", config->repeat ? "yes" : "no");
    print_msg(MSG_DEBUG, msg_buf);
    snprintf(msg_buf, MSG_BUF_MAX, "  * period: %d [ns]", config->period);
    print_msg(MSG_DEBUG, msg_buf);
    snprintf(msg_buf, MSG_BUF_MAX, "  * file name: %s", config->file_name);
    print_msg(MSG_DEBUG, msg_buf);
  }
}
