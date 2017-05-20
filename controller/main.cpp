#include <Arduino.h>
#include <BridgeKeeper.h>
#include "Manchester.h"

Manchester pole1_manchester;
Manchester remote_rx_manchester;

#define TX_PIN 5
#define RX_PIN 8

lightpole_msg_t pole1;
remote_msg_t remote_msg;
uint8_t rx_buf[sizeof(remote_msg_t) + 1];


void setup() {
    pinMode(13, OUTPUT);
    pinMode(TX_PIN, OUTPUT);

    remote_rx_manchester.setupReceive(RX_PIN, MAN_300);
    remote_rx_manchester.beginReceiveArray(sizeof(remote_msg_t) + 1, rx_buf);

    pole1_manchester.setupTransmit(TX_PIN, MAN_300);
}

void transmit() {
    uint8_t buf[sizeof(lightpole_msg_t) + 1];
    buf[0] = sizeof(lightpole_msg_t) + 1;

    memcpy(buf + 1, &pole1, sizeof(lightpole_msg_t));
    pole1_manchester.transmitArray(sizeof(lightpole_msg_t) + 1, buf);

    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
}

void loop() {
    if (remote_rx_manchester.receiveComplete()) {

        if (rx_buf[0] != sizeof(remote_msg_t) + 1) {
            /* ignore */
            return;
        }

        memcpy(&remote_msg, rx_buf + 1, sizeof(remote_msg_t));

        if (remote_msg.button1) {
            pole1.light1 = LOW;
            pole1.light2 = HIGH;
            pole1.light3 = HIGH;
            pole1.light4 = HIGH;
        } else if (remote_msg.button2) {
            pole1.light1 = LOW;
            pole1.light2 = LOW;
            pole1.light3 = HIGH;
            pole1.light4 = HIGH;
        } else if (remote_msg.button3) {
            pole1.light1 = LOW;
            pole1.light2 = LOW;
            pole1.light3 = LOW;
            pole1.light4 = HIGH;
        }

        transmit();

        remote_rx_manchester.beginReceiveArray(sizeof(remote_msg_t) + 1, rx_buf);
    }

}


int main() {
    init();
    setup();

    while (true) {
        loop();
    }
}
