
#include "Manchester.h"


Manchester man;

#define RX_PIN 5

uint8_t buffer[4];

void setup() {
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);

    buffer[0] = 255;

    man.setupReceive(RX_PIN, MAN_9600);
    man.beginReceiveArray(4, buffer);
}

void loop() {
    if (man.receiveComplete()) {
        digitalWrite(8, (buffer[0] >> 0) & 1);
        digitalWrite(9, (buffer[0] >> 1) & 1);
        digitalWrite(10, (buffer[0] >> 2) & 1);
        digitalWrite(11, (buffer[0] >> 3) & 1);

        digitalWrite(13, HIGH);
        delay(20);
        digitalWrite(13, LOW);

        man.beginReceiveArray(4, buffer);
    }
}

int main() {
    init();

    setup();

    while (1) {
        loop();
    }
}

