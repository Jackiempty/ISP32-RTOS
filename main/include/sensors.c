#include "sensors.h"

static pressure_sensor_t* pressure_altitude_instance;
static gps_t* gps_instance;
static imu_t* imu_instance;

void sensors_init() {
  pressure_altitude_instance = bmp_fetch();
  gps_instance = gps_fetch();
  imu_instance = imu_fetch();
  bmp280_init();
  imu_init();
  gps_init();
}

void sensors_task(void* arg) {
  bmp280_update();
  imu_update();
  printf("bmp280_altitude: %f\n", pressure_altitude_instance->relative_altitude);
  printf("bmp280_velocity: %f\n", pressure_altitude_instance->velocity);
  printf("gps_longitude: %ld\n", gps_instance->longitude);
  printf("gps_latitude: %ld\n", gps_instance->latitude);
  printf("gps_altitude: %f\n", gps_instance->altitude);
  printf("imu_accel: x: %f, y: %f, z: %f\n", imu_instance->a.x, imu_instance->a.y, imu_instance->a.z);
  printf("imu_gyro: x: %f, y: %f, z: %f\n", imu_instance->g.x, imu_instance->g.y, imu_instance->g.z);
  printf("----------------------------------------------\n");
}