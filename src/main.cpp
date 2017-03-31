
#include <Arduino.h>


int main(void) {
    // Mandatory init
    init();

    pinMode(13, OUTPUT);

    Serial.begin(9600);


    while (true) {
        digitalWrite(13, HIGH);
        Serial.println("whoop");

        delay(200);

        digitalWrite(13, LOW);

        delay(200);
    }
}

