/*
  wiring.c - Partial implementation of the Wiring API for the mcs51.
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

  DELAY_10US)(i) and DELAY_MS(i,j) created by stc-isp-15xx-v6.86s.exe
  Modified 2 February 2018 for mcs51 by huaweiwx 
*/

#define  WIRING_MAIN
#include "Arduino.h"
#include "bsp/mcu.h"
#include "bsp/STC89C5xRC.h"
// #define USE_SYSTICK 1

extern void SystemClock_Config(void);

/****************  简单延时 **************************/
void delay_loop(unsigned char cnt)
{
	while (--cnt);
}


#if USE_SYSTICK

static volatile uint32_t dwTickCount = 0;

/***************  Timer0 中断函数 *********************/
void Timer0_IRQHandler (void) //1毫秒
{
    TH0 = TH0_INIT; TL0 = TL0_INIT; //重载定时初值
    TF0 = 0;                        //清除TF0标志
    dwTickCount++;                  //systic 计数 
}

void init(void){
    SystemClock_Config();
    dwTickCount = 0;
    attachInterrupt(TIMER0_IRQn, Timer0_IRQHandler, 0);
    TMOD = 0x01;                    //set timer0 as mode1 (16-bit)
    TL0 = TL0_INIT;                 //initial timer0 low byte
    TH0 = TH0_INIT;                 //initial timer0 high byte
    TR0 = 1;                        //timer0 start running
    ET0 = 1;                        //enable timer0 interrupt
    EA = 1;                         //open global interrupt switch
}

unsigned long millis()
{
    return dwTickCount;
}

unsigned long micros()
{
    uint32_t m,u;
    uint8_t  hi,lo;

    lo =  TL0; hi =  TH0; 
    u = dwTickCount*1000;

    m = ((((hi<<8)| lo)- T1MS)*1000);
    u += m/T1MS; 

    return u;
}

void delay(unsigned int ms){
    uint32_t s = dwTickCount;
    uint32_t e = s + ms;
    if(e < s){
       while(e < millis());
    }
    while(millis()< e);
}

void delayMicroseconds(unsigned int us)
{
    uint32_t s = micros();
    uint32_t e = s + us;
    if(e < s){
       while(e < micros());
    }
    while(micros()< e);
}

#else

void init(void){
    SystemClock_Config();
}

void delay10us(unsigned int us)
{   
    unsigned char i;
    do{
      DELAY_10US(i);
      while (--i);
    }while(--us);
}

void delay(unsigned int ms)
{
    unsigned char i, j;

    do {
      DELAY_MS(i,j);
      do {
         while (--j);
      } while (--i);
    }while (--ms);
}
#endif
