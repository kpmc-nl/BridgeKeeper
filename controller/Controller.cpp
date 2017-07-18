#include "Controller.h"

static Controller instance;

Controller::Controller() {
    ui = UI();
    angle_sensor = AngleSensor();
    
    target_state = Down;
}

Controller *Controller::getInstance() {
    return &instance;
}

void Controller::setup() {
    ui.setup();
    receiver.setup();
    angle_sensor.setup();
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

void Controller::setTargetState(State state) {
    this->target_state = state;
}

UI *Controller::getUi() {
    return &ui;
}

AngleSensor *Controller::getAngleSensor() {
    return &angle_sensor;
}


