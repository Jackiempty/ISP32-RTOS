#ifndef __IMU_H__
#define __IMU_H__

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <math.h>

#include "LSM6DSM.h"
#include "esp_system.h"

void imu_init();
void imu_update();
imu_t* imu_fetch();

#endif
