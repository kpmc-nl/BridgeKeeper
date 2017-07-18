#ifndef BRIDGEKEEPER_CONTROLLER_H
#define BRIDGEKEEPER_CONTROLLER_H


#include "UI.h"
#include "AngleSensor.h"

class Controller {

private:
    UI ui;
    AngleSensor angleSensor;

public:

    Controller();

    static Controller *getInstance();

    void init();

    void update();

    UI *getUi();

    AngleSensor *getAngleSensor();


};


#endif //BRIDGEKEEPER_CONTROLLER_H
