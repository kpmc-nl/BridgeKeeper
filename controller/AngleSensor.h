#ifndef BRIDGEKEEPER_ANGLESENSOR_H
#define BRIDGEKEEPER_ANGLESENSOR_H


#include <MPU6050.h>

class AngleSensor {

private:
    MPU6050 accelgyro;
    double angle;

public:
    AngleSensor();

    void setup();

    void update();

    double getAngle();


};


#endif //BRIDGEKEEPER_ANGLESENSOR_H
