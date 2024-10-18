#ifndef __SENSORS_T__
#define __SENSORS_T__

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <string.h>

#include "bmp280.h"
#include "comm.h"
#include "gps.h"
#include "imu.h"
#include "storage.h"
#include "fsm.h"

#define sensor_freq 100

void sensors_init();
void sensors_task();

#endif