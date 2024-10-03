#include <esp_log.h>
#include <esp_vfs.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <inttypes.h>
#include <stdio.h>

#include "include/sensors.h"

// void task1() {
//     while (1) {
//         printf("hello world\n");
//         vTaskDelay(pdMS_TO_TICKS(1000));
//     }
// }

void app_main() {
    gpio_init();
    i2c_init();
    uart_init();
    spi_init(LORA_SPI_HOST, CONFIG_LORA_MOSI_GPIO, CONFIG_LORA_MISO_GPIO, CONFIG_LORA_SCK_GPIO);
    spi_init(SD_SPI_HOST, CONFIG_SD_MOSI_GPIO, CONFIG_SD_MISO_GPIO, CONFIG_SD_SCK_GPIO);
    sensors_init();

    // xTaskCreate(task1, "task1", 2048, NULL, 4, NULL);
    xTimerStart(xTimerCreate("sensors_task", pdMS_TO_TICKS(500), pdTRUE, (void*)0, sensors_task), 0);
}
