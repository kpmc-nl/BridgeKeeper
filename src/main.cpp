
#include <Arduino.h>
#include "Manchester.h"


Manchester manchester;


uint8_t data[4] = {1,3,3,7};

int main(void) {
    // Mandatory init
    init();

    pinMode(13, OUTPUT);

    Serial.begin(9600);

    manchester.setupTransmit(5, MAN_300);

    for (;;) {
        digitalWrite(13, HIGH);
        manchester.transmitArray(4, data);
        digitalWrite(13, LOW);
        delay(2000);
    }
}