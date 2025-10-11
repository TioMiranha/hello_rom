#include <stdio.h>
#include "../includes/pwmInclude.h"

void pwmControlSignal(void)
{
    int i;
    ESP_LOGI("MAIN", "CONTROLE COM MODBUS");

    pwm_init_all();
    initializeModbus();

    for (i = 0; i < NUM_OUTPUTS; i++)
    {
        if (outputs[i].enabled == 1)
        {
            uint32_t initial_duty = outputs[i].mode == 0 ? outputs[i].voltage_duty : outputs[i].current_duty;

            initilizeRegisterModbus(i, outputs);
            ledc_set_duty(LEDC_MODE, outputs[i].pwm_channel, initial_duty);
            ledc_update_duty(LEDC_MODE, outputs[i].initial_duty);
        }
    }

    vTaskDelay(pdMS_TO_TICKS(2000));

    for (;;)
    {
        for (i = 0; i < NUM_OUTPUTS; i++)
        {

            if (defineModeAnalog(i, outputs))
            {
                // outputs[i].current_voltage = read_voltage(i, &outputs[i]);

                // outputs[i].current_duty = pid_control(outputs[i].current_voltage, &outputs[i].pid);
                uint32_t final_duty = outputs[i].mode == 0 ? outputs[i].voltage_duty : outputs[i].current_voltage;

                ledc_set_duty(LEDC_MODE, outputs[i].pwm_channel, final_duty);
                ledc_update_duty(LEDC_MODE, outputs[i].pwm_channel);

                ESP_LOGI("PID", "Alvo: 10.0V | Medido: %.2fV | Duty: %lu | Erro: %.2fV",
                         outputs[i].current_voltage, outputs[i].current_duty, 10.0f - final_duty);

                final_duty += 50;

                // Limitar duty cycle
                if (final_duty >= 7145)
                    final_duty = 1112;
            }
            vTaskDelay(pdMS_TO_TICKS(500)); // Controle a cada 1500ms

            vTaskDelay(pdMS_TO_TICKS(800));
        }
    }
}