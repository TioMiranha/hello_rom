#ifndef PWMCONSTRUCTOR_H
#define PWMCONSTRUCTOR_H
#include "../structs/pwmStructs.h"
#include "generalIncludes.h"

#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO_0 (0)
#define LEDC_OUTPUT_IO_1 (1)
#define LEDC_OUTPUT_IO_2 (2)
#define LEDC_OUTPUT_IO_3 (3) // GPIO4 para teste
#define LEDC_OUTPUT_IO_4 (4)
#define LEDC_CHANNEL_0 LEDC_CHANNEL_0
#define LEDC_CHANNEL_1 LEDC_CHANNEL_1
#define LEDC_CHANNEL_2 LEDC_CHANNEL_2
#define LEDC_CHANNEL_3 LEDC_CHANNEL_3
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT
#define LEDC_FREQUENCY (1000)
#define NUM_OUTPUTS 4

// Definições para compatibilidade
#define PWM_MODE LEDC_MODE
#define PWM_TIMER LEDC_TIMER
#define PWM_RESOLUTION LEDC_DUTY_RES
#define PWM_FREQUENCY LEDC_FREQUENCY

void pwm_init_all(void);

extern output_channel_t outputs[NUM_OUTPUTS];

#endif