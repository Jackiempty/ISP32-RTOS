#include "recv.h"

#include <stddef.h>
#include <stdint.h>

// #include "common.h"

#define TAG "RECV"

#define RECV_LEN 255

void recv_task(void* args) {
  uint8_t data[RECV_LEN];
  size_t len;
  uint8_t led_status = 0;

  fsm_state_e state;
  uint32_t systick;
  float pressure_altitude;
  float pressure_velocity;
  vector_t acceleration;
  vector_t gyro;
  int32_t latitude;
  int32_t longitude;
  float gps_altitude;
  float heading, pitch, roll;
  int8_t rssi;

  for (;;) {
    if ((len = LoRaReceive(&data[0], RECV_LEN)) > 0) {
      uint8_t* logger_ptr = data;

      memcpy(&state, logger_ptr, sizeof(fsm_state_e));
      logger_ptr += sizeof(fsm_state_e);

      memcpy(&systick, logger_ptr, sizeof(systick));
      logger_ptr += sizeof(systick);

      memcpy(&pressure_altitude, logger_ptr, sizeof(pressure_altitude));
      logger_ptr += sizeof(pressure_altitude);

      memcpy(&pressure_velocity, logger_ptr, sizeof(pressure_velocity));
      logger_ptr += sizeof(pressure_velocity);

      memcpy(&acceleration, logger_ptr, sizeof(acceleration));
      logger_ptr += sizeof(acceleration);

      memcpy(&gyro, logger_ptr, sizeof(gyro));
      logger_ptr += sizeof(gyro);

      memcpy(&longitude, logger_ptr, sizeof(longitude));
      logger_ptr += sizeof(longitude);

      memcpy(&latitude, logger_ptr, sizeof(latitude));
      logger_ptr += sizeof(latitude);

      memcpy(&gps_altitude, logger_ptr, sizeof(gps_altitude));
      logger_ptr += sizeof(gps_altitude);

      memcpy(&roll, logger_ptr, sizeof(roll));
      logger_ptr += sizeof(roll);

      memcpy(&pitch, logger_ptr, sizeof(pitch));
      logger_ptr += sizeof(pitch);

      memcpy(&heading, logger_ptr, sizeof(heading));
      logger_ptr += sizeof(heading);

      uint8_t ecc = 0;
      for (size_t i = 0; i < logger_ptr - &data[0]; i++) {
        ecc = ecc ^ data[i];
      }

      uint8_t tx_ecc;
      memcpy(&tx_ecc, logger_ptr, sizeof(tx_ecc));
      logger_ptr += sizeof(tx_ecc);

      rssi = GetRssiInst();
      if (tx_ecc == ecc) {
        // printf(">>>%u, %lu, %f, %f, %ld, %ld, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n<<<\n",
        //        state, systick, pressure_altitude,
        //        pressure_velocity,
        //        longitude, latitude, gps_altitude,
        //        acceleration.x, acceleration.y, acceleration.z,
        //        gyro.x, gyro.y, gyro.z,
        //        roll, pitch, heading);

        printf("run_time: %lu\n", systick);
        printf("lora_rssi: %d\n", rssi);
        printf("bmp280_altitude: %f\n", pressure_altitude);
        printf("bmp280_velocity: %f\n", pressure_velocity);
        printf("gps_longitude: %ld\n", longitude);
        printf("gps_latitude: %ld\n", latitude);
        printf("gps_altitude: %f\n", gps_altitude);
        printf("imu_accel: x: %f, y: %f, z: %f\n", acceleration.x, acceleration.y, acceleration.z);
        printf("imu_gyro: x: %f, y: %f, z: %f\n", gyro.x, gyro.y, gyro.z);
        printf("imu_position: roll: %f, pitch: %f, heading: %f\n", roll, pitch, heading);
        printf("----------------------------------------------\n");

        gpio_set_level(CONFIG_INDI_LED, led_status);
        led_status = !led_status;
      }
    }
  }
}
