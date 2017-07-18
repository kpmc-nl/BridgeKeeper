#include <Arduino.h>
#include "Controller.h"


int main() {
    init();

    Controller *controller = Controller::getInstance();

    controller->setup();

    while (true) {
        controller->update();
    }

}