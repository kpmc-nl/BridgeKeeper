#include <Arduino.h>
#include "Controller.h"


int main() {
    init();

    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);

    Controller *controller = Controller::getInstance();

    controller->setup();

//    for(int i=0; i<10; i++){
//        digitalWrite(12, HIGH);
//        delay(150);
//        digitalWrite(12, LOW);
//        delay(150);
//    }

//    controller->update();
//    delay(1000);

    while (true) {
        controller->update();
    }

}