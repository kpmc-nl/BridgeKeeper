#include <Arduino.h>
#include "pinout.h"

unsigned long time;

void handle_interrupt();

void setup() {
    analogReference(INTERNAL2V56_NO_CAP);

    pinMode(MOTOR_ENABLE_PIN, INPUT);
    pinMode(SIGNAL_OUT_PIN, OUTPUT);
    pinMode(SIGNAL_IN_PIN, INPUT);
    attachInterrupt(MOTOR_ENABLE_INT, handle_interrupt, FALLING);
}

void loop() {
    if(time + 1000 < millis()){
        digitalWrite(SIGNAL_OUT_PIN, HIGH);
    }
}

void handle_interrupt(){

    if(analogRead(SIGNAL_IN_PIN) > 560){
        time = millis();
        digitalWrite(SIGNAL_OUT_PIN, LOW);
    }else{
        digitalWrite(SIGNAL_OUT_PIN, HIGH);
    }
}


int main(void) {

    init();

    setup();

    while (true) {
        loop();
    }

}

