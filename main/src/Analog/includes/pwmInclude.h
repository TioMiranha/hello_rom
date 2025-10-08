#ifndef PWMINCLUDE_H
#define PWMINCLUDE_H
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "pwmConstructor.h"
#include "../../utils/includes/allUtilsIncludes.h"
#include "esp_system.h"

void set_voltage_calibrated(int output_index, float voltage, uint32_t *duty);
void set_voltage(int output_index, float voltage);
void pwmControlSignal();

#endif