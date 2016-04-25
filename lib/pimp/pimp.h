#ifndef _PIMP_H_
  #define _PIMP_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>


/**
 * FF - FromFlash Macro
 *
 * Stores string in flash memory & copies them into `flash_buffer` for usage
 */
#ifndef PIMP_FLASH_BUFFER
  #define PIMP_FLASH_BUFFER   32
#endif

char flash_buffer[PIMP_FLASH_BUFFER];
#define FF(str) (strcpy_P(flash_buffer, PSTR(str)), flash_buffer)


/**
 * Get free SRAM in bytes
 * http://jeelabs.org/2011/05/22/atmega-memory-use/
 */
uint16_t mem_free();


/**
 *
 */
char* itoa(int i, char b[]);

#endif // _PIMP_H_
