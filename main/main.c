#include <esp_log.h>
#include <esp_vfs.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <inttypes.h>
#include <stdio.h>

#include "include/sensors.h"

void task1() {
    while (1) {
        printf("hello world\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task2() {

}

void app_main() { 

    xTaskCreate(task1, "task1", 2048, NULL, 4, NULL);
    xTaskCreate(task2, "task2", 2048, NULL, 5, NULL);
    
}
