//
// Created by matthijs on 8/18/17.
//

#include "Button.h"


Button::Button(uint8_t pin, void (*onPress)(void), void (*onLongPress)(void)) {
    this->pin = pin;
    this->onPress = onPress;
    this->onLongPress = onLongPress;
    this->last_low = 0;
}

void Button::setup() {
    pinMode(pin, INPUT);
}

void Button::update() {

    if(0 == last_low && LOW == digitalRead(pin)){
        last_low = millis();
    } else if (0 != last_low && HIGH == digitalRead(pin)){

        if(LONG_PRESS_TIME_MS < millis() - last_low){
            // it was a long press
            onLongPress();
        }else{
            // it was a short press
            onPress();
        }
        last_low = 0;
    }




}

