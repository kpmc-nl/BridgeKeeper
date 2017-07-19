#ifndef BRIDGEKEEPER_CONTROLLER_H
#define BRIDGEKEEPER_CONTROLLER_H


#include "UI.h"
#include "AngleSensor.h"
#include "State.h"
#include "Receiver.h"
#include "BridgeActuator.h"

class Controller {

private:
    UI ui;
    AngleSensor angle_sensor;
    Receiver receiver;
    BridgeActuator bridge_actuator;
    State target_state;
    State current_state;

public:

    Controller();

    static Controller *getInstance();

    void setup();

    void update();

    State getTargetState();

    State getCurrentState();

    double getDownTargetAngle();

    double getUpTargetAngle();

    void setTargetState(State state);

    void setCurrentState(State state);

    UI *getUi();

    AngleSensor *getAngleSensor();


};


#endif //BRIDGEKEEPER_CONTROLLER_H
