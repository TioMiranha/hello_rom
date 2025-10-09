#include <stdio.h>
#include "../includes/pwmInclude.h"

output_channel_t outputs[NUM_OUTPUTS] = {
    {
        .pwm_channel = ADC_CHANNEL_0,
        .name = "VOUT_0",
        .gpio_num = ADC_CHANNEL_0,
        .pid = {
            .setpoint = 10.0f,
            .kp = 0.8f,
            .ki = 0.1f,
            .kd = 0.05f,
            .integral = 0.0f,
            .previous_error = 0.0f},
        .current_duty = 1112,
        .current_voltage = 0.0f,
        .enabled = 1,
    },

    {
        .pwm_channel = ADC_CHANNEL_1,
        .name = "VOUT_1",
        .gpio_num = ADC_CHANNEL_1,
        .pid = {.setpoint = 10.0f, .kp = 0.8f, .ki = 0.1f, .kd = 0.05f, .integral = 0.0f, .previous_error = 0.0f},
        .current_duty = 1112,
        .current_voltage = 0.0f,
        .enabled = 1,
    },

    {
        .pwm_channel = ADC_CHANNEL_2,
        .name = "VOUT_2",
        .gpio_num = ADC_CHANNEL_2,
        .pid = {.setpoint = 10.0f, .kp = 0.8f, .ki = 0.1f, .kd = 0.05f, .integral = 0.0f, .previous_error = 0.0f},
        .current_duty = 1112,
        .current_voltage = 0.0f,
        .enabled = 1,
    },

    {
        .pwm_channel = ADC_CHANNEL_3,
        .name = "VOUT_3",
        .gpio_num = ADC_CHANNEL_3,
        .pid = {.setpoint = 10.0f, .kp = 0.8f, .ki = 0.1f, .kd = 0.05f, .integral = 0.0f, .previous_error = 0.0f},
        .current_duty = 1112,
        .current_voltage = 0.0f,
        .enabled = 1,
    },
};

void pwmControlSignal(void)
{
    int i;
    ESP_LOGI("MAIN", "CONTROLE EM MALHA FECHADA COM PID");

    ledc_Timer();
    ledc_Channel();
    adc_init();

    uint32_t current_duty = 1112; // Valor inicial conservador
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, current_duty);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

    vTaskDelay(pdMS_TO_TICKS(2000));

    for (;;)
    {
        for (i = 0; i < NUM_OUTPUTS; i++)
        {

            if (outputs[i].enabled == 1)
            {
                outputs[i].current_voltage = read_voltage(i, &outputs[i]);

                ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, current_duty);
                ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

                ESP_LOGI("PID", "Alvo: 10.0V | Medido: %.2fV | Duty: %lu | Erro: %.2fV",
                         measured_voltage, current_duty, 10.0f - measured_voltage);
            }
            vTaskDelay(pdMS_TO_TICKS(1500)); // Controle a cada 500ms
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}