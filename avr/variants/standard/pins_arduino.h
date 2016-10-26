#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>
/*

                  8151core STANDARD PINOUT
                   ATmega8515, ATmega162
   	 
                         +---\/---+
    PWM /LED (D 0) PB0  1|        |40  GND
        PWM* (D 1) PB1  2|        |39  PA0 (D 24) PCINT0
        RX1* (D 2) PB2  3|        |38  PA1 (D 25) PCINT1
        TX1* (D 3) PB3  4|        |37  PA2 (D 26) PCINT2
    PWM* /SS (D 4) PB4  5|        |36  PA3 (D 27) PCINT3
        MOSI (D 5) PB5  6|        |35  PA4 (D 28) PCINT4
        MISO (D 6) PB6  7|        |34  PA5 (D 39) PCINT5
         SCK (D 7) PB7  8|        |33  PA6 (D 30) PCINT6
                   RST  9|        |32  PA7 (D 31) PCINT7
         RX0 (D 8) PD0 10|        |31  PE0 (D 32) INT2
         TX0 (D 9) PD1 11|        |30  PE1 (D 33)
       INT0 (D 10) PD2 12|        |29  PE2 (D 34) PWM
       INT1 (D 11) PD3 13|        |28  PC7 (D 23) PCINT15* TDI*
       PWM* (D 12) PD4 14|        |27  PC6 (D 22) PCINT14* TDO*
        PWM (D 13) PD5 15|        |26  PC5 (D 21) PCINT13* TMS*
            (D 14) PD6 16|        |25  PC4 (D 20) PCINT12* TCK*
            (D 15) PD7 17|        |24  PC3 (D 19) PCINT11*
                 XTAL1 18|        |23  PC2 (D 18) PCINT10*
                 XTAL2 19|        |22  PC1 (D 17) PCINT9*
                   GND 20|        |21  PC0 (D 16) PCINT8*
                         +--------+
                     * ATmega162 only
   

*/

#define STANDARD_PINOUT
#define NUM_DIGITAL_PINS            35
#define NUM_ANALOG_INPUTS           0
#define analogInputToDigitalPin(p)  (-1)
#define analogPinToChannel(p)       (-1)
#define digitalPinToInterrupt(p)    ((p) == 10 ? 0 : ((p) == 11 ? 1 : ((p) == 32 ? 2 : NOT_AN_INTERRUPT)))

#if defined(__AVR_ATmega8515__)
#define digitalPinHasPWM(p)         ((p) == 0 || (p) == 13 || (p) == 34)

#elif defined(__AVR_ATmega162__)
#define digitalPinHasPWM(p)         ((p) == 0 || (p) == 1 || (p) == 4 || (p) == 12 || (p) == 13 || (p) == 34)
#endif


static const uint8_t LED = 0;
#define LED_BUILTIN 0

static const uint8_t SS   = 4;
static const uint8_t MOSI = 5;
static const uint8_t MISO = 6;
static const uint8_t SCK  = 7;


#if defined(__AVR_ATmega162__)
#define digitalPinToPCICR(p)    (0)
#define digitalPinToPCICRbit(p) (0)
#define digitalPinToPCMSK(p)    (((p) >= 24 && (p) <= 31) ? &PCMSK0 : ((p) >= 16 && (p) <= 32) ? &PCMSK1 : 0)
#define digitalPinToPCMSKbit(p) ((p) % 8)
#endif




#ifdef ARDUINO_MAIN

#define PA 1
#define PB 2
#define PC 3
#define PD 4
#undef PE
#define PE 5

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &DDRA,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
	(uint16_t) &DDRE,
};

const uint16_t PROGMEM port_to_output_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
	(uint16_t) &PORTE,
};

const uint16_t PROGMEM port_to_input_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &PINA,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
	(uint16_t) &PINE,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] =
{
	PB, /* D0 */
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PD, /* D8 */
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PC, /* D16 */
	PC,
	PC,
	PC,
	PC,
	PC,
	PC,
	PC,
	PA, /* D24 */
	PA,
	PA,
	PA,
	PA,
	PA,
	PA,
	PA, /* D31 */
	PE,
	PE,
	PE  /* D34 */
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] =
{
	_BV(0), /* D0, port B */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* D8, port D */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* D16, port C */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* D24, port A */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* D32, port E */
	_BV(1),
	_BV(2)
};


