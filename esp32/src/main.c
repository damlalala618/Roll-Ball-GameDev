#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/gpio.h"

#define X ADC1_CHANNEL_4
#define Y ADC1_CHANNEL_3
#define SW GPIO_NUM_2

void app_main() {

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(X, ADC_ATTEN_DB_12);
    adc1_config_channel_atten(Y, ADC_ATTEN_DB_12);

    gpio_set_direction(SW, GPIO_MODE_INPUT);
    gpio_set_pull_mode(SW, GPIO_PULLUP_ONLY);

    while (1) {

        int x = adc1_get_raw(X);
        int y = adc1_get_raw(Y);

        int mid = 2000;
        int dead = 600;

        int dx = x - mid;
        int dy = y - mid;


        if (dx > dead) printf("R\n");
        else if (dx < -dead) printf("L\n");

        if (dy > dead) printf("D\n");
        else if (dy < -dead) printf("U\n");

        int sw = gpio_get_level(SW);
        vTaskDelay(pdMS_TO_TICKS(20));
        if (sw == 0 && gpio_get_level(SW) == 0) printf("C\n");

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}