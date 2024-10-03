#include "sensors.h"

static pressure_sensor_t* pressure_altitude_instance;

void sensors_init(void *arg) {
    pressure_altitude_instance = bmp_fetch();
    bmp280_init();
}

void sensors_task(void *arg) {
    bmp280_update();
    printf("altitude: %d\n", pressure_altitude_instance->relative_altitude);
    printf("velocity: %d\n", pressure_altitude_instance->velocity);
}