#ifndef PWMSTRUCT_H
#define PWMSTRUCT_H
#include "driver/ledc.h"

// Configura timer do PWM
ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_LOW_SPEED_MODE,    // velocidade
    .timer_num = LEDC_TIMER_0,            // Timer do PWM
    .duty_resolution = LEDC_TIMER_10_BIT, // resolução 10 bits (0-1023)
    .freq_hz = 10000,                     // frequência 5 kHz
    .clk_cfg = LEDC_AUTO_CLK              // clock automático
};
ledc_timer_config(&ledc_timer);

// configura canal do pwm e gpio
ledc_channel_config_t ledc_channel = {
    .gpio_num = 4, // gpio do LED
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = LEDC_CHANNEL_0,
    .timer_sel = LEDC_TIMER_0,
    .duty = 0,
    .hpoint = 0};
ledc_channel_config(&ledc_channel);

#endif