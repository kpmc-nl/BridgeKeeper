
#include "Manchester.h"


Manchester man;

#define RX_PIN 5

uint8_t buffer[2]={0,0};

void setup() {

    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);

    pinMode(RX_PIN, INPUT);
    Serial.begin(9600);
    Serial.println("Initialized");


    man.setupReceive(RX_PIN, MAN_1200);
    man.beginReceiveArray(4, buffer);
}

void loop() {
    if (man.receiveComplete()) {


        Serial.print("got data: ");

        Serial.print(buffer[0]);
        Serial.print(" - ");
        Serial.print(buffer[1]);
        Serial.println();

        PORTB = buffer[1];

        man.beginReceiveArray(2, buffer);
    }
}

int main() {
    init();

    setup();

    while (1) {
        loop();
    }
}

