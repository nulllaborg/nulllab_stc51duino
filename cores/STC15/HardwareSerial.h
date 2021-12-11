/*
  HardwareSerial.h - Hardware serial library for sduino
  Copyright (c) 2016 Michael Mayer

  Plain C version of HardwareSerial.cpp of the Arduino project.
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

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
  
  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 15 December 2016 by Michael Mayer
  Modified 2 February 2018 for mcs51  by huaweiwx
*/

#ifndef _HARDWARE_SERIAL_H_
#define _HARDWARE_SERIAL_H_

#include <stdlib.h>
#include <Print.h>

// Define config for Serial.begin(baud, config);
/* coding of the bit field: 00sw .pp.
 * wordlength w: 0:8 1:9 (5,6,7 not supported)
 * parity     pp:  0:n 2:e 3:o
 * stopbits   s:  0:1 1:2
 * => 8x1=0x0x, 9x1=0x1x, 8x2=0x2x, 9x2=0x3x
 * => n=0xx0, e=0xx4, o=0xx6
*/
#define SERIAL_8N1 0x00
#define SERIAL_9N1 0x10
#define SERIAL_8N2 0x20
#define SERIAL_9N2 0x30
#define SERIAL_8E1 0x04
#define SERIAL_9E1 0x14
#define SERIAL_8E2 0x24
#define SERIAL_9E2 0x34
#define SERIAL_8O1 0x06
#define SERIAL_9O1 0x16
#define SERIAL_8O2 0x26
#define SERIAL_9O2 0x36

#define MASK_PARITY	0x06
#define MASK_STOPBITS	0x20
#define MASK_DATABITS	0x10


// Public Methods //////////////////////////////////////////////////////////////

uint8_t HardwareSerial(void);
void HardwareSerial_begin(unsigned long baud);
void HardwareSerial_end(void);

int HardwareSerial_available(void);
int HardwareSerial_read(void);
size_t HardwareSerial_write(uint8_t c);
void HardwareSerial_flush(void);
extern writefunc_p putcharFunc;

#if   (USE_PRINTF  > 0)     /*use printf */
typedef struct {
  i_v_funcType available;
  v_l_funcType begin;
  s_c_funcType write;
  i_v_funcType read;
#if   (USE_PRINTF  > 4)     /*5 printf_tiny*/
  v_c_printfType printf;
#elif (USE_PRINTF  > 3)     /*4 printf_small*/
  v_printfType printf;
#elif (USE_PRINTF  > 2)     /*3 printf_fast*/
  v_c_printfType printf;
#elif (USE_PRINTF  > 1)     /*2 printf_fast_f*/
  v_c_printfType printf;
#else
  i_printfType printf; /*1 printf*/
#endif
} HWSERIAL_TypeDef;
extern __code HWSERIAL_TypeDef Serial;
#endif

// Alias Definitions for a more Arduino-like look ////////////////////////////

//#define Serial			 HardwareSerial()
#define Serial_begin	 HardwareSerial_begin
#define Serial_available HardwareSerial_available
#define Serial_read		 HardwareSerial_read
#define Serial_write	 HardwareSerial_write
#define Serial_flush	 HardwareSerial_flush
#define Serial_end		 HardwareSerial_end


// variants of the standard Serial.print() function: Separate implementations
// for string, char, unsigned, signed int
#define Serial_print_s(S)	Print_print_s(HardwareSerial_write,S)
#define Serial_print_sn(S)	Print_print_sn(HardwareSerial_write,S,N)
#define Serial_print_c(C)	HardwareSerial_write(C)

// print signed/unsigned integer values (char, short, int, long) as decimal values
#define Serial_print_i(I)	Print_print_i(HardwareSerial_write,I)
#define Serial_print_u(U)	Print_print_u(HardwareSerial_write,U)

// print signed/unsigned integer values (char, short, int, long) to base B
#define Serial_print_ib(I,B)	Print_print_ib(HardwareSerial_write,I,B)
#define Serial_print_ub(U,B)	Print_print_ub(HardwareSerial_write,U,B)

// print float value
#define Serial_print_f(F)	   Print_print_fd(HardwareSerial_write,F,2)
#define Serial_print_fd(F,D)	Print_print_fd(HardwareSerial_write,F,D)

#define Serial_println()	Print_println(HardwareSerial_write)
#define Serial_println_s(S)	Print_println_s(HardwareSerial_write,S)
#define Serial_println_sn(S,N)	Print_println_sn(HardwareSerial_write,S,N)
#define Serial_println_u(U)	Print_println_u(HardwareSerial_write,U)
#define Serial_println_i(I)	Print_println_i(HardwareSerial_write,I)
#define Serial_println_ib(I,B)	Print_println_ib(HardwareSerial_write,I,B)
#define Serial_println_ub(U,B)	Print_println_ub(HardwareSerial_write,U,B)
#define Serial_println_f(F)	Print_println_fd(HardwareSerial_write,F,2)
#define Serial_println_fd(F,D)	Print_println_fd(HardwareSerial_write,F,D)


#endif
