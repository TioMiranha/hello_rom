#include "../includes/adcSignal.h"

static esp_adc_cal_characteristics_t *adc_chars;

void adc_init(void)
{
  // Configurar ADC
  adc1_config_width(ADC_WIDTH);
  adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);

  // Caracterização do ADC para melhor precisão
  adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN, ADC_WIDTH,
                           ESP_ADC_CAL_VAL_DEFAULT_VREF, adc_chars);

  ESP_LOGI("ADC", "ADC inicializado no GPIO%d", ADC1_CHANNEL_0_GPIO_NUM);
}

float read_voltage(void)
{
  uint32_t adc_reading = 0;

  // Fazer média de várias leituras
  for (int i = 0; i < ADC_SAMPLES; i++)
  {
    adc_reading += adc1_get_raw(ADC_CHANNEL);
  }
  adc_reading /= ADC_SAMPLES;

  // Converter para tensão (mV)
  uint32_t voltage_mv = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
  float voltage_v = (float)voltage_mv / 1000.0f;

  // Aplicar fator do divisor de tensão (se houver)
  voltage_v *= VOLTAGE_DIVIDER_RATIO;

  return voltage_v;
}

// CONTROLE PID SIMPLES PARA MANTER 10.0V EXATOS
typedef struct
{
  float setpoint;
  float kp, ki, kd;
  float integral;
  float previous_error;
} pid_controller_t;

pid_controller_t pid = {
    .setpoint = 10.0f, // 10.0V desejados
    .kp = 0.5f,        // Ganho proporcional - AJUSTE
    .ki = 0.01f,       // Ganho integral - AJUSTE
    .kd = 0.1f,        // Ganho derivativo - AJUSTE
    .integral = 0.0f,
    .previous_error = 0.0f};

uint32_t pid_control(float measured_voltage)
{
  float error = pid.setpoint - measured_voltage;

  // Termo Proporcional
  float proportional = pid.kp * error;

  // Termo Integral
  pid.integral += error;
  float integral = pid.ki * pid.integral;

  // Termo Derivativo
  float derivative = pid.kd * (error - pid.previous_error);
  pid.previous_error = error;

  // Soma todos os termos
  float output = proportional + integral + derivative;

  // Converter para duty cycle (0-8191)
  uint32_t duty = (uint32_t)(output * 8191.0f / 10.0f);

  // Limitar duty cycle
  if (duty > 8191)
    duty = 8191;
  if (duty < 0)
    duty = 0;

  return duty;
}

void maintain_exact_10v_closed_loop(void)
{
  ESP_LOGI("CLOSED_LOOP", "🎯 Iniciando controle em malha fechada para 10.0V exatos");

  // Inicializar PWM e ADC
  ledc_Timer();
  ledc_Channel();
  adc_init();

  // Valor inicial
  uint32_t current_duty = 7500;
  ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, current_duty);
  ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

  vTaskDelay(pdMS_TO_TICKS(1000));

  while (1)
  {
    // Ler tensão atual
    float measured_voltage = read_voltage();

    // Calcular novo duty cycle usando PID
    current_duty = pid_control(measured_voltage);

    // Aplicar novo duty cycle
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, current_duty);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

    // Log
    ESP_LOGI("CLOSED_LOOP", "Medido: %.3fV | Duty: %lu | Erro: %.3fV",
             measured_voltage, current_duty, 10.0f - measured_voltage);

    vTaskDelay(pdMS_TO_TICKS(100)); // Loop a cada 100ms
  }
}