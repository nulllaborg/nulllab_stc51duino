/*
  Modified 2 February 2018 for mcs51  by huaweiwx
 */
  
#ifndef __WIRING_DIGITAL_H__
#define __WIRING_DIGITAL_H__

uint8_t portRead(uint8_t ucPort);
void    digitalWriteHigh(uint8_t pin);
void    digitalWriteLow(uint8_t pin);
void    portWrite(uint8_t ucPort,uint8_t val);
void    digitalWrite(uint8_t pin, bool val);
void    digitalToggle(uint8_t pin);
bool    digitalRead(uint8_t pin);

#endif //__WIRING_DIGITAL_H__