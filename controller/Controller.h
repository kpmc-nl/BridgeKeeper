#ifndef BRIDGEKEEPER_CONTROLLER_H
#define BRIDGEKEEPER_CONTROLLER_H


#include "AngleSensor.h"
#include "State.h"
#include "Receiver.h"
#include "BridgeActuator.h"
#include "Pinout.h"

class Controller {


private:
    static AngleSensor angle_sensor;
    static Receiver receiver;
    static BridgeActuator bridge_actuator;
    static State target_state;
    static State current_state;
    static double up_target;
    static double down_target;



public:


    static void setup();

    static void update();

    static State getTargetState();

    static State getCurrentState();

    static double getDownTargetAngle();

    static double getUpTargetAngle();

    static void setTargetState(State state);

    static void setCurrentState(State state);

    static AngleSensor *getAngleSensor();

};


#endif //BRIDGEKEEPER_CONTROLLER_H
