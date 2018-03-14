#include "Controller.h"

AngleSensor Controller::angle_sensor = AngleSensor();
Receiver Controller::receiver = Receiver();
BridgeActuator Controller::bridge_actuator = BridgeActuator();
BatterySensor Controller::battery_sensor = BatterySensor();
State Controller::target_state = Idle;
State Controller::current_state = Idle;

#define UP_ANGLE_DIFF 60

double Controller::down_target = 80;
double Controller::up_target = 150;


void Controller::setup() {
    receiver.setup();
    angle_sensor.setup();;
    bridge_actuator.setup();
    battery_sensor.setup();
    pinMode(END_STOP, INPUT_PULLUP);

    if(digitalRead(END_STOP) == LOW){
        down_target = angle_sensor.getAngle();
        up_target = down_target + UP_ANGLE_DIFF;
    }

}

unsigned long fb_time =0;
bool fb_active = false;

void Controller::update() {
    battery_sensor.update();
    while(battery_sensor.getVoltage() < BATT_EMPTY){
        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, LOW);
        delay(100);
        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, HIGH);
        delay(100);
        battery_sensor.update();
    }

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

            if(fb_active && fb_time + 800 < millis()){
                target_state = Idle;
                angle_sensor.update();
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

BatterySensor* Controller::getBatterySensor() {
    return &battery_sensor;
}