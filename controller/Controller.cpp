#include "Controller.h"

static Controller instance;

Controller::Controller() {
    ui = UI();
    angle_sensor = AngleSensor();

    target_state = Down;
    current_state = Falling;
}

Controller *Controller::getInstance() {
    return &instance;
}

void Controller::setup() {
    receiver.setup();
    angle_sensor.setup();
    ui.setup();
}

void Controller::update() {
    angle_sensor.update();
    receiver.update();

    // always update ui the last
    ui.update();
}

State Controller::getTargetState() {
    return target_state;
}

State Controller::getCurrentState() {
    return current_state;
}

void Controller::setTargetState(State state) {
    this->target_state = state;
}

UI *Controller::getUi() {
    return &ui;
}

AngleSensor *Controller::getAngleSensor() {
    return &angle_sensor;
}


