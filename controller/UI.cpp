#include "UI.h"
#include "Controller.h"


UI::UI() {
    lcd = new LiquidCrystal_I2C(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
}

void UI::setup() {
    lcd->begin(16, 2);

    lcd->setCursor(0,0);
    lcd->print("==BridgeKeeper==");

    delay(1000);
    lcd->clear();
}

void UI::update() {

    if (last_display + DISPLAY_REFRESH_MS < millis()) {

        Controller *controller = Controller::getInstance();

        lcd->clear();

        lcd->setCursor(0, 0);
        lcd->print("c:");
        lcd->print(controller->getAngleSensor()->getAngle(), 1);

        lcd->setCursor(7,0);
        lcd->print(" t:");

        switch (controller->getTargetState()) {

            case Up_L:
                lcd->print("UL");
                break;
            case Up_R:
                lcd->print("UR");
                break;
            case Down:
                lcd->print("DO");
                break;
        }

        lcd->setCursor(0, 1);
        lcd->print("s:");

        switch (controller->getCurrentState()) {

            case Up_L:
                lcd->print("UL");
                break;
            case Up_R:
                lcd->print("UR");
                break;
            case Down:
                lcd->print("DO");
                break;
            case Rising:
                lcd->print("RI");
                break;
            case Falling:
                lcd->print("FA");
                break;
        }

        last_display = millis();
    }
}

