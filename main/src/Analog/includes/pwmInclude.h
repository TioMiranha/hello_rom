#ifndef PWMINCLUDE_H
#define PWMINCLUDE_H

#include "generalIncludes.h"
#include "pwmConstructor.h"
#include "../../utils/includes/allUtilsIncludes.h"
#include "adcSignal.h"

// void set_voltage_calibrated(int output_index, float voltage, uint32_t *duty);
//  void set_voltage(int output_index, float voltage);
void pwmControlSignal();

#endif