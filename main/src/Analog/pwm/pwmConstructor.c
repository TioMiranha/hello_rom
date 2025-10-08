#include "../includes/pwmConstructor.h"

/*
output_channel_t outputs[NUM_OUTPUTS] = {
  {LEDC_CHANNEL_0, 2, "VOUT_1"}, // PWM_1 -> GPIO2
  {LEDC_CHANNEL_1, 3, "VOUT_2"}, // PWM_2 -> GPIO3
  {LEDC_CHANNEL_2, 6, "VOUT_3"}, // PWM_3 -> GPIO6
  {LEDC_CHANNEL_3, 7, "VOUT_4"}  // PWM_4 -> GPIO7
};
*/

ledc_timer_config_t ledc_Timer(void)
{
  ledc_timer_config_t timer = {
      .speed_mode = LEDC_MODE,
      .timer_num = LEDC_TIMER,
      .duty_resolution = LEDC_DUTY_RES,
      .freq_hz = LEDC_FREQUENCY,
      .clk_cfg = LEDC_AUTO_CLK};

  ESP_ERROR_CHECK(ledc_timer_config(&timer));
  ESP_LOGI("PWM", "Timer PWM configurado: %d Hz, %d bits",
           LEDC_FREQUENCY, (1 << LEDC_DUTY_RES) - 1);

  return timer;
}

ledc_channel_config_t ledc_Channel(void)
{
  ledc_channel_config_t channel = {
      .gpio_num = LEDC_OUTPUT_IO,
      .speed_mode = LEDC_MODE,
      .channel = LEDC_CHANNEL,
      .timer_sel = LEDC_TIMER,
      .duty = 0,
      .hpoint = 0};

  ESP_ERROR_CHECK(ledc_channel_config(&channel));
  ESP_LOGI("PWM", "Canal PWM configurado: GPIO%d, Canal %d",
           LEDC_OUTPUT_IO, LEDC_CHANNEL);

  return channel;
}