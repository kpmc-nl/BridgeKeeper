#ifndef BRIDGEKEEPER_CONTROLLER_H
#define BRIDGEKEEPER_CONTROLLER_H


#include "UI.h"
#include "AngleSensor.h"
#include "State.h"
#include "Receiver.h"
#include "BridgeActuator.h"
#include "Button.h"
#include "Pinout.h"

class Controller {


private:
    static UI ui;
    static AngleSensor angle_sensor;
    static Receiver receiver;
    static BridgeActuator bridge_actuator;
    static State target_state;
    static State current_state;
    static double up_target;
    static double down_target;
    static double manual_target;
    static Button upButton;
    static Button downButton;

public:


    static void setup();

    static void update();

    static State getTargetState();

    static State getCurrentState();

    static double getDownTargetAngle();

    static double getUpTargetAngle();

    static double getManualTargetAngle();

    static void setTargetState(State state);

    static void setCurrentState(State state);

    static UI *getUi();

    static AngleSensor *getAngleSensor();

    static void toManual();

    static void targetUp();

    static void targetDown();

    static void confirmUpTarget();

    static void confirmDownTarget();

};


#endif //BRIDGEKEEPER_CONTROLLER_H
