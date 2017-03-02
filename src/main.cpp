
#include <Arduino.h>


int main(void) {
    // Mandatory init
    init();

    pinMode(13, OUTPUT);


    while (true) {
        digitalWrite(13, HIGH);

        delay(200);

        digitalWrite(13, LOW);

        delay(200);
    }
}

