#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#define P0_0	0x00      /*P00*/
#define P0_1	0x01      /*P01*/
#define P0_2	0x02      /*P02*/
#define P0_3	0x03      /*P03*/
#define P0_4	0x04      /*P04*/
#define P0_5	0x05      /*P05*/
#define P0_6	0x06      /*P06*/
#define P0_7	0x07      /*P07*/
#define P1_0	0x10     /*P10*/
#define P1_1	0x11      /*P11*/
#define P1_2	0x12      /*P12*/
#define P1_3	0x13      /*P13*/
#define P1_4	0x14      /*P14*/
#define P1_5	0x15      /*P15*/
#define P1_6	0x16      /*P16*/
#define P1_7	0x17      /*P17*/
#define P2_0	0x20      /*P20*/
#define P2_1	0x21      /*P21*/
#define P2_2	0x22      /*P22*/
#define P2_3	0x23      /*P23*/
#define P2_4	0x24      /*P24*/
#define P2_5	0x25      /*P25*/
#define P2_6	0x26      /*P26*/
#define P2_7	0x27      /*P27*/
#define P3_0	0x30      /*P30*/
#define P3_1	0x31      /*P31*/
#define P3_2	0x32      /*P32*/
#define P3_3	0x33      /*P33*/
#define P3_4	0x34      /*P34*/
#define P3_5	0x35      /*P35*/
#define P3_6	0x36      /*P36*/
#define P3_7	0x37      /*P37*/
#define P4_0	0x40      /*P40*/
#define P4_1	0x41      /*P41*/
#define P4_2	0x42      /*P42*/
#define P4_3	0x43      /*P43*/
#define P4_4	0x44      /*P44*/
#define P4_5	0x45      /*P45*/
#define P4_6	0x46      /*P46*/
#define P4_7	0x47      /*P47*/

/*在工程中 HAL_config.h 或 boards.txt 中定义，可覆盖以下定义*/
#ifndef LED_BUILTIN
#define LED_BUILTIN      P0_0	/*fixed me!*/
#define LED_BUILTIN_MASK 0x00  /* low in on */
#endif

#ifndef POWER_VCC
# ifdef MENU_VCC 
#  define POWER_VCC MENU_VCC
# else
#  define POWER_VCC 5000
# endif	
#endif

#endif
