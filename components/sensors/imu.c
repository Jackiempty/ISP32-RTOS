#include "imu.h"

static calibration_t cal = {._ascale = AFS_16G,
                            ._gscale = GFS_2000DPS,
                            ._aodr = ODR_6660Hz,
                            ._godr = ODR_6660Hz,
                            ._ares = 0,
                            ._gres = 0,
                            ._accelBias = {0, 0, 0},
                            ._gyroBias = {0, 0, 0}};
static imu_t imu_instance;

void imu_init() {
  /* Init the MPU and AHRS */
  printf("IMU init...\n");
  lsm6dsm_init(&cal);
  MadgwickAHRSinit(100, 0.8);
  imu_instance.freq = 100;
  imu_instance.velocity.x = 0;
  imu_instance.velocity.y = 0;
  imu_instance.velocity.z = 0;
  imu_instance.heading = 0;
  imu_instance.pitch = 0;
  imu_instance.roll = 0;

  /* Start timer task for precise frequency */
  xTimerStart(xTimerCreate("imu_update", pdMS_TO_TICKS(10), pdTRUE, (void *)0, imu_update), 0);
}

void imu_update() {
  readData(&imu_instance, &cal);
  // Apply the AHRS algorithm
  MadgwickAHRSupdate(DEG2RAD(imu_instance.g.x), DEG2RAD(imu_instance.g.y), DEG2RAD(imu_instance.g.z), imu_instance.a.x, imu_instance.a.y,
                     imu_instance.a.z, 0, 0, 0);

  MadgwickGetEulerAnglesDegrees(&imu_instance.heading, &imu_instance.pitch, &imu_instance.roll);
  imu_instance.velocity.x += imu_instance.a.x / imu_instance.freq;
  imu_instance.velocity.y += imu_instance.a.y / imu_instance.freq;
  imu_instance.velocity.z += imu_instance.a.z / imu_instance.freq;
}

imu_t *imu_fetch() { return &imu_instance; }
