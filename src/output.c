#include "output.h"

#include <string.h>

#include "mraa.h"
#include "mraa/gpio.h"
#include "printer.h"

#define PIN_COUNT_MAX 20

static mraa_gpio_context pins[PIN_COUNT_MAX];
static int pin_map[PIN_COUNT_MAX];
static int pin_count = 0;

void set_pin_value(int pin, bool value) {
  int pin_index = -1;
  for (int i = 0; i < pin_count; i++) {
    if (pin_map[i] == pin) {
      pin_index = i;
      break;
    }
  }
  if (pin_index == -1) {
    snprintf(msg_buf, MSG_BUF_MAX, "Pin #%d not found.", pin);
    print_msg(MSG_WARNING, msg_buf);
    return;
  }
  if (mraa_gpio_write(pins[pin_index], value) != MRAA_SUCCESS) {
    snprintf(msg_buf, MSG_BUF_MAX, "Setting output value %d on pin #%d failed.",
      value, pin);
    print_msg(MSG_WARNING, msg_buf);
  }
}

void initialize_mraa()
{
  snprintf(msg_buf, MSG_BUF_MAX, "Using 'mraa' %s (%s detected).",
    mraa_get_version(), mraa_get_platform_name());
  print_msg(MSG_INFO, msg_buf);
  mraa_init();
}

void register_pin(int pin) {
  if (!(pins[pin_count] = mraa_gpio_init(pin))) {
    snprintf(msg_buf, MSG_BUF_MAX, "Initializing pin #%d failed.", pin);
    print_msg(MSG_WARNING, msg_buf);
    return;
  }
  else if (mraa_gpio_dir(pins[pin_count], MRAA_GPIO_OUT) != MRAA_SUCCESS) {
    snprintf(msg_buf, MSG_BUF_MAX, "Forcing pin #%d direction failed.", pin);
    print_msg(MSG_WARNING, msg_buf);
    return;
  }
  pin_map[pin_count++] = pin;
}

void cleanup_mraa()
{
  while(pin_count--) {
    if (mraa_gpio_close(pins[pin_count]) != MRAA_SUCCESS) {
      snprintf(msg_buf, MSG_BUF_MAX, "Closing pin #%d failed.", pin_count);
    }
  }
  mraa_deinit();
}
