
#include <Arduino.h>
#include "Manchester.h"


Manchester manchester;


uint8_t data[4] = {'t','e','s','t'};

int main(void) {
    // Mandatory init
    init();

    pinMode(13, OUTPUT);

    manchester.setupTransmit(5, MAN_300);

    uint16_t idx =0;
    for (;;) {
        digitalWrite(13, HIGH);

        manchester.transmit(idx);

        digitalWrite(13, LOW);
        delay(2000);
        idx=idx+1;
    }
}