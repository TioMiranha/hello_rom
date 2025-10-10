#include "../includes/pwmConstructor.h"

output_channel_t outputs[NUM_OUTPUTS] = {
    {
        .pwm_channel = LEDC_CHANNEL_0,
        .adc_channel = ADC_CHANNEL_0,
        .name = "VOUT_0",
        .gpio_num = 4,
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
        .pwm_channel = LEDC_CHANNEL_1,
        .name = "VOUT_1",
        .adc_channel = ADC_CHANNEL_1,
        .gpio_num = 5,
        .pid = {.setpoint = 10.0f, .kp = 0.8f, .ki = 0.1f, .kd = 0.05f, .integral = 0.0f, .previous_error = 0.0f},
        .current_duty = 1112,
        .current_voltage = 0.0f,
        .enabled = 1,
    },

    {
        .pwm_channel = LEDC_CHANNEL_2,
        .adc_channel = ADC_CHANNEL_2,
        .name = "VOUT_2",
        .gpio_num = 6,
        .pid = {.setpoint = 10.0f, .kp = 0.8f, .ki = 0.1f, .kd = 0.05f, .integral = 0.0f, .previous_error = 0.0f},
        .current_duty = 1112,
        .current_voltage = 0.0f,
        .enabled = 1,
    },

    {
        .pwm_channel = LEDC_CHANNEL_3,
        .adc_channel = ADC_CHANNEL_3,
        .name = "VOUT_3",
        .gpio_num = 7,
        .pid = {.setpoint = 10.0f, .kp = 0.8f, .ki = 0.1f, .kd = 0.05f, .integral = 0.0f, .previous_error = 0.0f},
        .current_duty = 1112,
        .current_voltage = 0.0f,
        .enabled = 1,
    },
};

void pwm_init_all(void)
{
  // Configurar timer (comum a todos os canais)
  ledc_timer_config_t ledc_timer = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .timer_num = LEDC_TIMER,
      .duty_resolution = LEDC_DUTY_RES,
      .freq_hz = LEDC_FREQUENCY,
      .clk_cfg = LEDC_AUTO_CLK};
  ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

  // Configurar cada canal PWM individualmente
  for (int i = 0; i < NUM_OUTPUTS; i++)
  {
    if (outputs[i].enabled == 1)
    {
      ledc_channel_config_t ledc_channel = {
          .speed_mode = LEDC_MODE,
          .channel = outputs[i].pwm_channel,
          .timer_sel = LEDC_TIMER,
          .intr_type = LEDC_INTR_DISABLE,
          .gpio_num = outputs[i].gpio_num,
          .duty = outputs[i].current_duty,
          .hpoint = 0};
      ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

      ESP_LOGI("PWM", "Canal %s configurado: GPIO%d, Canal PWM %d",
               outputs[i].name, outputs[i].gpio_num, outputs[i].pwm_channel);
    }
  }
}