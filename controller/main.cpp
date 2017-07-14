#include <Arduino.h>
#include <BridgeKeeper.h>
#include <MPU6050.h>
#include "Manchester.h"

Manchester pole1_manchester;
Manchester remote_rx_manchester;

MPU6050 accelgyro;

double angleX, angleY, angleZ;

double downTargetAngle = 90;

#define MOTOR_ENABLE 3
#define MOTOR_FWD 5
#define MOTOR_BACK 6

#define NAV_L_1_PIN 7
#define NAV_L_2_PIN 9
#define RF_DATA_PIN 8

#define LED1_PIN 12
#define LED2_PIN 13

lightpole_msg_t pole1;
remote_msg_t remote_msg;
uint8_t rx_buf[sizeof(remote_msg_t) + 1];

enum State {
    up, down, rising, falling
};

State state;
State target;

void setup() {

    pinMode(MOTOR_ENABLE, OUTPUT);
    pinMode(MOTOR_FWD, OUTPUT);
    pinMode(MOTOR_BACK, OUTPUT);

    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(NAV_L_1_PIN, OUTPUT);
    pinMode(NAV_L_2_PIN, OUTPUT);

    Serial.begin(38400);
    Serial.print("Initializing...");


    Serial.println("Initializing I2C devices...");
    accelgyro.setDLPFMode(6);
    accelgyro.initialize();

    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ?
                   "MPU6050 connection successful" : "MPU6050 connection failed");

    Serial.println("Initializing states...");
    state = down;
    target = down;

    Serial.println("Initializing remote manchester...");
    remote_rx_manchester.setupReceive(RF_DATA_PIN, MAN_300);
    remote_rx_manchester.beginReceiveArray(sizeof(remote_msg_t) + 1, rx_buf);

    Serial.println("Initializing pole1 manchester...");
    pole1_manchester.setupTransmit(NAV_L_1_PIN, MAN_300);

    Serial.println("Initialized.");
}

void transmit() {
    uint8_t buf[sizeof(lightpole_msg_t) + 1];
    buf[0] = sizeof(lightpole_msg_t) + 1;

    memcpy(buf + 1, &pole1, sizeof(lightpole_msg_t));
    pole1_manchester.transmitArray(sizeof(lightpole_msg_t) + 1, buf);

//    digitalWrite(13, HIGH);
//    delay(100);
//    digitalWrite(13, LOW);
}

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

//    Serial.println("angles:\t");
//    Serial.print(*xTgt);
//    Serial.print("\t");
//    Serial.print(*yTgt);
//    Serial.print("\t");
//    Serial.println(*zTgt);
}

void readTargetPot() {
//    double tgt = map(analogRead(A0), 0, 1023, 850, 950);
//    tgt /= 10.0;
//
//    if (tgt != downTargetAngle) {
//        Serial.print("new target:");
//        Serial.println(tgt);
//        target = down;
//        state = falling;
//        downTargetAngle = tgt;
//    }
}

uint8_t getPower(double angle, double start, double end) {
    double diff = min(abs(angle - start), abs(angle - end));

    if (diff > 7.0) {
        return 128;
    }
    return map(diff * 100, 0, 700, 78, 128);
}

void receive(){
    if (remote_rx_manchester.receiveComplete()) {

        if (rx_buf[0] != sizeof(remote_msg_t) + 1) {
            /* ignore */
            goto b_rx;
        }

        if(state != target){
            /* ignore input, we are working :) */
            goto b_rx;
        }

        memcpy(&remote_msg, rx_buf + 1, sizeof(remote_msg_t));

        if (remote_msg.button1) {
            target = up;
            Serial.println("want up");
        } else if (remote_msg.button2) {
            target = down;
            Serial.println("want down");
        } else if (remote_msg.button3) {
            target = up;
            Serial.println("want up");
        }

//        transmit(); TODO enable when adding lights back

        b_rx:
        remote_rx_manchester.beginReceiveArray(sizeof(remote_msg_t) + 1, rx_buf);
    }
}

void loop() {

    readTargetPot();

    receive();

    getAngle(&angleX, &angleY, &angleZ);

    if (state == target) {
        digitalWrite(MOTOR_ENABLE, LOW);
        digitalWrite(MOTOR_FWD, LOW);
        digitalWrite(MOTOR_BACK, LOW);

        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, HIGH);

    } else {
        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, LOW);

        switch (target) {
            case up:
                analogWrite(MOTOR_ENABLE, getPower(angleY, downTargetAngle, 135));
                digitalWrite(MOTOR_FWD, HIGH);
                digitalWrite(MOTOR_BACK, LOW);
                state = rising;
                if (angleY > 135) {
                    Serial.println("Bridge is up");
                    state = up;
                }

                break;
            case down:
                analogWrite(MOTOR_ENABLE, getPower(angleY, 135, downTargetAngle));
                digitalWrite(MOTOR_FWD, LOW);
                digitalWrite(MOTOR_BACK, HIGH);
                state = falling;
                if (angleY < downTargetAngle) {
                    Serial.println("Bridge is down");
                    state = down;
                }

                break;
        }
    }

}


int main() {
    init();
    setup();

    while (true) {
        loop();
        Serial.print("angle: ");
        Serial.print(angleY);
        Serial.println();
        delay(500);
    }
}