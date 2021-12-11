#ifndef __GPIO_H__
#define __GPIO_H__

#define CHIP_PIN_LIST \
PIN(0,0),      /*0  P00*/\
PIN(0,1),      /*1  P01*/\
PIN(0,2),      /*2  P02*/\
PIN(0,3),      /*3  P03*/\
PIN(0,4),      /*4  P04*/\
PIN(0,5),      /*5  P05*/\
PIN(0,6),      /*6  P06*/\
PIN(0,7),      /*7  P07*/\
PIN(1,0),,     /*8  P10*/\
PIN(1,1),      /*9  P11*/\
PIN(1,2),      /*10 P12*/\
PIN(1,3),      /*11 P13*/\
PIN(1,4),      /*12 P14*/\
PIN(1,5),      /*13 P15*/\
PIN(1,6),      /*14 P16*/\
PIN(1,7),      /*15 P17*/\
PIN(2,0),      /*16 P20*/\
PIN(2,1),      /*17 P21*/\
PIN(2,2),      /*18 P22*/\
PIN(2,3),      /*19 P23*/\
PIN(2,4),      /*20 P24*/\
PIN(2,5),      /*21 P25*/\
PIN(2,6),      /*22 P26*/\
PIN(2,7),      /*23 P27*/\
PIN(3,0),      /*24 P30*/\
PIN(3,1),      /*25 P31*/\
PIN(3,2),      /*26 P32*/\
PIN(3,3),      /*27 P33*/\
PIN(3,4),      /*28 P34*/\
PIN(3,5),      /*29 P35*/\
PIN(3,6),      /*30 P36*/\
PIN(3,7),      /*31 P37*/\
PIN(4,0),      /*32 P40*/\
PIN(4,1),      /*33 P41*/\
PIN(4,2),      /*34 P42*/\
PIN(4,3),      /*35 P43*/\
PIN(4,4),      /*36 P44*/\
PIN(4,5),      /*37 P45*/\
PIN(4,6),      /*38 P46*/\
PIN(4,7)       /*39 P47*/

#ifdef VARIANT_PIN_LIST
#define PIN_LIST VARIANT_PIN_LIST
#else
#define PIN_LIST CHIP_PIN_LIST
#endif

/*使用宏定义，GPIO mode set 兼容与 stc 8 */
#define gpioMode_QS(a,b)
#define gpioMode_PP(a,b)
#define gpioMode_IN(a,b)   P##a##b = 1
#define gpioMode_OUT(a,b) 
#define gpioMode_OD(a,b)  
#define gpioMode(a,b,m)   

#define portMode_QS(a)
#define portMode_PP(a)
#define portMode_OUT(a)
#define portMode_IN(a)     P##a=0xff
#define portMode_OD(a)
#define portMode(a,m)

#endif  //__GPIO_H__
