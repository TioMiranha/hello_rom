#ifndef ADCSIGNAL_H
#define ADCSIGNAL_H

#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "../structs/adcStructs.h"
#include "generalIncludes.h"

// Configuração do ADC
#define ADC_CHANNEL_0 ADC1_CHANNEL_0
#define ADC_CHANNEL_1 ADC1_CHANNEL_1
#define ADC_CHANNEL_2 ADC1_CHANNEL_2
#define ADC_CHANNEL_3 ADC1_CHANNEL_3
#define ADC_CHANNEL_4 ADC1_CHANNEL_4

#define ADC_ATTEN ADC_ATTEN_DB_11
#define ADC_WIDTH ADC_WIDTH_BIT_12
#define ADC_SAMPLES 64
#define VOLTAGE_DIVIDER_RATIO 3.03 // Exemplo: 10V → 3.3V

void adc_init(void);
float read_voltage(void);
uint32_t pid_control(float measured_voltage, pid_controller_t *pid);

#endif