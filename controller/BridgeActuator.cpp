//
// Created by matthijs on 7/19/17.
//

#include "BridgeActuator.h"
#include "Controller.h"
#include "Pinout.h"


void BridgeActuator::init() {

    pinMode(MOTOR_ENABLE, OUTPUT);
    pinMode(MOTOR_FWD, OUTPUT);
    pinMode(MOTOR_BACK, OUTPUT);

}

void BridgeActuator::update() {

    Controller *controller = Controller::getInstance();

    State tgt = controller->getTargetState();
    State cur = controller->getCurrentState();

    if (cur == tgt) {
        digitalWrite(MOTOR_ENABLE, LOW);
        digitalWrite(MOTOR_FWD, LOW);
        digitalWrite(MOTOR_BACK, LOW);

        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, HIGH);

    } else {
        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, LOW);

        switch (tgt) {
            case up:
//                analogWrite(MOTOR_FWD, getPower(angleY, downTargetAngle, 135));
                //  analogWrite(MOTOR_ENABLE, getPower(angleY, downTargetAngle, 135));
                digitalWrite(MOTOR_FWD, HIGH);
                digitalWrite(MOTOR_BACK, LOW);
                state = rising;
                if (angleY > 135) {
                    Serial.println("Bridge is up");
                    state = up;
                }

                break;
            case down:
//                analogWrite(MOTOR_ENABLE, getPower(angleY, 135, downTargetAngle));
//                analogWrite(MOTOR_BACK, getPower(angleY, 135, downTargetAngle));
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