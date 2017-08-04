#include "Controller.h"

static Controller instance;

Controller::Controller() {
    ui = UI();
    angle_sensor = AngleSensor();
    bridge_actuator = BridgeActuator();

    target_state = Down;
    current_state = Falling;
}

Controller *Controller::getInstance() {
    return &instance;
}

void blink(int count) {
    for (int i = 0; i < count; i++) {
        digitalWrite(12, HIGH);
        delay(100);
        digitalWrite(12, LOW);
        delay(100);
    }
//    delay(1000);
}


void Controller::setup() {
//    blink(1);
    receiver.setup();
//    blink(2);
    angle_sensor.setup();
//    blink(3);
    bridge_actuator.setup();
//    blink(4);
    ui.setup();
//    blink(5);
}

void Controller::update() {
    angle_sensor.update();

//    blink(4);
//delay(1000);

    receiver.update();

    switch (target_state) {
        case Up_L:
        case Up_R:
            if (angle_sensor.getAngle() >= getUpTargetAngle()) {
                current_state = target_state;
            }
            break;

        case Down:
            if (angle_sensor.getAngle() <= getDownTargetAngle()) {
                current_state = target_state;
            }
            break;
    }

    bridge_actuator.update();

    // always update ui the last

    if (millis() % 100 == 0) {
//        blink(1);

//        cli();
//        delay(100);
        ui.update();
//        sei();
    }
}

State Controller::getTargetState() {
    return target_state;
}

State Controller::getCurrentState() {
    return current_state;
}

double Controller::getDownTargetAngle() {
    return 90;
}

double Controller::getUpTargetAngle() {
    return 150;
}

void Controller::setTargetState(State state) {
    this->target_state = state;
}

void Controller::setCurrentState(State state) {
    this->current_state = state;
}

UI *Controller::getUi() {
    return &ui;
}

AngleSensor *Controller::getAngleSensor() {
    return &angle_sensor;
}


