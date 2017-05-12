

#include <Arduino.h>
#include "Manchester.h"

Manchester man;
Manchester man2;

#define TX_PIN 5
#define TX2_PIN 6

uint8_t buffer[2]= {2,0};
uint8_t buffer2[2]= {2,0};

int main() {
    init();

    pinMode(13, OUTPUT);

    pinMode(TX_PIN, OUTPUT);
    pinMode(TX2_PIN, OUTPUT);
    man.setupTransmit(TX_PIN, MAN_300);
    man2.setupTransmit(TX2_PIN, MAN_300);

    while (1) {

        man.transmitArray(2, buffer);
        man2.transmitArray(2, buffer2);

        digitalWrite(13, HIGH);
        delay(100);
        digitalWrite(13, LOW);
        delay(1000);


        if(buffer[1] >= 15){
            buffer[1] = 0;
        }else{
            buffer[1]++;
        }
        buffer2[1] = 15 - buffer[1];

    }
}
