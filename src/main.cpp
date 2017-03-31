#include <Arduino.h>
#include "Manchester.h"


#define RX_PIN 5
#define LED_PIN 13

Manchester man;

#define BUFFER_SIZE 4
uint8_t buffer[BUFFER_SIZE];

void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(19200);
    man.setupReceive(RX_PIN, MAN_300);
    Serial.println("initialized");

    man.beginReceive();

//    man.beginReceiveArray(BUFFER_SIZE, buffer);
}

void loop() {


    if (man.receiveComplete()) {

        Serial.println(man.getMessage());
        man.beginReceive();
    }


//    Serial.print(man.receiveComplete());


//    if (man.receiveComplete()) {
//        for (uint8_t i = 0; i < BUFFER_SIZE; i++) {
//            Serial.write(buffer[i]);
//        }
//
//        Serial.println();
//
//        man.beginReceiveArray(BUFFER_SIZE, buffer);
//    }
}


int main() {
    init();

    setup();

    while (1) {
        loop();
    }
}

