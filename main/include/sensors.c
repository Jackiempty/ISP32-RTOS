#include "sensors.h"

static uint8_t* comm_buffer;
static pressure_sensor_t* pressure_altitude_instance;
static gps_t* gps_instance;
static imu_t* imu_instance;
static uint32_t systick;
static fsm_state_e* state;

#define TAG "sensors"

static inline void comm_dump();

void sensors_init() {
  comm_buffer = comm_fetch();
  pressure_altitude_instance = bmp_fetch();
  gps_instance = gps_fetch();
  imu_instance = imu_fetch();
  state = fsm_fetch();
  // All sensors' update tasks are created in each init()
  bmp280_init();
  imu_init();
  gps_init();
}

void sensors_task() {
  while (1) {
    systick = bsp_current_time();
    comm_dump();
    ESP_LOGI(TAG, "%u, %lu, %f, %f, %ld, %ld, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n", *state, systick, pressure_altitude_instance->relative_altitude,
             pressure_altitude_instance->velocity, gps_instance->longitude, gps_instance->latitude, gps_instance->altitude,
             imu_instance->a.x, imu_instance->a.y, imu_instance->a.z, imu_instance->g.x, imu_instance->g.y, imu_instance->g.z,
             imu_instance->roll, imu_instance->pitch, imu_instance->heading);

    vTaskDelay(pdMS_TO_TICKS(250));
  }
}

static void comm_dump() {
  uint8_t* logger_ptr = comm_buffer;

  memcpy(logger_ptr, &state, sizeof(fsm_state_e));
  logger_ptr += sizeof(fsm_state_e);
  
  memcpy(logger_ptr, &systick, sizeof(systick));
  logger_ptr += sizeof(systick);

  memcpy(logger_ptr, &pressure_altitude_instance->relative_altitude, sizeof(pressure_altitude_instance->relative_altitude));
  logger_ptr += sizeof(pressure_altitude_instance->relative_altitude);

  memcpy(logger_ptr, &pressure_altitude_instance->velocity, sizeof(pressure_altitude_instance->velocity));
  logger_ptr += sizeof(pressure_altitude_instance->velocity);

  memcpy(logger_ptr, &imu_instance->a, sizeof(imu_instance->a));
  logger_ptr += sizeof(imu_instance->a);

  memcpy(logger_ptr, &imu_instance->g, sizeof(imu_instance->g));
  logger_ptr += sizeof(imu_instance->g);

  memcpy(logger_ptr, &gps_instance->longitude, sizeof(gps_instance->longitude));
  logger_ptr += sizeof(gps_instance->longitude);

  memcpy(logger_ptr, &gps_instance->latitude, sizeof(gps_instance->latitude));
  logger_ptr += sizeof(gps_instance->latitude);

  memcpy(logger_ptr, &gps_instance->altitude, sizeof(gps_instance->altitude));
  logger_ptr += sizeof(gps_instance->altitude);

  memcpy(logger_ptr, &imu_instance->roll, sizeof(imu_instance->roll));
  logger_ptr += sizeof(imu_instance->roll);

  memcpy(logger_ptr, &imu_instance->pitch, sizeof(imu_instance->pitch));
  logger_ptr += sizeof(imu_instance->pitch);

  memcpy(logger_ptr, &imu_instance->heading, sizeof(imu_instance->heading));
  logger_ptr += sizeof(imu_instance->heading);

  uint8_t ecc = 0;
  for (size_t i = 0; i < logger_ptr - comm_buffer; i++) {
    ecc = ecc ^ comm_buffer[i];
  }
  memcpy(logger_ptr, &ecc, sizeof(ecc));
  logger_ptr += sizeof(ecc);
}

void sensors_print() {
  while(1) {
    printf("bmp280_altitude: %f\n", pressure_altitude_instance->relative_altitude);
    printf("bmp280_velocity: %f\n", pressure_altitude_instance->velocity);
    printf("gps_longitude: %ld\n", gps_instance->longitude);
    printf("gps_latitude: %ld\n", gps_instance->latitude);
    printf("gps_altitude: %f\n", gps_instance->altitude);
    printf("imu_accel: x: %f, y: %f, z: %f\n", imu_instance->a.x, imu_instance->a.y, imu_instance->a.z);
    printf("imu_gyro: x: %f, y: %f, z: %f\n", imu_instance->g.x, imu_instance->g.y, imu_instance->g.z);
    printf("imu_position: roll: %f, pitch: %f, heading: %f\n", imu_instance->roll, imu_instance->pitch, imu_instance->heading);
    printf("----------------------------------------------\n");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
  
}