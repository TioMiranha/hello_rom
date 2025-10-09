#ifndef PWMSTRUCT_H
#define PWMSTRUCT_H
#include "adcSignal.h"
#include "driver/ledc.h"

extern ledc_timer_config_t ledc_timer;
extern ledc_channel_config_t ledc_channel;

typedef struct
{
  int pwm_channel;
  int gpio_num;
  const char *name;
  pid_controller_t pid;
  uint32_t current_duty;
  float current_voltage;
  int active;
} output_channel_t;

typedef struct
{
  float measured_voltage;
  uint32_t pwm_duty;
} cal_point_t;

#endif