#if defined(__AVR_ATmega8515__)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
	TIMER0, 	      /* D0  - PB0 */
	NOT_ON_TIMER, 	/* D1  - PB1 */
	NOT_ON_TIMER, 	/* D2  - PB2 */
	NOT_ON_TIMER,   /* D3  - PB3 */
	NOT_ON_TIMER, 	/* D4  - PB4 */
	NOT_ON_TIMER, 	/* D5  - PB5 */
	NOT_ON_TIMER, 	/* D6  - PB6 */
	NOT_ON_TIMER,	  /* D7  - PB7 */
	NOT_ON_TIMER, 	/* D8  - PD0 */
	NOT_ON_TIMER, 	/* D9  - PD1 */
	NOT_ON_TIMER, 	/* D10 - PD2 */
	NOT_ON_TIMER, 	/* D11 - PD3 */
	NOT_ON_TIMER,  	/* D12 - PD4 */
	TIMER1A,     	  /* D13 - PD5 */
	NOT_ON_TIMER,   /* D14 - PD6 */
	NOT_ON_TIMER,   /* D15 - PD7 */
	NOT_ON_TIMER, 	/* D16 - PC0 */
	NOT_ON_TIMER,   /* D17 - PC1 */
	NOT_ON_TIMER,   /* D18 - PC2 */
	NOT_ON_TIMER,   /* D19 - PC3 */
	NOT_ON_TIMER,   /* D20 - PC4 */
	NOT_ON_TIMER,   /* D21 - PC5 */
	NOT_ON_TIMER,   /* D22 - PC6 */
	NOT_ON_TIMER,   /* D23 - PC7 */
	NOT_ON_TIMER,   /* D24 - PA0 */
	NOT_ON_TIMER,   /* D25 - PA1 */
	NOT_ON_TIMER,   /* D26 - PA2 */
	NOT_ON_TIMER,   /* D27 - PA3 */
	NOT_ON_TIMER,   /* D28 - PA4 */
	NOT_ON_TIMER,   /* D29 - PA5 */
	NOT_ON_TIMER,   /* D30 - PA6 */
	NOT_ON_TIMER,   /* D31 - PA7 */
	NOT_ON_TIMER,   /* D32 - PE0 */
	NOT_ON_TIMER,   /* D33 - PE1 */
	TIMER1B         /* D34 - PE2 */
};


#elif defined(__AVR_ATmega162__)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
	TIMER0, 	      /* D0  - PB0 */
	TIMER2, 	      /* D1  - PB1 */
	NOT_ON_TIMER, 	/* D2  - PB2 */
	NOT_ON_TIMER,   /* D3  - PB3 */
	TIMER3B,      	/* D4  - PB4 */
	NOT_ON_TIMER, 	/* D5  - PB5 */
	NOT_ON_TIMER, 	/* D6  - PB6 */
	NOT_ON_TIMER,	  /* D7  - PB7 */
	NOT_ON_TIMER, 	/* D8  - PD0 */
	NOT_ON_TIMER, 	/* D9  - PD1 */
	NOT_ON_TIMER, 	/* D10 - PD2 */
	NOT_ON_TIMER, 	/* D11 - PD3 */
	TIMER3A,      	/* D12 - PD4 */
	TIMER1A,     	  /* D13 - PD5 */
	NOT_ON_TIMER,   /* D14 - PD6 */
	NOT_ON_TIMER,   /* D15 - PD7 */
	NOT_ON_TIMER, 	/* D16 - PC0 */
	NOT_ON_TIMER,   /* D17 - PC1 */
	NOT_ON_TIMER,   /* D18 - PC2 */
	NOT_ON_TIMER,   /* D19 - PC3 */
	NOT_ON_TIMER,   /* D20 - PC4 */
	NOT_ON_TIMER,   /* D21 - PC5 */
	NOT_ON_TIMER,   /* D22 - PC6 */
	NOT_ON_TIMER,   /* D23 - PC7 */
	NOT_ON_TIMER,   /* D24 - PA0 */
	NOT_ON_TIMER,   /* D25 - PA1 */
	NOT_ON_TIMER,   /* D26 - PA2 */
	NOT_ON_TIMER,   /* D27 - PA3 */
	NOT_ON_TIMER,   /* D28 - PA4 */
	NOT_ON_TIMER,   /* D29 - PA5 */
	NOT_ON_TIMER,   /* D30 - PA6 */
	NOT_ON_TIMER,   /* D31 - PA7 */
	NOT_ON_TIMER,   /* D32 - PE0 */
	NOT_ON_TIMER,   /* D33 - PE1 */
	TIMER1B         /* D34 - PE2 */
};

#endif // Timer defs

#endif // ARDUINO_MAIN

#endif // Pins_Arduino_h

// vim:ai:cin:sts=2 sw=2 ft=cpp
