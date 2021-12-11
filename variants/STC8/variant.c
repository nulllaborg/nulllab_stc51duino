
#include "Arduino.h"

void SystemClock_Config(void) {
#ifdef HXT	
    P_SW2 = 0x80;
    XOSCCR = 0xc0;                              //启动外部晶振
    while (!(XOSCCR & 1));                      //等待时钟稳定
    CKDIV = 0x00;                               //时钟不分频
    CKSEL = 0x01;                               //选择外部晶振
#else
	char	*IRC;
#if (F_CPU == 22118400UL)||(F_CPU == 11059200UL)	
	IRC = (__idata char  *)0xfa;   //22M
#else
	IRC = (__idata char  *) 0xfb;  //24M
#endif
	IRCCR = *IRC;	   //装载24MHz/22.1184MHz的IRC参数
	
#if HRC>0
	CLKDIV = HRC;	//主时钟预分频
#endif	
    P_SW2 = 0x80;
    CKSEL = 0x00;                               //选择内部IRC ( 默认 )
#endif	
    P_SW2 = 0x00;
	
}