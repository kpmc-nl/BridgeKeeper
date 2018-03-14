//
// Created by matthijs on 14-3-18.
//

#ifndef BRIDGEKEEPER_BATTERYSENSOR_H
#define BRIDGEKEEPER_BATTERYSENSOR_H

class BatterySensor {

private:
    unsigned long last_update;
    long voltage;

public:
    BatterySensor();

    void setup();

    void update();

    long getVoltage();


};


#endif //BRIDGEKEEPER_BATTERYSENSOR_H
