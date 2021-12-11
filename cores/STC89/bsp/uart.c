//----------------------------------------------------------------
// stc firm lib
// for stc12c56xx
// uart.c
// by flotox@yeah.net
// http://hi.baidu.com/flotox
// 2011-07-14
// for arduino by huaweiwx@sina.com 2018.5.19
//----------------------------------------------------------------

#include"Arduino.h"

/*由BRC.exe生成的波特率设置函数(只能设置工作于模式1、3下的波特率),默认允许接收,如果为方式0或方式2则由自己编写*/
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
