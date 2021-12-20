#ifndef _MCU_H_
#define _MCU_H_
#include "STC89C5xRC.h"

#define CORE_STCYn  1

#define SBIT_XSTRING(PORT,PIN)  PORT##PIN

/*creat by stc-isp.exer*/
#if   (F_CPU == 6000000L)
# define DELAY_10US(i)   i = 2
#elif (F_CPU == 8000000L)
# define DELAY_10US(i)   i = 3
# define DELAY_MS(i,j)    i = 2;j=72 
#elif (F_CPU == 10000000L)
# define DELAY_10US(i)   i = 4
# define DELAY_MS(i,j)    i = 2;j=155 
#elif (F_CPU == 11059200L)
# define DELAY_10US(i)   i = 4 
# define DELAY_MS(i,j)    i = 2;j=199 
#elif (F_CPU == 12000000L)
# define DELAY_10US(i)   i = 5
# define DELAY_MS(i,j)    i = 2;j=239 
#elif (F_CPU == 16000000L)
# define DELAY_10US(i)   i = 6
# define DELAY_MS(i,j)    i = 16;j=140 
#elif (F_CPU == 18432000L)
# define DELAY_10US(i)   i = 7
# define DELAY_MS(i,j)    i = 3;j=250 
#elif (F_CPU == 20000000L)
# define DELAY_10US(i)   i = 8 
# define DELAY_MS(i,j)    i = 4;j=58 
#elif (F_CPU == 22118400L)
# define DELAY_10US(i)   i = 9
# define DELAY_MS(i,j)    i = 4;j=146 
#elif (F_CPU == 24000000L)
# define DELAY_10US(i)   i = 9 
# define DELAY_MS(i,j)    i = 4;j=225 
#elif (F_CPU == 25000000L)
# define DELAY_10US(i)   i = 10
# define DELAY_MS(i,j)    i = 5;j=9 
#elif (F_CPU == 38000000L)
# define DELAY_10US(i)   i = 15
# define DELAY_MS(i,j)    i = 7;j=37 
#else
# error  "F_CPU undef! please add me"
#endif

#define sei()  EA=1
#define cli()  EA=0

#define  INT0_IRQn             0
#define  TIMER0_IRQn           1
#define  INT1_IRQn             2
#define  TIMER1_IRQn           3
#define  UART_IRQn             4
#define  TIMER2_IRQn           5

/*AT98x52 兼容 中断矢量定义 */
#define IE0_VECTOR      X0_INTNO         //外部中断0中断号,入口地址为0003H
#define TF0_VECTOR      T0_INTNO         //定时器0中断号,入口地址为000BH
#define IE1_VECTOR      X1_INTNO         //外部中断1中断号,入口地址为0013H
#define TF1_VECTOR      T1_INTNO         //定时器1中断号,入口地址为001BH
#define SI0_VECTOR      UART_INTNO       //串口中断号,入口地址为0023H
#define TF2_VECTOR      T2_INTNO         //定时器2中断号,入口地址为002BH
#define IE2_VECTOR      X2_INTNO         //外部中断2中断号,入口地址为0033H
#define IE3_VECTOR      X3_INTNO         //外部中断3中断号,入口地址为003BH

#endif //_MCU_H_
