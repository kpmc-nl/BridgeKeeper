/*
This code is based on the Atmel Corporation Manchester
Coding Basics Application Note.

http://www.atmel.com/dyn/resources/prod_documents/doc9164.pdf

Quotes from the application note:

"Manchester coding states that there will always be a transition of the message signal
at the mid-point of the data bit frame.
What occurs at the bit edges depends on the state of the previous bit frame and
does not always produce a transition. A logical '1' is defined as a mid-point transition
from low to high and a '0' is a mid-point transition from high to low.

We use Timing Based Manchester Decode.
In this approach we will capture the time between each transition coming from the demodulation
circuit."

Timer 2 is used with a ATMega328. Timer 1 is used for a ATtiny85.

This code gives a basic data rate as 1200 bauds. In manchester encoding we send 1 0 for a data bit 0.
We send 0 1 for a data bit 1. This ensures an average over time of a fixed DC level in the TX/RX.
This is required by the ASK RF link system to ensure its correct operation.
The data rate is then 600 bits/s.
*/

#include "Manchester.h"
#include <avr/interrupt.h>

static int8_t RxPin = 255;

static int16_t rx_sample = 0;
static int16_t rx_last_sample = 0;
static uint8_t rx_count = 0;
static uint8_t rx_sync_count = 0;
static uint8_t rx_mode = RX_MODE_IDLE;

static uint16_t rx_manBits = 0; //the received manchester 32 bits
static uint8_t rx_numMB = 0; //the number of received manchester bits
static uint8_t rx_curByte = 0;

static uint8_t rx_maxBytes = 2;
static uint8_t rx_default_data[2];
static uint8_t *rx_data = rx_default_data;

Manchester::Manchester() //constructor
{
}


void Manchester::setRxPin(uint8_t pin) {
    ::RxPin = pin; // user sets the digital pin as output
    DDRB &= ~_BV(pin);
}

void Manchester::setupReceive(uint8_t pin, uint8_t SF) {
    setRxPin(pin);
    ::MANRX_SetupReceive(SF);
}


//decode 8 bit payload and 4 bit ID from the message, return true if checksum is correct, otherwise false
uint8_t Manchester::decodeMessage(uint16_t m, uint8_t &id, uint8_t &data) {
    //extract components
    data = (m & 0xFF);
    id = (m >> 12);
    uint8_t ch = (m >> 8) & 0b1111; //checksum received
    //calculate checksum
    uint8_t ech = (id ^ data ^ (data >> 4) ^ 0b0011) & 0b1111; //checksum expected
    return ch == ech;
}

//encode 8 bit payload, 4 bit ID and 4 bit checksum into 16 bit
uint16_t Manchester::encodeMessage(uint8_t id, uint8_t data) {
    uint8_t chsum = (id ^ data ^ (data >> 4) ^ 0b0011) & 0b1111;
    uint16_t m = ((id) << 12) | (chsum << 8) | (data);
    return m;
}

void Manchester::beginReceiveArray(uint8_t maxBytes, uint8_t *data) {
    ::MANRX_BeginReceiveBytes(maxBytes, data);
}

void Manchester::beginReceive(void) {
    ::MANRX_BeginReceive();
}


uint8_t Manchester::receiveComplete(void) {
    return ::MANRX_ReceiveComplete();
}


uint16_t Manchester::getMessage(void) {
    return ::MANRX_GetMessage();
}


void Manchester::stopReceive(void) {
    ::MANRX_StopReceive();
}


void MANRX_SetupReceive(uint8_t speedFactor) {
    DDRB &= ~_BV(::RxPin); // INPUT

    //setup timers depending on the microcontroller used

    /*
    Timer 1 is used with a ATtiny85. 
    http://www.atmel.com/Images/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf page 88
    How to find the correct value: (OCRxA +1) = F_CPU / prescaler / 1953.125
    OCR1C is 8 bit register
    */

#if F_CPU == 1000000UL
    TCCR1 = _BV(CTC1) | _BV(CS12); // 1/8 prescaler
    OCR1C = (64 >> speedFactor) - 1;
#elif F_CPU == 8000000UL
    TCCR1 = _BV(CTC1) | _BV(CS12) | _BV(CS11) | _BV(CS10); // 1/64 prescaler
    OCR1C = (64 >> speedFactor) - 1;
#elif F_CPU == 16000000UL
    TCCR1 = _BV(CTC1) | _BV(CS12) | _BV(CS11) | _BV(CS10); // 1/64 prescaler
    OCR1C = (128 >> speedFactor) - 1;
#elif F_CPU == 16500000UL
    TCCR1 = _BV(CTC1) | _BV(CS12) | _BV(CS11) | _BV(CS10); // 1/64 prescaler
    OCR1C = (132 >> speedFactor) - 1;
#else
#error "Manchester library only supports 1mhz, 8mhz, 16mhz, 16.5Mhz clock speeds on ATtiny85 chip"
#endif

    OCR1A = 0; // Trigger interrupt when TCNT1 is reset to 0
    TIMSK |= _BV(OCIE1A); // Turn on interrupt
    TCNT1 = 0; // Set counter to 0


} //end of setupReceive

void MANRX_BeginReceive(void) {
    rx_maxBytes = 2;
    rx_data = rx_default_data;
    rx_mode = RX_MODE_PRE;
}

