#ifndef ALLUTILSINCLUDES_H
#define ALLUTILSINCLUDES_H

#include "../Analog/includes/generalIncludes.h"
#include "../Analog/includes/pwmConstructor.h"

double potencia(double x, int y);
int defineModeAnalog(int index, output_channel_t out_mode);
int isAnalogEnabled(int index, output_channel_t is_enabled);

#endif