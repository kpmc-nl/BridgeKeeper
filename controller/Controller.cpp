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

void Controller::setup() {
    receiver.setup();
    angle_sensor.setup();
    bridge_actuator.setup();
    ui.setup();
}

void Controller::update() {
    angle_sensor.update();

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


    if (millis() % 100 == 0) {
        ui.update();
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


