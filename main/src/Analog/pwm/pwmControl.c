#include <stdio.h>
#include "../includes/pwmInclude.h"

// Definição do array de saídas (mantido para compatibilidade futura)
output_channel_t outputs[NUM_OUTPUTS] = {
    {LEDC_CHANNEL_0, 2, "VOUT_1"},
    {LEDC_CHANNEL_1, 3, "VOUT_2"},
    {LEDC_CHANNEL_2, 6, "VOUT_3"},
    {LEDC_CHANNEL_3, 7, "VOUT_4"}};

void set_voltage(int output_index, float voltage)
{
    // 🔥 CORREÇÃO: Removida a verificação de output_index para teste único
    // Use output_index = 0 para testar no canal 0

    if (voltage < 0.0f)
        voltage = 0.0f;
    if (voltage > 10.0f)
        voltage = 10.0f;

    uint32_t duty = (uint32_t)((voltage / 10.0f) * 4095.0f);

    if (duty > 8191)
        duty = 8191;

    // 🔥 CORREÇÃO: Usando LEDC_CHANNEL fixo para teste com GPIO4
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

    ESP_LOGI("VOLTAGE", "GPIO%d: %.2fV -> duty: %lu",
             LEDC_OUTPUT_IO, voltage, duty);
}

// Tabela de calibração
cal_point_t calibration_table[NUM_OUTPUTS][5] = {
    {{0.0, 0}, {2.5, 2048}, {5.0, 4096}, {7.5, 6144}, {10.0, 8191}},
    {{0.0, 0}, {2.5, 2048}, {5.0, 4096}, {7.5, 6144}, {10.0, 8191}},
    {{0.0, 0}, {2.5, 2048}, {5.0, 4096}, {7.5, 6144}, {10.0, 8191}},
    {{0.0, 0}, {2.5, 2048}, {5.0, 4096}, {7.5, 6144}, {10.0, 8191}}};

void set_voltage_calibrated(int output_index, float voltage)
{
    // 🔥 CORREÇÃO: Adicionado loop completo e declaração de variável
    if (output_index < 0 || output_index >= NUM_OUTPUTS)
        return;

    cal_point_t *cal = calibration_table[output_index];
    uint32_t duty = 0;

    // Interpolação linear entre pontos de calibração
    for (int i = 0; i < 4; i++)
    {
        if (voltage >= cal[i].measured_voltage &&
            voltage <= cal[i + 1].measured_voltage)
        {

            float ratio = (voltage - cal[i].measured_voltage) /
                          (cal[i + 1].measured_voltage - cal[i].measured_voltage);

            duty = cal[i].pwm_duty +
                   (uint32_t)(ratio * (cal[i + 1].pwm_duty - cal[i].pwm_duty));
            break;
        }
    }

    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void pwmControlSignal(void)
{
    ESP_LOGI("MAIN", "Iniciando controle de saída analógica única no GPIO: [%d]", LEDC_OUTPUT_IO);

    // Inicializar PWM
    ledc_timer_config_t timerLed = ledc_Timer();
    ledc_channel_config_t channelLed = ledc_Channel();

    vTaskDelay(pdMS_TO_TICKS(100));

    // CORREÇÃO: Teste simplificado para uma única saída
    ESP_LOGI("TEST", "Testando saída única no GPIO%d", LEDC_OUTPUT_IO);

    // Levar a 0V
    set_voltage(0, 0.0f); // Usando índice 0, mas canal fixo
    vTaskDelay(pdMS_TO_TICKS(2000));

    // Varredura de 0-10V
    ESP_LOGI("TEST", "Iniciando varredura 0-10V");
    for (float volt = 0.0f; volt <= 10.0f; volt += 1.0f)
    {
        set_voltage(0, volt); // Usando índice 0, mas canal fixo
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    // Voltar a 0V
    set_voltage(0, 0.0f);
    vTaskDelay(pdMS_TO_TICKS(2000));

    // CORREÇÃO: Loop principal simplificado
    ESP_LOGI("TEST", "Iniciando ciclo contínuo de teste");
    float test_voltages[] = {0.0f, 2.5f, 5.0f, 7.5f, 10.0f};
    int num_voltages = sizeof(test_voltages) / sizeof(test_voltages[0]);

    while (1)
    {
        for (int i = 0; i < num_voltages; i++)
        {
            set_voltage(0, test_voltages[i]);
            ESP_LOGI("TEST", "Mantendo: %.1fV", test_voltages[i]);
            vTaskDelay(pdMS_TO_TICKS(3000));
        }
    }
}