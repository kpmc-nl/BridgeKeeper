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
uint8_t testblock[sizeof(remote_msg_t)];

void setup() {
    memset(testblock, 0, sizeof(testblock));
    tx_buf[0] = sizeof(remote_msg_t) + 1;


    pinMode(PIN_B2, OUTPUT);
    pinMode(BTN1_PIN, INPUT_PULLUP);
    pinMode(BTN2_PIN, INPUT_PULLUP);
    pinMode(BTN3_PIN, INPUT_PULLUP);

    pinMode(TX_PIN, OUTPUT);


    pole1_manchester.setupTransmit(TX_PIN, MAN_300);
}

void transmit() {

    memcpy(tx_buf + 1, &msg, sizeof(remote_msg_t));
    pole1_manchester.transmitArray(sizeof(remote_msg_t) + 1, tx_buf);

    digitalWrite(PIN_B2, HIGH);
    delay(100);
    digitalWrite(PIN_B2, LOW);
}


void readBtn(uint8_t pin, uint8_t *target) {
    if (!digitalRead(pin)) {
        while (!digitalRead(pin)) {
            /* somewhat crude busy wait debounce ;) */
        }
        *target = HIGH;
    } else {
        *target = LOW;
    }
}

boolean shouldSend() {
    return 0 != memcmp(testblock, &msg, sizeof(remote_msg_t));
}


int main() {
    init();

    setup();

    while (1) {

        readBtn(BTN1_PIN, &msg.button1);
        readBtn(BTN2_PIN, &msg.button2);
        readBtn(BTN3_PIN, &msg.button3);


        if (shouldSend()) {
            transmit();
        }
    }
}
