/*
  HardwareSerial.c - Hardware serial library for sduino
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

  Modified 2 February 2018 for mcs51 by huaweiwx
  Review 2021 for stc89c52rc by nulllab-jun
*/

#include "Arduino.h"
#include "bsp/STC89C5xRC.h"
#include "bsp/mcu.h"
#include "bsp/compatible.h"
#define MENU_SERIAL 1

// private data //////////////////////////////////////////////////////////////

#ifndef SERIAL_BUFFER_SIZE
#  define SERIAL_BUFFER_SIZE 64
#endif

#if SERIAL_BUFFER_SIZE > 255
typedef struct {
  uint8_t  buffer[SERIAL_BUFFER_SIZE];
  uint16_t size;
  volatile uint16_t head;
  volatile uint16_t tail;
} RINGBUF_TypeDef;
#else
typedef struct {
  uint8_t  buffer[SERIAL_BUFFER_SIZE];
  uint8_t  size;
  volatile uint8_t head;
  volatile uint8_t tail;
} RINGBUF_TypeDef;
#endif

/*如果uart工作于模式0或模式2,此时可以不占用定时器*/
void uart_init0(unsigned long baud)
{
    SCON = 0x50;            //8-bit variable UART
    TMOD = 0x20;            //Set Timer1 as 8-bit auto reload mode
    TH1 = TL1 = -(F_CPU/12/32/baud); //Set auto-reload vaule
    TR1 = 1;                //Timer1 start run
    ES = 1;                 //Enable UART interrupt
    EA = 1;                 //Open master interrupt switch
}
//extern void uart_init0(unsigned long baud);

static XDATA(RINGBUF_TypeDef, rxBuf);// = { { 0 }, 0, 0};
static bool initialized; //=0 internal status. Returned on HardwareSerial()

// private functions  ////////////////////////////////////////////////////////
static void storeChar(uint8_t c, RINGBUF_TypeDef *buf)
{
  noInterrupts();
  int i = (unsigned int)(buf->head + 1) % buf->size;

  // if we should be storing the received character into the location
  // just before the tail (meaning that the head would advance to the
  // current location of the tail), we're about to overflow the buffer
  // and so we don't write the character or advance the head.
  if (i != buf->tail) {
    buf->buffer[buf->head] = c;
    buf->head = i;
  }
  interrupts();
}

// Interrupt handler ///////////////////////////////////////////////////////////
/**
   FUNCTION_PURPOSE: serial interrupt, echo received data.
   FUNCTION_INPUTS:  P0.7(RXD) serial input
   FUNCTION_OUTPUTS: P0.6(TXD) serial output
*/

#if (MENU_SERIAL == 1)
#define InitialUARTx(x)  \
  attachInterrupt(UART_IRQn, UART_IRQHandler, 0); \
  uart_init0(x)


#define RXREG SBUF


void UART_IRQHandler(void)  // UART_ISR, 4
{
  uint8_t c;
  if (RI)
  { /* if reception occur */
    RI = 0;                             /* clear reception flag for next reception */
    c = RXREG;
    storeChar(c, &rxBuf);
  }

  if (TI)
  {
    TI = 0;                             /* if emission occur */
  }
}

size_t HardwareSerial_write(uint8_t c)
{
  noInterrupts();
  TI = 0;
  RXREG = c;
  while (!TI);
  interrupts();
  return 1;
}

#else
#error "This case undefined! Please add"
#endif


// Public Methods //////////////////////////////////////////////////////////////

uint8_t HardwareSerial(void)
{
  return initialized;
}

void HardwareSerial_begin(unsigned long baud)
{
  rxBuf.head = rxBuf.tail = 0;
  rxBuf.size = sizeof(rxBuf.buffer);
  initialized = 1;
  putcharFunc = HardwareSerial_write;
  InitialUARTx(baud);
}

void HardwareSerial_end(void)
{
  // wait for transmission of outgoing data
  rxBuf.head = rxBuf.tail = 0;
  initialized = 0;
}

int HardwareSerial_available(void)
{
  unsigned int rtn;
  noInterrupts();
  rtn = (rxBuf.size + rxBuf.head - rxBuf.tail) % rxBuf.size;
  interrupts();  
  return rtn;
}

int HardwareSerial_peek(void)
{
  int rtn;
  noInterrupts();
  if (rxBuf.head == rxBuf.tail) {
    rtn = -1;
  } else {
    rtn = rxBuf.buffer[rxBuf.tail];
  }
  interrupts();  
  return rtn;
}

int HardwareSerial_read(void)
{
  int rtn;
  noInterrupts();
  if (rxBuf.head == rxBuf.tail) {
    rtn = -1;
  } else {
    rtn = rxBuf.buffer[rxBuf.tail];
    rxBuf.tail = (unsigned int)(rxBuf.tail + 1) % rxBuf.size;
  }
  interrupts();  
  return rtn;
}

void HardwareSerial_flush(void)
{
}

writefunc_p putcharFunc = HardwareSerial_write; /*缺省使用库 HardwareSerial_write*/
int putchar(int c)
{
  putcharFunc((unsigned char)c);      /* output character */
  return (c);
}

//#define PRINTF_TINY   5
//#define PRINTF_SMALL  4
//#define PRINTF_FAST   3
//#define PRINTF_FAST_F 2
//#define PRINTF        1

#if   (USE_PRINTF  > 0)     /*use printf */
__code HWSERIAL_TypeDef Serial = {
  HardwareSerial_available,
  HardwareSerial_begin,
  HardwareSerial_write,
  HardwareSerial_read,
#if   (USE_PRINTF  > 4)  /*5*/
  printf_tiny,
#elif (USE_PRINTF  > 3)
  printf_small,
#elif (USE_PRINTF  > 2)
  printf_fast,
#elif (USE_PRINTF  > 1)
  printf_fast_f,
#else
  printf,
#endif
};
#endif
