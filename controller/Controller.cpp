#include "Controller.h"

AngleSensor Controller::angle_sensor = AngleSensor();
Receiver Controller::receiver = Receiver();
BridgeActuator Controller::bridge_actuator = BridgeActuator();
State Controller::target_state = Idle;
State Controller::current_state = Idle;

#define UP_ANGLE_DIFF 70

double Controller::down_target = 90;
double Controller::up_target = Controller::down_target + UP_ANGLE_DIFF;


void Controller::setup() {
    receiver.setup();
    angle_sensor.setup();;
    bridge_actuator.setup();

    pinMode(END_STOP, INPUT_PULLUP);
}

unsigned long fb_time =0;
bool fb_active = false;

void Controller::update() {
    angle_sensor.update();

    receiver.update();

    switch (target_state) {
//        case Up_L:
//        case Up_R:
        case Up:
            if (angle_sensor.getAngle() >= getUpTargetAngle()) {
                target_state = Idle;
            }
            break;

        case Down:
//            if (angle_sensor.getAngle() <= getDownTargetAngle()) {
//                target_state = Idle;
//            }

            bool fb =  digitalRead(END_STOP) == LOW;

            if(!fb_active && fb){
                fb_active = true;
                fb_time = millis();
            }
            if(!fb){
                fb_active = false;
            }

            if(fb_active && fb_time + 500 < millis()){
                target_state = Idle;
                down_target = angle_sensor.getAngle();
                up_target = down_target + UP_ANGLE_DIFF;
            }


            break;
    }



    bridge_actuator.update();
}

State Controller::getTargetState() {
    return target_state;
}

State Controller::getCurrentState() {
    return current_state;
}

double Controller::getDownTargetAngle() {
    return down_target;
}

double Controller::getUpTargetAngle() {
    return up_target;
}

void Controller::setTargetState(State state) {
    target_state = state;
}

void Controller::setCurrentState(State state) {
    current_state = state;
}

AngleSensor *Controller::getAngleSensor() {
    return &angle_sensor;
}