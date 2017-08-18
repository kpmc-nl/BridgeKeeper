#include <Arduino.h>
#include "Controller.h"


int main() {
    init();

    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);

    Controller *controller = Controller::getInstance();

    controller->setup();

    while (true) {
        controller->update();
    }

}