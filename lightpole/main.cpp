/**
 * Firmware for an RC speed controller with a circuit based on some FETs and two relays
 */

#include <Arduino.h>
#include "Manchester.h"

Manchester man;

uint8_t buffer[2] = {0, 0};

#define RX_PIN PB2

void setup(){

    pinMode(PB0, OUTPUT);
    pinMode(PB1, OUTPUT);
    pinMode(PB3, OUTPUT);
    pinMode(PB4, OUTPUT);

    pinMode(PB2, INPUT);

    man.setupReceive(RX_PIN, MAN_300);
    man.beginReceiveArray(2, buffer);
}

void loop(){

    if (man.receiveComplete()) {

        digitalWrite(PB0, buffer[1] & _BV(0));
        digitalWrite(PB1, buffer[1] & _BV(1));
        digitalWrite(PB3, buffer[1] & _BV(2));
        digitalWrite(PB4, buffer[1] & _BV(3));

        man.beginReceiveArray(2, buffer);
    }

}


int main(void) {

    init();

    setup();

    while(true){
        loop();
    }

}

