#include "Controller.h"

UI Controller::ui = UI();
AngleSensor Controller::angle_sensor = AngleSensor();
Receiver Controller::receiver = Receiver();
BridgeActuator Controller::bridge_actuator = BridgeActuator();
State Controller::target_state = Down;
State Controller::current_state = Falling;

double Controller::up_target = 165;
double Controller::down_target = 90;
double Controller::manual_target = 0;

unsigned long Controller::last_intervention = 0;

Button Controller::upButton = Button(BTN_UP_PIN,
                                     Controller::targetUp,
                                     Controller::confirmUpTarget);

Button Controller::downButton = Button(BTN_DOWN_PIN,
                                       Controller::targetDown,
                                       Controller::confirmDownTarget);


void Controller::setup() {
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);

    receiver.setup();
    angle_sensor.setup();
    bridge_actuator.setup();
    upButton.setup();
    downButton.setup();
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

    upButton.update();
    downButton.update();

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
    return down_target;
}

double Controller::getUpTargetAngle() {
    return up_target;
}

double Controller::getManualTargetAngle() {
    return manual_target;
}

void Controller::setTargetState(State state) {
    target_state = state;
}

void Controller::setCurrentState(State state) {
    current_state = state;
}

UI *Controller::getUi() {
    return &ui;
}

AngleSensor *Controller::getAngleSensor() {
    return &angle_sensor;
}

void Controller::toManual() {
    if (Manual != current_state) {
        current_state = Manual;
        target_state = Manual;
        manual_target = angle_sensor.getAngle();
    }
}

void Controller::targetUp() {
    last_intervention = millis();
    toManual();
    manual_target += 0.3;
}

void Controller::targetDown() {
    toManual();
    manual_target -=0.3;
    last_intervention = millis();
}

void Controller::confirmUpTarget() {
    if (current_state == Manual) {
        up_target = manual_target;
        current_state = Up_L;
        target_state = Up_L;
        manual_target = 0;
    }
}

void Controller::confirmDownTarget() {
    if (current_state == Manual) {
        down_target = manual_target;
        current_state = Down;
        target_state = Down;
        manual_target = 0;
    }
}

unsigned long Controller::getLastIntervention() {
    return last_intervention;
}