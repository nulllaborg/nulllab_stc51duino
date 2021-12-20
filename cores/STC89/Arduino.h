/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 2 February 2018 for MSC51 by huaweiwx 
  Modified 2 February 2018 for stc89c52 by nulllab-jun
*/

#ifndef Arduino_h
#define Arduino_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
//#include "utils/compatible.h"
//#include "xmacro.h"
#include "bsp/STC89C5xRC.h"
#include <compiler.h>
#include "pins_arduino.h"

// FIXME: workarounds for missing features or unimplemented functions
// cancel out the PROGMEM attribute - used only for atmel CPUs
#define PROGMEM
void yield(void);

// we use pre-defined IRQ function the way wiring does
#define WIRING

#define HIGH  0x1
#define LOW   0x0

/*特定 mnu.h 定义 gpio 模式*/
/*default*/
#ifndef QUASI         /*准双向口,注意:读外部状态时,先要锁存为1,延时2个nop后再读取外部端口状态*/
#define QUASI	0x0	
#endif
#ifndef OUTPUT              /*强推挽输出,每个i/o口都可以提供20mA的驱动能力,要接限流电阻,注意整个芯片不要超过120mA*/
#define OUTPUT		0x1
#endif
#ifndef OUTPUT_PP           /*强推挽输出,每个i/o口都可以提供20mA的驱动能力,要接限流电阻,注意整个芯片不要超过120mA*/
#define OUTPUT_PP	0x1    
#endif
#ifndef INPUT           /*强推挽输出,每个i/o口都可以提供20mA的驱动能力,要接限流电阻,注意整个芯片不要超过120mA*/
#define INPUT		0x2     /*仅为输入*/
#endif
#ifndef OUTPUT_OD           /*强推挽输出,每个i/o口都可以提供20mA的驱动能力,要接限流电阻,注意整个芯片不要超过120mA*/
#define	OUTPUT_OD	0x3    /*开漏*/
#endif

// undefine mathlib's pi if encountered
#ifdef PI
#undef PI
#endif
#ifdef HALF_PI
#undef HALF_PI
#endif
#ifdef TWO_PI
#undef TWO_PI
#endif

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE  1
#define FALLING 2
#define RISING  3

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define interrupts()   EA = 1
#define noInterrupts() EA = 0

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesPerMillisecond() ( F_CPU / 1000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

//#define bitSet(value, b) (__asm__("bset\t"))
//#define bitClear(value, b) (__asm__("bres\t"))

#define bitRead(value, b)            (((value) >> (b)) & 0x01)
#define bitSet(value, b)             ((value) |= (1UL << (b)))
#define bitClear(value, b)           ((value) &= ~(1UL << (b)))
#define bitWrite(value, b, bitvalue) ((bitvalue) ? bitSet(value, b) : bitClear(value, b))

#ifndef _BV
#define _BV(x) (1<<(x))
#endif
#ifndef cbi /*compatible with wiring*/
#define cbi(a, b)  bitClear(a,b)
#endif
#ifndef sbi  /*compatible with wiring*/
#define sbi(a, b) bitSet(a, b)
#endif

#define maskSet(value, mask) ((value) |= (mask))
#define maskClear(value, mask) ((value) &= ~(mask))


// avr-libc defines _NOP() since 1.6.2
#ifndef _NOP
#define _NOP() NOP()
#endif

#ifndef F
#define F(x)
#endif

/* for SDCC this is supposed to be "__critical{" and "}", but up to
 * sdcc version 3.6.4 it is wrongly implemented. */
/* so geht es nicht:
#define BEGIN_CRITICAL		__asm__("push\tcc");__asm__("sim");
#define END_CRITICAL		__asm__("pop\tcc");
*/
#define BEGIN_CRITICAL		__critical {
#define END_CRITICAL		}
/* klappt:
#define BEGIN_CRITICAL
#define END_CRITICAL
*/

// #define bit(b) (1UL << (b)) sdcc bit is __bit keywords

//typedef bool        boolean;
typedef unsigned int  word;
typedef unsigned char byte;

void init(void);
void initVariant(void);		// weak

int atexit(void (*func)());	// __attribute__((weak));
void serialEvent(void);		// weak

#include "wiring_digital.h"

int analogRead(uint8_t);
void analogReference(uint8_t);
void analogWrite(uint8_t, int);

#include "wiring.h"

unsigned long pulseIn(uint8_t, uint8_t, unsigned long);
unsigned long pulseInLong(uint8_t, uint8_t, unsigned long);

//void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
//uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);

void attachInterrupt(uint8_t, void (*)(void), int);
void detachInterrupt(uint8_t);

void setup(void);
void loop(void);

// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.

#define analogInPinToBit(P) (P)

//extern const uint8_t digital_pin_to_port[];
//extern const uint8_t PROGMEM digital_pin_to_bit_PGM[];
//extern const uint8_t digital_pin_to_bit_mask[];
//extern const uint8_t digital_pin_to_timer[];

// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.
// 
#define digitalPinToPort(pin)    (pin >> 4)
#define digitalPinToBitMask(pin) (1 << (pin & 0x0f))
//#define digitalPinToTimer(P)     ( digital_pin_to_timer[(P)] )
//#define analogInPinToBit(P)    (P)
//#define portOutputRegister(P)  ( (volatile uint8_t *)( port_to_output[(P)]) )
//#define portInputRegister(P)   ( (volatile uint8_t *)( port_to_input[(P)]) )
//#define portModeRegister(P)    ( (volatile uint8_t *)( port_to_mode[(P)]) )

#define NOT_A_PIN  0xff
#define NOT_A_PORT 0xff
#define ARDUINO_PINMASK   0x08
#define ARDUINO_PORTMASK  0x80
#define NOT_A_PORTPIN(x)  ((x)&(ARDUINO_PORTMASK|ARDUINO_PINMASK))
#define IS_A_PIN(x)       !NOT_A_PORTPIN(x)


#define NOT_AN_INTERRUPT -1

#ifdef ARDUINO_MAIN
//#define PA 1
//#define PB 2
//#define PC 3
//#define PD 4
//#define PE 5
//#define PF 6
//#define PG 7
//#define PH 8
//#define PJ 10
//#define PK 11
//#define PL 12
#endif

//FIXME#include "WCharacter.h"
//FIXME#include "WString.h"
#include "HardwareSerial.h"

//uint16_t makeWord(uint16_t w);
//uint16_t makeWord(byte h, byte l);

//#define word(...) makeWord(__VA_ARGS__)


void tone(uint8_t _pin, unsigned int frequency, unsigned long duration);
void noTone(uint8_t _pin);

// WMath prototypes
long random(long howbig);
long random_minmax(long howsmall, long howbig);
void randomSeed(unsigned long seed);
long map(long x, long in_min, long in_max, long out_min, long out_max);

inline unsigned int makeWord(unsigned char h, unsigned char l) { return (h << 8) | l; }

#endif //Arduino_h
