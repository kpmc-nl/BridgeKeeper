#ifndef BRIDGEKEEPER_CONTROLLER_H
#define BRIDGEKEEPER_CONTROLLER_H


#include "UI.h"
#include "AngleSensor.h"
#include "State.h"
#include "Receiver.h"

class Controller {

private:
    UI ui;
    AngleSensor angle_sensor;
    Receiver receiver;
    State target_state;

public:

    Controller();

    static Controller *getInstance();

    void setup();

    void update();

    State getTargetState();

    void setTargetState(State state);

    UI *getUi();

    AngleSensor *getAngleSensor();


};


#endif //BRIDGEKEEPER_CONTROLLER_H
