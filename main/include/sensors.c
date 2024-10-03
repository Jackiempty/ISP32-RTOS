#include "sensors.h"

static pressure_sensor_t* pressure_altitude_instance;
static gps_t* gps_instance;

void sensors_init() {
    pressure_altitude_instance = bmp_fetch();
    gps_instance = gps_fetch();
    bmp280_init();
    gps_init();
}

void sensors_task(void *arg) {
    bmp280_update();
    printf("bmp280_altitude: %f\n", pressure_altitude_instance->relative_altitude);
    printf("bmp280_velocity: %f\n", pressure_altitude_instance->velocity);
    printf("gps_longitude: %ld\n", gps_instance->longitude);
    printf("gps_latitude: %ld\n", gps_instance->latitude);
    printf("gps_altitude: %f\n", gps_instance->altitude);
}