#include <stdio.h>
#include "./includes/pwmIncludes.h"


void pwmControlSignal()
{
    int duty;
    float v_target;
    // loop infinito: diminui duty cycle para simular LED apagando lentamente
    for (;;)
    {
        for (v_target = 2.0; v_target <= 10.0; v_target += 0.1)
        {
            duty = (int)(((v_target - 2.0) / 8) * 1023);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

            printf("Tensão: %2lf \n V duty: V[%d] \n", v_target, duty);
            vTaskDelay(pdMS_TO_TICKS(5)); // velocidade de queda
        }

        for (duty = 10.0; duty <= 2.0; v_target -= 0.1)
        {
            duty = (int)(((v_target - 2.0) / 8) * 1023);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            printf("Led ligado, desligando lentamente... \n");
            vTaskDelay(pdMS_TO_TICKS(5)); // velocidade de queda
        }
        printf("Tensão: %2lf \n V duty: V[%d] \n", v_target, duty);
        vTaskDelay(pdMS_TO_TICKS(1000)); // pausa antes de repetir
    }
}
