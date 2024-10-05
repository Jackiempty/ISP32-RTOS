#include "imu.h"

// const static vector_t rot = {
//     .x = 90.0 * (M_PI) / 180.0,
//     .y = 0.0 * (M_PI) / 180.0,
//     .z = 90.0 * (M_PI) / 180.0,
// };

static calibration_t cal = {._ascale = AFS_16G,
                            ._gscale = GFS_2000DPS,
                            ._aodr = ODR_6660Hz,
                            ._godr = ODR_6660Hz,
                            ._ares = 0,
                            ._gres = 0,
                            ._accelBias = {0, 0, 0},
                            ._gyroBias = {0, 0, 0}};
static imu_t imu_instance;
// static float rotation[3][3] = {
//     {1, 0, 0},
//     {0, 1, 0},
//     {0, 0, 1},
// };

void imu_init() {
    /* Init the MPU and AHRS */
    lsm6dsm_init(&cal);
    // MadgwickAHRSinit(100, 0.8);
    // imu_instance.freq = frequency;
    imu_instance.velocity.x = 0;
    imu_instance.velocity.y = 0;
    imu_instance.velocity.z = 0;
    imu_instance.heading = 0;
    imu_instance.pitch = 0;
    imu_instance.roll = 0;
}

void imu_update() { readData(&imu_instance, &cal); }

imu_t *imu_fetch() { return &imu_instance; }
