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
        cur == Rising && tgt == Down ||
            (digitalRead(END_STOP) == LOW &&
             Controller::getAngleSensor()->getAngle() <= Controller::getDownTargetAngle() + 5)
            ) {
        digitalWrite(BOOST, HIGH);
        boost_time = millis();
    }

    if (boost_time + 500 < millis() || (tgt == Down && digitalRead(END_STOP) == LOW)) {
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
    cli();


    if(Controller::getTargetState() == Down){
        return 190 - map(Controller::getBatterySensor()->getVoltage(), BATT_EMPTY, BATT_FULL, 0, 62);
    }

//    return 128;
//    return 190 - map(Controller::getBatterySensor()->getVoltage(), BATT_EMPTY, BATT_FULL, 0, 62);
//    return 160 - map(Controller::getBatterySensor()->getVoltage(), BATT_EMPTY, BATT_FULL, 0, 32);


    double angle = Controller::getAngleSensor()->getAngle();
    double down = Controller::getDownTargetAngle();
    double up = Controller::getUpTargetAngle();

//    if(Controller::getTargetState() == Down && angle > up - 10){
//        return 128;
//    }

    double diff = min(abs(angle - down), abs(angle - up));

    long min = 128 - map(Controller::getBatterySensor()->getVoltage(), BATT_EMPTY, BATT_FULL, 0, 64);
    long max = min + 84;

    if(Controller::getTargetState() == Up){
        min += 25 - map(Controller::getBatterySensor()->getVoltage(), BATT_EMPTY, BATT_FULL, 0, 10);
    }

    int threshold = 10;
    if(Controller::getTargetState() == Down){
        threshold = 20;
    }

    if (diff > threshold) {
        return max;
    }

    uint8_t res =map(diff * 100, 0, threshold*100, min, max);
    sei();
    return res;
}
