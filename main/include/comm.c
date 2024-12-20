#include "comm.h"

#define TAG "LOGGER"

static uint8_t led_state = 0;
static uint8_t buffer[128];

void comm_task(void* args) {
  uint8_t* commu_buffer = &buffer[0];
  while (1) {
    gpio_set_level(CONFIG_INDI_LED, led_state);
    led_state = !led_state;
    LoRaSend(commu_buffer, comm_len(), SX126x_TXMODE_SYNC);
    vTaskDelay(pdMS_TO_TICKS(300));
  }
}

uint8_t* comm_fetch() { return &buffer[0]; }

size_t comm_len() { return sizeof(buffer); }
