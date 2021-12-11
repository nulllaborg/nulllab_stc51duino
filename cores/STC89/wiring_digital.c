/*
  wiring_digital.c - digital input and output functions
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  Modified 2 February 2018 for mcs51  by huaweiwx 
*/
#include "Arduino.h"

/* This char array helps to convert pin map to port*/
const uint8_t pinToMask[] = { 1, 2, 4, 8, 16, 32, 64, 128 };

uint8_t portRead(uint8_t ucPort){
	    uint8_t rtn = 0;
		switch (ucPort){
#ifdef  SFR_P0
		case 0:
		   rtn = P0;
		   break;
#endif
#ifdef  SFR_P1
        case 1:		   
		   rtn = P1;
		   break;
#endif
#ifdef  SFR_P2
        case 2:		   
		   rtn = P2;
		   break;
#endif
#ifdef SFR_P3
        case 3:		   
		   rtn = P3;
		   break;
#endif
#ifdef SFR_P4
        case 4:		   
		   rtn = P4;
		   break;
#endif
#ifdef SFR_P5
        case 5:		   
		   rtn = P5;
		   break;
#endif
	}
	return rtn;
}

void portWrite(uint8_t ucPort,uint8_t val){
		switch (ucPort){
#ifdef SFR_P0
		case 0:
		   P0 = val;
		   break;
#endif
#ifdef SFR_P1
        case 1:		   
		   P1 = val;
		   break;
#endif
#ifdef SFR_P2
        case 2:		   
		   P2 = val;
		   break;
#endif
#ifdef SFR_P3
        case 3:		   
		   P3 = val;
		   break;
#endif
#ifdef SFR_P4
        case 4:		   
		   P4 = val;
		   break;
#endif
#ifdef SFR_P5
        case 5:		   
		   P5 = val;
		   break;
#endif
	}
}

void digitalWriteHigh(uint8_t pin){
	uint8_t ucPort,ucPin,mask;
	if(pin & 0x88) return;  /*0b10001000(0x88) is not a pin*/
	ucPort = pin >>4;
	ucPin =  pin & 0x07;
	mask = pinToMask[ucPin];
	mask |= portRead(ucPort);
	portWrite(ucPort,mask);
}

void digitalWriteLow(uint8_t pin){
	uint8_t ucPort,ucPin;
	if(NOT_A_PORTPIN(pin)) return;  /*0b10001000(0x88) is not a pin*/
	ucPort = pin >>4;
	ucPin =  pin & 0x07;
	portWrite(ucPort,portRead(ucPort) & (~pinToMask[ucPin]));
}

void digitalToggle(uint8_t pin){
	uint8_t ucPort,ucPin,mask;
	if(NOT_A_PORTPIN(pin)) return;  /*0b10001000(0x88) is not a pin*/
	ucPort = pin >>4;
	ucPin =  pin & 0x07;
	mask = pinToMask[ucPin];
	mask ^= portRead(ucPort);
	portWrite(ucPort,mask);
}

void digitalWrite(uint8_t pin, bool val)
{
	if(val) {
		digitalWriteHigh(pin);
	}else{
		digitalWriteLow(pin);
	}
}

bool digitalRead(uint8_t pin)
{
	uint8_t readp =0;
	uint8_t ucPort,ucPin;
	if(NOT_A_PORTPIN(pin)) return 0;  /*0b10001000(0x88) is not a pin*/
	ucPort = pin >>4;
	ucPin =  pin & 0x07;

    readp = portRead(ucPort);
	return (readp & pinToMask[ucPin]);
}

void pinMode(uint8_t pin, uint8_t mode){
	if(mode == INPUT) digitalWriteHigh(pin);  /*STC89/90 is QUASI/OD, set to HIGH for read */
}
