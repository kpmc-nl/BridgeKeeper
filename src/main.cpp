
#include <Arduino.h>


int main(void) {
    // Mandatory init
    init();

    pinMode(13, OUTPUT);


    while (true) {
        digitalWrite(13, HIGH);

        delay(1000);

        digitalWrite(13, LOW);

        delay(1000);
    }
}


#endif