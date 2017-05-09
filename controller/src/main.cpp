// // // /*
// // // #include <Arduino.h>
// // // #include "Manchester.h"
// // // 
// // // 
// // // Manchester manchester;
// // // 
// // // 
// // // uint8_t data[4] = {'t'};
// // // 
// // // int main(void) {
// // //     // Mandatory init
// // //     init();
// // // 
// // //     pinMode(13, OUTPUT);
// // // 
// // //     manchester.setupTransmit(5, MAN_300);
// // // 
// // //     uint16_t idx =0;
// // //     for (;;) {
// // //         digitalWrite(13, HIGH);
// // // 
// // //         manchester.transmit(idx);
// // // 
// // //         digitalWrite(13, LOW);
// // //         delay(2000);
// // //         idx=idx+1;
// // //     }
// // // }*/

#include <Arduino.h>
#include <Manchester.h>

/*
  Manchester Transmitter example
  
  In this example transmitter will send 10 bytes array  per transmittion
  try different speeds using this constants, your maximum possible speed will 
  depend on various factors like transmitter type, distance, microcontroller speed, ...
  MAN_300 0
  MAN_600 1
  MAN_1200 2
  MAN_2400 3
  MAN_4800 4
  MAN_9600 5
  MAN_19200 6
  MAN_38400 7
*/

Manchester man;

#define TX_PIN  5  //pin where your transmitter is connected
//#define LED_PIN 13 //pin for blinking LED

uint8_t moo = 1; //last led status
uint8_t data[4] = {4, 'S','&', 'C'};  // data [0] => length of send data; data[x>0] is data. S=> Start data;  C=> Close data.

void setup() 
{
  man.setupTransmit(TX_PIN, MAN_9600);
}

//uint8_t datalength=2;   //at least two data
void loop() 

{
  man.transmitArray(data[0], data);
  delay(2000);
}

int main() {
    init();

    setup();

    while (1) {
        loop();
    }
}
