//
// Created by Matthijs Oosterhoff on 18/07/2017.
//

#include <BridgeKeeper.h>
#include "Receiver.h"
#include "Pinout.h"
#include "Controller.h"

unsigned long last_recv_time;

Receiver::Receiver() {
    manchester = new Manchester();
}

void Receiver::setup() {
    manchester->setupReceive(RF_DATA_PIN, MAN_300);
    manchester->beginReceiveArray(sizeof(remote_msg_t) + 1, buffer);
}

void Receiver::update() {

    if (manchester->receiveComplete()) {

        if (buffer[0] == sizeof(remote_msg_t) + 1) {
            /* only handle the message if the received size matches the protocol */

            memcpy(&current_message, buffer + 1, sizeof(remote_msg_t));


            if (current_message.button1) {
                Controller::setTargetState(Down);
            } else if (current_message.button2) {
                Controller::setTargetState(Up);
            } else if (current_message.button3 || current_message.button4) {
                Controller::setTargetState(Idle);
            }

            last_recv_time = millis();
        }
        manchester->beginReceiveArray(sizeof(remote_msg_t) + 1, buffer);
    }

//    if(last_recv_time + 500 < millis()){
//        Controller::setTargetState(Idle);
//    }

}

