#ifndef BRIDGEKEEPER_UI_H
#define BRIDGEKEEPER_UI_H

#define DISPLAY_REFRESH_MS 100

#include <LiquidCrystal_I2C.h>

class UI {

private:
    LiquidCrystal_I2C *lcd;
    unsigned long last_display;

public:

    UI();

    void setup();

    void update();

};


#endif //BRIDGEKEEPER_UI_H
