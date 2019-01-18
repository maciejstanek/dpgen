#ifndef _PATTERN_H_
#define _PATTERN_H_

#include <stdbool.h>

int get_pattern_len();
int get_signals_count();
int get_pin_number_at(int sig);
bool get_pattern_at(int sig, int time_unit);
int load_pattern(const char *file_name);
void print_pattern();

#endif