void MANRX_BeginReceiveBytes(uint8_t maxBytes, uint8_t *data) {
    rx_maxBytes = maxBytes;
    rx_data = data;
    rx_mode = RX_MODE_PRE;
}

void MANRX_StopReceive(void) {
    rx_mode = RX_MODE_IDLE;
}

uint8_t MANRX_ReceiveComplete(void) {
    return (rx_mode == RX_MODE_MSG);
}

uint16_t MANRX_GetMessage(void) {
    return (((int16_t) rx_data[0]) << 8) | (int16_t) rx_data[1];
}


void MANRX_SetRxPin(uint8_t pin) {
    RxPin = pin;
    DDRB &= ~_BV(pin); // INPUT
}//end of set transmit pin

void AddManBit(uint16_t *manBits, uint8_t *numMB,
               uint8_t *curByte, uint8_t *data,
               uint8_t bit) {
    *manBits <<= 1;
    *manBits |= bit;
    (*numMB)++;
    if (*numMB == 16) {
        uint8_t newData = 0;
        for (int8_t i = 0; i < 8; i++) {
            // ManBits holds 16 bits of manchester data
            // 1 = LO,HI
            // 0 = HI,LO
            // We can decode each bit by looking at the bottom bit of each pair.
            newData <<= 1;
            newData |= (*manBits & 1); // store the one
            *manBits = *manBits >> 2; //get next data bit
        }
        data[*curByte] = newData ^ DECOUPLING_MASK;
        (*curByte)++;

        // added by caoxp @ https://github.com/caoxp
        // compatible with unfixed-length data, with the data length defined by the first byte.
        // at a maximum of 255 total data length.
        if ((*curByte) == 1) {
            rx_maxBytes = data[0];
        }

        *numMB = 0;
    }
}


ISR(TIMER1_COMPA_vect) {
    if (rx_mode < RX_MODE_MSG) //receiving something
    {
        // Increment counter
        rx_count += 8;

        // Check for value change
        //rx_sample = digitalRead(RxPin);
        // caoxp@github,
        // add filter.
        // sample twice, only the same means a change.
        static uint8_t rx_sample_0 = 0;
        static uint8_t rx_sample_1 = 0;
        rx_sample_0 = PINB & _BV(RxPin); // digitalRead(RxPin)
        if (rx_sample_1 == rx_sample_0) {
            rx_sample = rx_sample_1;
        }
        rx_sample_0 = rx_sample_1;


        //check sample transition
        uint8_t transition = (rx_sample != rx_last_sample);

        if (rx_mode == RX_MODE_PRE) {
            // Wait for first transition to HIGH
            if (transition && (rx_sample == 1)) {
                rx_count = 0;
                rx_sync_count = 0;
                rx_mode = RX_MODE_SYNC;
            }
        } else if (rx_mode == RX_MODE_SYNC) {
            // Initial sync block
            if (transition) {
                if (((rx_sync_count < (SYNC_PULSE_MIN * 2)) || (rx_last_sample == 1)) &&
                    ((rx_count < MinCount) || (rx_count > MaxCount))) {
                    // First 20 bits and all 1 bits are expected to be regular
                    // Transition was too slow/fast
                    rx_mode = RX_MODE_PRE;
                } else if ((rx_last_sample == 0) &&
                           ((rx_count < MinCount) || (rx_count > MaxLongCount))) {
                    // 0 bits after the 20th bit are allowed to be a double bit
                    // Transition was too slow/fast
                    rx_mode = RX_MODE_PRE;
                } else {
                    rx_sync_count++;

                    if ((rx_last_sample == 0) &&
                        (rx_sync_count >= (SYNC_PULSE_MIN * 2)) &&
                        (rx_count >= MinLongCount)) {
                        // We have seen at least 10 regular transitions
                        // Lock sequence ends with unencoded bits 01
                        // This is encoded and TX as HI,LO,LO,HI
                        // We have seen a long low - we are now locked!
                        rx_mode = RX_MODE_DATA;
                        rx_manBits = 0;
                        rx_numMB = 0;
                        rx_curByte = 0;
                    } else if (rx_sync_count >= (SYNC_PULSE_MAX * 2)) {
                        rx_mode = RX_MODE_PRE;
                    }
                    rx_count = 0;
                }
            }
        } else if (rx_mode == RX_MODE_DATA) {
            // Receive data
            if (transition) {
                if ((rx_count < MinCount) ||
                    (rx_count > MaxLongCount)) {
                    // wrong signal lenght, discard the message
                    rx_mode = RX_MODE_PRE;
                } else {
                    if (rx_count >= MinLongCount) // was the previous bit a double bit?
                    {
                        AddManBit(&rx_manBits, &rx_numMB, &rx_curByte, rx_data, rx_last_sample);
                    }
                    if ((rx_sample == 1) &&
                        (rx_curByte >= rx_maxBytes)) {
                        rx_mode = RX_MODE_MSG;
                    } else {
                        // Add the current bit
                        AddManBit(&rx_manBits, &rx_numMB, &rx_curByte, rx_data, rx_sample);
                        rx_count = 0;
                    }
                }
            }
        }

        // Get ready for next loop
        rx_last_sample = rx_sample;
    }
}

