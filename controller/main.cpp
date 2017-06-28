#include <Arduino.h>

#include <LiquidCrystal_I2C.h>
#include "MPU6050.h"

MPU6050 accelgyro;
double angleX, angleY, angleZ;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address


void getAngle(double *xTgt, double *yTgt, double *zTgt) {
    //TODO optimize this
    int16_t ax, ay, az;
    accelgyro.getAcceleration(&ax, &ay, &az);

    double x = ax;
    double y = ay;
    double z = az;

    double g = sqrt(x * x + y * y + z * z);

    *xTgt = acos(x / g) * 180 / M_PI;
    *yTgt = acos(y / g) * 180 / M_PI;
    *zTgt = acos(z / g) * 180 / M_PI;

}

void setup()
{

    lcd.begin(16,2);

    accelgyro.setDLPFMode(6);
    accelgyro.initialize();


    lcd.begin(16,2);
    lcd.print("Initialized");
}

void loop()
{
    getAngle(&angleX, &angleY, &angleZ);

    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(angleX);
    delay(100);
}


int main() {
    init();
    setup();

    while (true) {
        loop();
    }
}