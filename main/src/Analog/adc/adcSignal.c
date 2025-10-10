#include "../includes/adcSignal.h"

static esp_adc_cal_characteristics_t *adc_chars;

void adc_init(void)
{
  // Configurar ADC
  adc1_config_width(ADC_WIDTH);

  // Caracterização do ADC para melhor precisão
  adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN, ADC_WIDTH,
                           ESP_ADC_CAL_VAL_DEFAULT_VREF, adc_chars);
  for (int i = 0; i < NUM_OUTPUTS; i++)
  {
    if (outputs[i].enabled)
    {
      adc1_config_channel_atten(outputs[i].adc_channel, ADC_ATTEN_DB_11);
      ESP_LOGI("ADC", "Canal ADC %d configurado para %s",
               outputs[i].adc_channel, outputs[i].name);
    }
  }

  ESP_LOGI("ADC", "ADC inicializado no GPIO%d", ADC1_CHANNEL_0);
}

float read_voltage(int index, output_channel_t *channel_index)
{
  if (adc_chars == NULL)
  {
    adc_init();
  }

  uint32_t adc_reading = 0;
  // Fazer média de várias leituras
  printf("Coletando %d amostras ADC:\n", ADC_SAMPLES);

  for (int i = 0; i < ADC_SAMPLES; i++)
  {
    uint32_t single_read = adc1_get_raw(channel_index->adc_channel);
    adc_reading += single_read;
    printf("  Amostra %2d: %4u | Acumulado: %6u\n",
           i, single_read, adc_reading);

    vTaskDelay(pdMS_TO_TICKS(10)); // Pequena pausa entre leituras
  }

  // Calcular média
  uint32_t average_raw = adc_reading / ADC_SAMPLES;
  printf("-> Média das leituras: %u\n", average_raw);

  // Converter para tensão (mV)
  uint32_t voltage_mv = esp_adc_cal_raw_to_voltage(average_raw, adc_chars);
  printf("-> Tensão convertida: %u mV\n", voltage_mv);

  // Converter para Volts
  float voltage_v = (float)voltage_mv / 1000.0f;
  printf("-> Tensão em Volts: %.3f V\n", voltage_v);

  // Aplicar fator do divisor de tensão
  float final_voltage = voltage_v * VOLTAGE_DIVIDER_RATIO;
  printf("-> Tensão final (com divisor): %.3f V\n", final_voltage);
  printf("----------------------------------------\n");

  return final_voltage;
}

uint32_t pid_control(float measured_voltage, pid_controller_t *pid)
{
  float error = pid->setpoint - measured_voltage;

  // Termo Proporcional
  float proportional = pid->kp * error;

  // Termo Integral
  pid->integral += error;
  float integral = pid->ki * pid->integral;

  // Termo Derivativo
  float derivative = pid->kd * (error - pid->previous_error);
  pid->previous_error = error;

  // Soma todos os termos
  float output_delta = proportional + integral + derivative;

  static uint32_t current_duty = 1500;
  int32_t new_duty = current_duty + (int32_t)output_delta;

  // Limitar duty cycle
  if (new_duty >= 7150)
    new_duty = 1112;
  if (new_duty < 0)
    new_duty = 0;

  current_duty = new_duty;
  return current_duty;
}