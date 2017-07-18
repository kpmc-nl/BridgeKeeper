#include <Arduino.h>
#include "Controller.h"


int main() {
    init();

    Controller *controller = Controller::getInstance();

    controller->init();

    while (true) {
        controller->update();
    }

}