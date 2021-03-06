
#ifndef BRIDGEKEEPER_PINOUT_H
#define BRIDGEKEEPER_PINOUT_H

#define BATT_EMPTY 10000 // that'll do
#define BATT_FULL 15800 // aref is ~5.1v. Our divider gives 5.1v at 15.8v battery.

#define BATTERY_SENSOR A0
#define MOTOR_ENABLE 10
#define MOTOR_FWD 5
#define MOTOR_BACK 6
#define BOOST 11


#define END_STOP 3

#define NAV_L_1_PIN 7
#define NAV_L_2_PIN 9
#define RF_DATA_PIN 8

#define LED1_PIN 13
#define LED2_PIN 12

#endif //BRIDGEKEEPER_PINOUT_H
