#ifndef _MAIN_H_
  #define _MAIN_H_

#include <TWI.h>
#include <ADXL345.h>
#include <ITG3200.h>
#include <USART.h>

extern "C" {
  #include <avr/delay.h>
  #include <pimp.h>
}

#define ADXL345_ADDRESS 0xA6
#define ITG3200_ADDRESS 0xD0

#endif // _MAIN_H_
