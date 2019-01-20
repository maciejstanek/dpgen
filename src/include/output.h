#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <stdbool.h>

#include "arg_parser.h"

void initialize_mraa();
void register_pin(int pin);
void set_pin_value(int pin, bool value);
void cleanup_mraa();

#endif
