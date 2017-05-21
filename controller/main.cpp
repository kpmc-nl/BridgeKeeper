

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project

#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "math.h"
#include "Wire.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;


void setup() {
    Wire.begin();

    Serial.begin(38400);
    Serial.println("Initializing I2C devices...");
    accelgyro.setDLPFMode(6);
    accelgyro.initialize();



    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ?
                   "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
    // read raw accel/gyro measurements from device
//    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // these methods (and a few others) are also available

    accelgyro.getAccelFIFOEnabled();
    accelgyro.getAcceleration(&ax, &ay, &az);
    accelgyro.getRotation(&gx, &gy, &gz);


    double x = ax;
    double y = ay;
    double z = az;

    double g = sqrt(x*x+y*y+z*z);

    double alpha = acos(x/g);
    double beta = acos(y/g);
    double gamma = acos(z/g);

    alpha = alpha * 180 / M_PI;
    beta = beta * 180 / M_PI;
    gamma = gamma * 180 / M_PI;

    Serial.print(alpha);
    Serial.print("\t");
    Serial.print(beta);
    Serial.print("\t");
    Serial.println(gamma);

    delay(500);
}





int main(){
    init();
    setup();
    while(1){
        loop();
    }
}