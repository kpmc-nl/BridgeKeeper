#include <Arduino.h>

unsigned long time;

void handle_interrupt();

void setup() {
    analogReference(INTERNAL2V56_NO_CAP);

    pinMode(PB0, OUTPUT);
    pinMode(PB2, INPUT);
    pinMode(PB4, OUTPUT);
    pinMode(A3, INPUT);
    attachInterrupt(0, handle_interrupt, FALLING);
}

void loop() {
    if(time + 1000 < millis()){
        digitalWrite(PB4, HIGH);
    }
}

void handle_interrupt(){

    if(analogRead(A3) > 560){
        time = millis();
        digitalWrite(PB4, LOW);
    }else{
        digitalWrite(PB4, HIGH);
    }
}


int main(void) {

    init();

    setup();

    while (true) {
        loop();
    }

}

