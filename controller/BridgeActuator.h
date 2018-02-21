//
// Created by matthijs on 7/19/17.
//

#ifndef BRIDGEKEEPER_BRIDGEACTUATOR_H
#define BRIDGEKEEPER_BRIDGEACTUATOR_H

#include <stdio.h>

class BridgeActuator {

private:
    unsigned long boost_time;


public:
    void setup();

    void update();

private:
    void rise();

    void fall();

    void stay();

    uint8_t getPower();

};


#endif //BRIDGEKEEPER_BRIDGEACTUATOR_H
