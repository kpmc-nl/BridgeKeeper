#include "UI.h"
#include "Controller.h"


UI::UI() {
    lcd = new LiquidCrystal_I2C(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
}

void UI::init() {
    lcd->begin(16, 2);
}

void UI::update() {

    if (last_display + DISPLAY_REFRESH_MS < millis()) {

        Controller *controller = Controller::getInstance();

        lcd->clear();

        lcd->setCursor(0, 0);
        lcd->print("c:");
        lcd->print(controller->getAngleSensor()->getAngle());

        last_display = millis();
    }
}

