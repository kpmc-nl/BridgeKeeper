#include <Arduino.h>
#include <BridgeKeeper.h>
#include "Manchester.h"

Manchester man;

#define TX_PIN 5

lightpole_msg_t pole1;

void setup() {
    pinMode(13, OUTPUT);
    pinMode(TX_PIN, OUTPUT);

    for (int i = 0; i < sizeof(lightpole_msg_t); i++) {
        digitalWrite(13, HIGH);
        delay(200);
        digitalWrite(13, LOW);
        delay(200);
    }

    man.setupTransmit(TX_PIN, MAN_300);
}

void transmit() {
    uint8_t buf[sizeof(lightpole_msg_t) + 1];
    buf[0] = sizeof(lightpole_msg_t) + 1;

    memcpy(buf + 1, &pole1, sizeof(lightpole_msg_t));
    man.transmitArray(sizeof(lightpole_msg_t) + 1, buf);

    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
}


int main() {
    init();
    setup();


    while (1) {

        pole1.light1 = HIGH;
        transmit();
        delay(1000);
        pole1.light2 = HIGH;
        transmit();
        delay(1000);
        pole1.light3 = HIGH;
        transmit();
        delay(1000);
        pole1.light4 = HIGH;
        transmit();
        delay(1000);

        pole1.light1 = LOW;
        pole1.light2 = LOW;
        pole1.light3 = LOW;
        pole1.light4 = LOW;
        transmit();
        delay(1000);


    }
}
