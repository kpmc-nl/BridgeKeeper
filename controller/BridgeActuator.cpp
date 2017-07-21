#include "BridgeActuator.h"
#include "Controller.h"
#include "Pinout.h"


void BridgeActuator::setup() {

    pinMode(MOTOR_ENABLE, OUTPUT);
    pinMode(MOTOR_FWD, OUTPUT);
    pinMode(MOTOR_BACK, OUTPUT);

}

void BridgeActuator::update() {

    Controller *controller = Controller::getInstance();

    State tgt = controller->getTargetState();
    State cur = controller->getCurrentState();

    if (cur == tgt) {
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
    Controller::getInstance()->setCurrentState(Rising);
}

void BridgeActuator::fall() {
    digitalWrite(MOTOR_ENABLE, HIGH);
    digitalWrite(MOTOR_FWD, LOW);
    analogWrite(MOTOR_BACK, getPower());
    Controller::getInstance()->setCurrentState(Falling);
}

uint8_t BridgeActuator::getPower() {
    Controller *controller = Controller::getInstance();
    double angle = controller->getAngleSensor()->getAngle();
    double down = controller->getDownTargetAngle();
    double up = controller->getUpTargetAngle();

    double diff = min(abs(angle - down), abs(angle - up));

    if(diff > 7.0){
        return 128;
    }
    return map(diff * 100, 0, 700, 78, 128);
}
