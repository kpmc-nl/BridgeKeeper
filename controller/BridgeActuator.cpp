#include "BridgeActuator.h"
#include "Controller.h"
#include "Pinout.h"


void BridgeActuator::setup() {

    pinMode(MOTOR_ENABLE, OUTPUT);
    pinMode(MOTOR_FWD, OUTPUT);
    pinMode(MOTOR_BACK, OUTPUT);
    pinMode(BOOST, OUTPUT);

    boost_time = 0;
}


void BridgeActuator::update() {
    State tgt = Controller::getTargetState();
    State cur = Controller::getCurrentState();

    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);

    if (tgt == Up ||
        cur == Idle && tgt != Idle ||
        cur == Rising && tgt == Down) {
        digitalWrite(BOOST, HIGH);
        boost_time = millis();
    }
    if (boost_time + 500 < millis()) {
        digitalWrite(BOOST, LOW);
    }

    switch (tgt) {
        case Idle:
        default:
            stay();
            break;
//            case Up_L:
//            case Up_R:
        case Up:
            digitalWrite(LED1_PIN, HIGH);
            rise();
            break;
        case Down:
            digitalWrite(LED2_PIN, HIGH);
            fall();
            break;
    }
}

void BridgeActuator::stay() {
    digitalWrite(MOTOR_ENABLE, LOW);
    digitalWrite(MOTOR_FWD, LOW);
    digitalWrite(MOTOR_BACK, LOW);
    Controller::setCurrentState(Idle);
}

void BridgeActuator::rise() {
    analogWrite(MOTOR_ENABLE, getPower());
    digitalWrite(MOTOR_FWD, HIGH);
    digitalWrite(MOTOR_BACK, LOW);
    Controller::setCurrentState(Rising);
}

void BridgeActuator::fall() {
    analogWrite(MOTOR_ENABLE, getPower());
    digitalWrite(MOTOR_FWD, LOW);
    digitalWrite(MOTOR_BACK, HIGH);
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
    return map(diff * 100, 0, 700, 100, 128);
}
