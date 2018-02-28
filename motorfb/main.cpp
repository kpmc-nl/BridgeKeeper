#include <Arduino.h>
#include "pinout.h"

#define SAMPLE_SIZE 11

static int samples[SAMPLE_SIZE];
int count = 0;

void handle_falling();
int median(int *input, int array_size);

void setup() {
    analogReference(INTERNAL2V56_NO_CAP);

    pinMode(MOTOR_ENABLE_PIN, INPUT);
    pinMode(SIGNAL_OUT_PIN, OUTPUT);
    pinMode(SIGNAL_IN_PIN, INPUT);
    attachInterrupt(MOTOR_ENABLE_INT, handle_falling, FALLING);
}

void loop() {

    int m = median(samples, SAMPLE_SIZE);

    if(m > 1.39/2.56*1024){
        digitalWrite(SIGNAL_OUT_PIN, LOW);
    }else{
        digitalWrite(SIGNAL_OUT_PIN, HIGH);
    }
}

void handle_falling(){


    if (count == SAMPLE_SIZE) {
        count = 0;
    }
    samples[count] = analogRead(SIGNAL_IN_PIN);
    ++count;

}

int median(int *input, int array_size) {

    int sorted[array_size];
    for (int i = 0; i < array_size; ++i) {
        sorted[i] = input[i];
    }
    for (int i = array_size - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (sorted[j] > sorted[j + 1]) {
                int tmp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = tmp;
            }
        }
    }

    // Middle or average of middle values in the sorted input.
    int res = 0;
    if ((array_size % 2) == 0) {
        res = ((sorted[array_size / 2] / 2) + (sorted[(array_size / 2) - 1]) / 2);
    } else {
        res = sorted[array_size / 2];
    }
    return res;

}


int main(void) {

    init();

    setup();

    while (true) {
        loop();
    }

}

