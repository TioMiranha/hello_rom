#include <stdio.h>
#include "../includes/pwmInclude.h"

output_channel_t outputs[NUM_OUTPUTS] = {
    {LEDC_CHANNEL_0, 2, "VOUT_1"},
    {LEDC_CHANNEL_1, 3, "VOUT_2"},
    {LEDC_CHANNEL_2, 6, "VOUT_3"},
    {LEDC_CHANNEL_3, 7, "VOUT_4"}};

// Tabela de calibração
cal_point_t calibration_table[NUM_OUTPUTS][5] = {
    {{10.0, 4095}, {8.0, 3071}, {6.9, 2047}, {3.5, 1023}, {0.0, 0}},
    {{10.0, 4095}, {8.0, 3071}, {6.9, 2047}, {3.5, 1023}, {0.0, 0}},
    {{10.0, 4095}, {8.0, 3071}, {6.9, 2047}, {3.5, 1023}, {0.0, 0}},
    {{10.0, 4095}, {8.0, 3071}, {6.9, 2047}, {3.5, 1023}, {0.0, 0}}};

/*void set_voltage_calibrated(int output_index, float voltage, uint32_t *duty)
{
    // CORREÇÃO: Adicionado loop completo e declaração de variável
    if (output_index < 0 || output_index >= NUM_OUTPUTS)
        return;

    *duty = 4095 - (uint32_t)((voltage / 10.0f) * 4095.0f);

    cal_point_t *cal = calibration_table[output_index];

    // Interpolação linear entre pontos de calibração
    for (int i = 0; i < 4; i++)
    {
        if (voltage >= cal[i].measured_voltage &&
            voltage <= cal[i + 1].measured_voltage)
        {

            float ratio = (voltage - cal[i].measured_voltage) /
                          (cal[i + 1].measured_voltage - cal[i].measured_voltage);

            *duty = 4095 - cal[i].pwm_duty +
                    (uint32_t)(ratio * (cal[i + 1].pwm_duty - cal[i].pwm_duty));
            break;
        }
    }
}*/

void pwmControlSignal(void)
{
    ESP_LOGI("MAIN", "🎯 CONTROLE EM MALHA FECHADA COM PID");

    ledc_Timer();
    ledc_Channel();
    adc_init();

    pid_controller_t pid = {
        .setpoint = 10.0f,
        .kp = 0.8f,
        .ki = 0.1f,
        .kd = 0.05f,
        .integral = 0.0f,
        .previous_error = 0.0f};

    uint32_t current_duty = 1112; // Valor inicial conservador
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, current_duty);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

    vTaskDelay(pdMS_TO_TICKS(2000));

    for (;;)
    {
        float measured_voltage = read_voltage();

        current_duty = pid_control(measured_voltage, &pid);

        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, current_duty);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

        ESP_LOGI("PID", "Alvo: 10.0V | Medido: %.2fV | Duty: %lu | Erro: %.2fV",
                 measured_voltage, current_duty, 10.0f - measured_voltage);

        vTaskDelay(pdMS_TO_TICKS(1500)); // Controle a cada 500ms
    }
}