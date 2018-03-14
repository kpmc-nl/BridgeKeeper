//
// Created by matthijs on 14-3-18.
//
#include <Arduino.h>
#include "Pinout.h"
#include "BatterySensor.h"

BatterySensor::BatterySensor() {
    this->voltage = 0;
    this->last_update = 0;
}

void BatterySensor::setup() {
    pinMode(BATTERY_SENSOR, INPUT);
}

void BatterySensor::update() {
    cli();
    unsigned long time = millis();
    if(last_update + 2000 < time){
        long val = analogRead(BATTERY_SENSOR);
        this->voltage = map(val, 0, 1023, 0, 15800);
        last_update = time;
    }
    sei();
}

long BatterySensor::getVoltage() {
    return this->voltage;
}