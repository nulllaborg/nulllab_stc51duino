// for stc89

#include "Arduino.h"
#include <compiler.h>
#include "bsp/compatible.h"
#define INTERRUPT_NUMS    6

typedef void    (*voidFuncPtr)(void);

XDATA(voidFuncPtr, callback[INTERRUPT_NUMS]) = {NULL};

#define INTERRUPT_ISR(a,b)  INTERRUPT(a,b){if (callback[b]) callback[b]();}

INTERRUPT_ISR(int0_isr,   0)
INTERRUPT_ISR(timer0_isr, 1)
INTERRUPT_ISR(int1_isr,   2)
INTERRUPT_ISR(timer1_isr, 3)
INTERRUPT_ISR(uart_isr,   4)
INTERRUPT_ISR(timer2_isr, 5)

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode)
{
  if (interruptNum < INTERRUPT_NUMS) {
    (void)mode;                            /*UNUSED*/
    callback[interruptNum] = userFunc;
  }
}

void detachInterrupt(uint8_t interruptNum)
{
  if (interruptNum < INTERRUPT_NUMS) {
    callback[interruptNum] = NULL;
  }
}