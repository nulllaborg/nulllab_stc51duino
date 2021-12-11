/* for stc12c56 */
#ifndef __ISR_H__
#define __ISR_H__

#define  INT0_IRQn             0
#define  TIMER0_IRQn           1
#define  INT1_IRQn             2
#define  TIMER1_IRQn           3

#define  UART_IRQn             4

#define  TIMER2_IRQn           5

/* AT89C52 IRQn compatible */
#ifndef IE0_VECTOR
#define IE0_VECTOR            0       /* 0x03 external interrupt 0 */
#define TF0_VECTOR            1       /* 0x0b timer 0 */
#define IE1_VECTOR            2       /* 0x13 external interrupt 1 */
#define TF1_VECTOR            3       /* 0x1b timer 1 */
#define SI0_VECTOR            4       /* 0x23 serial port 0 */
#define TF2_VECTOR            5       /* 0x2B timer 2 */
#endif

/*仅 sdcc 需要在 main 函数前显式声明 */
#if defined (SDCC) || defined (__SDCC)

INTERRUPT(int0_isr	,0);
INTERRUPT(timer0_isr,1);
INTERRUPT(int1_isr	,2);
INTERRUPT(timer1_isr,3);
INTERRUPT(uart_isr	,4);
INTERRUPT(timer2_isr,5);

#endif

#endif //__ISR_H__