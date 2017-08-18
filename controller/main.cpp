#include <Arduino.h>
#include "Controller.h"


int main() {
    init();




    Controller::setup();

    while (true) {
        Controller::update();
    }

}