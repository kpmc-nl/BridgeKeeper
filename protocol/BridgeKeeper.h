#ifndef BRIDGEKEEPER_H
#define BRIDGEKEEPER_H

#define HIGH 0x1
#define LOW  0x0

typedef struct {
    uint8_t light1 = LOW;
    uint8_t light2 = LOW;
    uint8_t light3 = LOW;
    uint8_t light4 = LOW;

} lightpole_msg_t;

typedef struct {
    uint8_t button1 = LOW;
    uint8_t button2 = LOW;
    uint8_t button3 = LOW;

} remote_msg_t;


#endif //BRIDGEKEEPER_H
