/**
 * Firmware for an RC speed controller with a circuit based on some FETs and two relays
 */

#include <avr/io.h>
#include "Manchester.h"
//#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/interrupt.h>

Manchester man;

#define RX_PIN PB2

uint8_t buffer[2] = {0, 0};


int main(void) {
    /* run at 8MHz */
    CLKPR = 0x80; // set system clock to 8mhz with no prescale
    CLKPR = 0x00; // these 2 CLKPR instructions have to be run together in order to set clock to 8 Mhz

    cli();


    // reset Timer 0
//    TCCR0A = 0;
//    TCCR0B = 0;

    DDRB |= _BV(PB0);
    DDRB |= _BV(PB1);
    DDRB |= _BV(PB4);
    DDRB |= _BV(PB3);
//
    DDRB &= ~_BV(RX_PIN);

    PORTB |= _BV(PB0);
    PORTB &= ~_BV(PB1);
    PORTB |= _BV(PB4);
    PORTB &= ~_BV(PB3);
    _delay_ms(500);
    PORTB &= ~_BV(PB0);
    PORTB |= _BV(PB1);
    PORTB &= ~_BV(PB4);
    PORTB |= _BV(PB3);
    _delay_ms(500);
    PORTB &= ~_BV(PB0);
    PORTB &= ~_BV(PB1);
    PORTB &= ~_BV(PB4);
    PORTB &= ~_BV(PB3);


//    GIMSK = 0;
//    GIMSK |= _BV(PCIE); // turn on pin change interrupts

//    PCMSK = 0;
//    PCMSK |= _BV(PCINT2);  // turn on interrupts on pins PB0, PB1, &amp;amp; PB4


    man.setupReceive(RX_PIN, MAN_1200);

    sei();

    man.beginReceiveArray(2, buffer);


    while (1) {

        if (man.receiveComplete()) {

            if (buffer[1] & _BV(0)) {
                PORTB |= _BV(PB0);
            } else {
                PORTB &= ~_BV(PB0);
            }
            if (buffer[1] & _BV(1)) {
                PORTB |= _BV(PB1);
            } else {
                PORTB &= ~_BV(PB1);
            }
            if (buffer[1] & _BV(2)) {
                PORTB |= _BV(PB4);
            } else {
                PORTB &= ~_BV(PB4);
            }
            if (buffer[1] & _BV(3)) {
                PORTB |= _BV(PB3);
            } else {
                PORTB &= ~_BV(PB3);
            }


            man.beginReceiveArray(2, buffer);
        }

    }
}

