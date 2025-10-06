#ifndef PWMINCLUDE_H
#define PWMINCLUDE_H
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "./structs/pwmStructs.h"
#include "esp_system.h"

void pwmControlSignal();

#endif