#include "UI.h"
#include "Controller.h"


UI::UI() {
    lcd = new LiquidCrystal_I2C(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
}

void UI::setup() {
    lcd->begin(16, 2);

    lcd->setCursor(0, 0);
    lcd->print("==BridgeKeeper==");

    delay(1000);
    lcd->clear();
}

void UI::update() {

//    if (last_display + DISPLAY_REFRESH_MS < millis()) {


    lcd->clear();

    lcd->setCursor(0, 0);
    lcd->print("c:");
    lcd->print(Controller::getAngleSensor()->getAngle(), 1);

    lcd->setCursor(7, 0);
    lcd->print(" t:");

    switch (Controller::getTargetState()) {

        case Up_L:
            lcd->print("UL");
            break;
        case Up_R:
            lcd->print("UR");
            break;
        case Down:
            lcd->print("DO");
            break;
        case Manual:
            lcd->print("MA");
    }

    lcd->setCursor(0, 1);
    lcd->print("s:");

    switch (Controller::getCurrentState()) {

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
        case Manual:
            lcd->print("MA");
    }

    lcd->setCursor(9, 1);
    switch(Controller::getTargetState()){
        case Manual:
            lcd->print(Controller::getManualTargetAngle(), 1);
            break;
        case Up_L:
        case Up_R:
        case Rising:
            lcd->print(Controller::getUpTargetAngle(), 1);
            break;
        case Falling:
        case Down:
            lcd->print(Controller::getDownTargetAngle(), 1);
            break;
    }

//        last_display = millis();
//    }
}

