#ifndef PWMSTRUCT_H
#define PWMSTRUCT_H
#include "driver/ledc.h"

extern ledc_timer_config_t ledc_timer;
extern ledc_channel_config_t ledc_channel;

typedef struct
{
  int pwm_channel;
  int gpio_num;
  const char *name;
  int mode;
  uint32_t voltage_duty;
  uint32_t current_duty;
  float current_voltage;
  int enabled;
} output_channel_t;

typedef struct
{
  float measured_voltage;
  uint32_t pwm_duty;
} cal_point_t;

#endif