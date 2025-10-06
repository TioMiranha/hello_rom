#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_system.h"

void app_main(void)
{
    int duty;

    // Configura timer do PWM
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,   // velocidade
        .timer_num        = LEDC_TIMER_0,          // Timer do PWM
        .duty_resolution  = LEDC_TIMER_10_BIT,     // resolução 10 bits (0-1023)
        .freq_hz          = 10000,                  // frequência 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK          // clock automático
    };
    ledc_timer_config(&ledc_timer);

    // configura canal do pwm e gpio
    ledc_channel_config_t ledc_channel = {
        .gpio_num       = 4,                        // gpio do LED
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);

    // loop infinito: diminui duty cycle para simular LED apagando lentamente
    for (;;)
    {
        for (duty = 0; duty <= 1023; duty++)
        {
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            printf("Led ligado, desligando lentamente... \n");
            vTaskDelay(pdMS_TO_TICKS(5)); // velocidade de queda
        }
        printf("\nLed desligado, voltando...\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // pausa antes de repetir
    }
}
