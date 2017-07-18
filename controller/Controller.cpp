#include "Controller.h"

static Controller instance;

Controller::Controller() {
    ui = UI();
    angleSensor = AngleSensor();
}

Controller *Controller::getInstance() {
    return &instance;
}

void Controller::init() {
    ui.init();
    angleSensor.init();
}

void Controller::update() {
    angleSensor.update();

    // always update ui the last
    ui.update();
}


UI *Controller::getUi() {
    return &ui;
}

AngleSensor *Controller::getAngleSensor() {
    return &angleSensor;
}