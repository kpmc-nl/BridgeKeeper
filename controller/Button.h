//
// Created by matthijs on 8/18/17.
//

#ifndef BRIDGEKEEPER_BUTTON_H
#define BRIDGEKEEPER_BUTTON_H

#include <Arduino.h>

#define LONG_PRESS_TIME_MS  1000

class Button {

private:
    uint8_t pin;
    unsigned long last_low;
    void (*onPress)(void);
    void (*onLongPress)(void);

public:

    Button(uint8_t pin, void (*onPress)(void),void (*onLongPress)(void));

    void setup();

    void update();


};


#endif //BRIDGEKEEPER_BUTTON_H
