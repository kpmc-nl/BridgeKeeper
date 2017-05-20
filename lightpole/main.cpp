#include <Arduino.h>
#include <BridgeKeeper.h>
#include "Manchester.h"

Manchester pole1_manchester;
lightpole_msg_t pole;

uint8_t buffer[sizeof(lightpole_msg_t) + 1];

void setup() {

    pinMode(PB0, OUTPUT);
    pinMode(PB1, OUTPUT);
    pinMode(PB2, OUTPUT);
    pinMode(PB3, OUTPUT);

    pinMode(PB4, INPUT);

    pole1_manchester.setupReceive(PB4, MAN_300);
    pole1_manchester.beginReceiveArray(sizeof(lightpole_msg_t) + 1, buffer);
}

void loop() {

    if (pole1_manchester.receiveComplete()) {

        if (buffer[0] != sizeof(lightpole_msg_t) + 1) {
            /* ignore */
            return;
        }

        memcpy(&pole, buffer + 1, sizeof(lightpole_msg_t));


        digitalWrite(PB0, pole.light1);
        digitalWrite(PB1, pole.light2);
        digitalWrite(PB2, pole.light3);
        digitalWrite(PB3, pole.light4);

        pole1_manchester.beginReceiveArray(sizeof(lightpole_msg_t) + 1, buffer);
    }

}


int main(void) {

    init();

    setup();

    while (true) {
        loop();
    }

}

