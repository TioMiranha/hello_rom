#include <stdio.h>
#include "../includes/pwmInclude.h"

void pwmControlSignal(void)
{
    int i;
    ESP_LOGI("MAIN", "CONTROLE EM MALHA FECHADA COM PID");

    pwm_init_all();
    // adc_init();

    for (i = 0; i < NUM_OUTPUTS; i++)
    {
        if (outputs[i].enabled == 1)
        {
            if (outputs[i].mode == 0)
            {

                ledc_set_duty(LEDC_MODE, outputs[i].pwm_channel, outputs[i].voltage_duty);
                ledc_update_duty(LEDC_MODE, outputs[i].pwm_channel);
            }
            else
            {
                ledc_set_duty(LEDC_MODE, outputs[i].pwm_channel, outputs[i].current_duty);
                ledc_update_duty(LEDC_MODE, outputs[i].pwm_channel);
            }
        }
    }

    vTaskDelay(pdMS_TO_TICKS(2000));

    for (;;)
    {
        for (i = 0; i < NUM_OUTPUTS; i++)
        {

            if (outputs[i].enabled == 1)
            {
                // outputs[i].current_voltage = read_voltage(i, &outputs[i]);

                // outputs[i].current_duty = pid_control(outputs[i].current_voltage, &outputs[i].pid);
                if (outputs[i].mode == 0)
                {

                    ledc_set_duty(LEDC_MODE, outputs[i].pwm_channel, outputs[i].voltage_duty);
                    ledc_update_duty(LEDC_MODE, outputs[i].pwm_channel);

                    ESP_LOGI("PID", "Alvo: 10.0V | Medido: %.2fV | Duty: %lu | Erro: %.2fV",
                             outputs[i].current_voltage, outputs[i].current_duty, 10.0f - outputs[i].voltage_duty);

                    outputs[i].voltage_duty += 50;

                    // Limitar duty cycle
                    if (outputs[i].voltage_duty >= 7145)
                        outputs[i].voltage_duty = 1112;
                }
                else
                {
                    ledc_set_duty(LEDC_MODE, outputs[i].pwm_channel, outputs[i].current_duty);
                    ledc_update_duty(LEDC_MODE, outputs[i].pwm_channel);

                    ESP_LOGI("PID", "Alvo: 10.0V | Medido: %.2fV | Duty: %lu | Erro: %.2fV",
                             outputs[i].current_voltage, outputs[i].current_duty, 10.0f - outputs[i].current_voltage);

                    outputs[i].current_duty += 50;

                    if (outputs[i].current_duty >= 7145)
                        outputs[i].current_duty = 1112;
                }
            }
            vTaskDelay(pdMS_TO_TICKS(500)); // Controle a cada 1500ms
        }
        vTaskDelay(pdMS_TO_TICKS(800));
    }
}