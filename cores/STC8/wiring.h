/*
  wiring.h
  Modified 2 February 2018 for mcs51 by huaweiwx 
*/
#ifndef _WIRING_H_
#define _WIRING_H_

#ifndef USE_SYSTICK
#define USE_SYSTICK 1
#endif

#if CORE_STCYn > 1
 #define T1MS   (65536L-F_CPU/1000)      //1ms timer calculation method in 1T mode
#elif CORE_STCYn == 1
 #define T1MS (65536L-F_CPU/12/1000)   //1ms timer calculation method in 12T mode
#else
 #error NOT STC core or CORE_STCYn undef!	
#endif

#define TH0_INIT         (T1MS  >>  8)
#define TL0_INIT         (T1MS & 0xff)

void delay_loop(unsigned char cnt);


#if USE_SYSTICK

unsigned long millis();
unsigned long micros();
void delay(unsigned int ms);
void delayMicroseconds(unsigned int us);

#else

void delay10us(unsigned int us);
void delay(unsigned int ms);

#define delayMicroseconds(us) if(us>10){delay10us(us/10);}else{delay_loop(us);}

#endif //USE_SYSTICK

#endif  //_WIRING_H_
