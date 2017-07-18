//
// Created by Matthijs Oosterhoff on 18/07/2017.
//

#ifndef BRIDGEKEEPER_RECEIVER_H
#define BRIDGEKEEPER_RECEIVER_H

#include <Manchester.h>
#include "BridgeKeeper.h"
#include "State.h"

class Receiver {

private:
    Manchester *manchester;
    uint8_t buffer[sizeof(remote_msg_t) + 1];
    remote_msg_t current_message;

public:

    Receiver();

    void setup();

    void update();

};


#endif //BRIDGEKEEPER_RECEIVER_H
