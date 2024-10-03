#ifndef __SENSORS_T__
#define __SENSORS_T__

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <string.h>

#include "bmp280.h"

#define sensor_freq 100

void sensors_init(void *);
void sensors_task(void *);

#endif