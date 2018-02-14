#include <Arduino.h>
#include <BridgeKeeper.h>
#include "Manchester.h"
#include <core_pins.h>

Manchester pole1_manchester;

#define TX_PIN PIN_A5

#define BTN1_PIN PIN_A1
#define BTN2_PIN PIN_A2
#define BTN3_PIN PIN_A3

remote_msg_t msg;
uint8_t tx_buf[sizeof(remote_msg_t) + 1];

void setup() {
    tx_buf[0] = sizeof(remote_msg_t) + 1;


    pinMode(PIN_A7, OUTPUT);
    pinMode(BTN1_PIN, INPUT);
    pinMode(BTN2_PIN, INPUT);
    pinMode(BTN3_PIN, INPUT);

    pinMode(TX_PIN, OUTPUT);


    pole1_manchester.setupTransmit(TX_PIN, MAN_300);
}

void transmit() {
    digitalWrite(PIN_A7, HIGH);
    memcpy(tx_buf + 1, &msg, sizeof(remote_msg_t));
    pole1_manchester.transmitArray(sizeof(remote_msg_t) + 1, tx_buf);
    digitalWrite(PIN_A7, LOW);
}


void readBtn(uint8_t pin, uint8_t *target) {
    if (digitalRead(pin)) {
        while (digitalRead(pin)) {
            *target = HIGH;
            transmit();
            delay(40);
        }
    }
    *target = LOW;
}

int main() {
    init();

    setup();

    while (true) {
        readBtn(BTN1_PIN, &msg.button1);
        readBtn(BTN2_PIN, &msg.button2);
        readBtn(BTN3_PIN, &msg.button3);
    }
}
