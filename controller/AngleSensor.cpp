#include "AngleSensor.h"

#define MPU6050_ADDRESS 0x68

AngleSensor::AngleSensor() {
    accelgyro = MPU6050(MPU6050_ADDRESS);
    angle = 90.0;
}

void AngleSensor::setup() {
    accelgyro.setDLPFMode(6);
    accelgyro.initialize();
}

void AngleSensor::update() {
    int16_t ax, ay, az;
    accelgyro.getAcceleration(&ax, &ay, &az);

    double x = ax;
    double y = ay;
    double z = az;

    double g = sqrt(x * x + y * y + z * z);

    // we are only interested in the Y angle
    this->angle = acos(y / g) * 180 / M_PI;
}

double AngleSensor::getAngle() {
    return 180-angle;
//    return angle;
}