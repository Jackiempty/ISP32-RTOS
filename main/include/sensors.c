#include "sensors.h"

static pressure_sensor_t* pressure_altitude_instance;
static gps_t* gps_instance;
static imu_t* imu_instance;

#define TAG "sensors"

void sensors_init() {
  pressure_altitude_instance = bmp_fetch();
  gps_instance = gps_fetch();
  imu_instance = imu_fetch();
  // All sensors' update tasks are created in each init()
  bmp280_init();
  imu_init();
  gps_init();
}

void sensors_task() {
  while (1) {
    static uint32_t systick;
    systick = bsp_current_time();
    printf("bmp280_altitude: %f\n", pressure_altitude_instance->relative_altitude);
    printf("bmp280_velocity: %f\n", pressure_altitude_instance->velocity);
    printf("gps_longitude: %ld\n", gps_instance->longitude);
    printf("gps_latitude: %ld\n", gps_instance->latitude);
    printf("gps_altitude: %f\n", gps_instance->altitude);
    printf("imu_accel: x: %f, y: %f, z: %f\n", imu_instance->a.x, imu_instance->a.y, imu_instance->a.z);
    printf("imu_gyro: x: %f, y: %f, z: %f\n", imu_instance->g.x, imu_instance->g.y, imu_instance->g.z);
    printf("----------------------------------------------\n");
    ESP_LOGI(TAG, "%lu, %f, %f, %ld, %ld, %f, %f, %f, %f, %f, %f, %f\n", systick, pressure_altitude_instance->relative_altitude,
             pressure_altitude_instance->velocity, gps_instance->longitude, gps_instance->latitude, gps_instance->altitude, imu_instance->a.x,
             imu_instance->a.y, imu_instance->a.z, imu_instance->g.x, imu_instance->g.y, imu_instance->g.z);

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}