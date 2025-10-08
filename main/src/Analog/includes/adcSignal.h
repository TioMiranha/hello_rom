#ifndef ADCSIGNAL_H
#define ADCSIGNAL_H

#include "driver/adc.h"
#include "esp_adc_cal.h"

// Configuração do ADC
#define ADC_CHANNEL ADC1_CHANNEL_0
#define ADC_ATTEN ADC_ATTEN_DB_11
#define ADC_WIDTH ADC_WIDTH_BIT_12
#define ADC_SAMPLES 64
#define VOLTAGE_DIVIDER_RATIO 3.03 // Exemplo: 10V → 3.3V

#endif