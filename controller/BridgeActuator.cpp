#include "BridgeActuator.h"
#include "Controller.h"
#include "Pinout.h"


void BridgeActuator::setup() {

    pinMode(MOTOR_ENABLE, OUTPUT);
    pinMode(MOTOR_FWD, OUTPUT);
    pinMode(MOTOR_BACK, OUTPUT);

}

void BridgeActuator::update() {


    State tgt = Controller::getTargetState();
    State cur = Controller::getCurrentState();


    if (cur == Manual) {

        double t = Controller::getManualTargetAngle();
        double a = Controller::getAngleSensor()->getAngle();

        if (abs(t - a) < 0.5) {
            stay();
        } else {
            digitalWrite(MOTOR_ENABLE, HIGH);
            if (t > a) {
                analogWrite(MOTOR_FWD, 128);
                digitalWrite(MOTOR_BACK, LOW);
            } else {
                digitalWrite(MOTOR_FWD, LOW);
                analogWrite(MOTOR_BACK, 128);
            }
        }

    } else if (cur == tgt) {
        stay();
        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, HIGH);
    } else {
        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, LOW);

        switch (tgt) {
            case Up_L:
            case Up_R:
                rise();
                break;
            case Down:
                fall();
                break;
        }
    }
}

void BridgeActuator::stay() {
    analogWrite(MOTOR_ENABLE, 0);
    digitalWrite(MOTOR_FWD, LOW);
    digitalWrite(MOTOR_BACK, LOW);
}

void BridgeActuator::rise() {
    digitalWrite(MOTOR_ENABLE, HIGH);
    analogWrite(MOTOR_FWD, getPower());
    digitalWrite(MOTOR_BACK, LOW);
    Controller::setCurrentState(Rising);
}

void BridgeActuator::fall() {
    digitalWrite(MOTOR_ENABLE, HIGH);
    digitalWrite(MOTOR_FWD, LOW);
    analogWrite(MOTOR_BACK, getPower());
    Controller::setCurrentState(Falling);
}

uint8_t BridgeActuator::getPower() {
    double angle = Controller::getAngleSensor()->getAngle();
    double down = Controller::getDownTargetAngle();
    double up = Controller::getUpTargetAngle();

    double diff = min(abs(angle - down), abs(angle - up));

    if (diff > 7.0) {
        return 128;
    }
    return map(diff * 100, 0, 700, 84, 128);
}
