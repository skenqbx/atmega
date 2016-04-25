#include "pimp.h"


uint16_t mem_free() {
  extern int __heap_start, *__brkval;

  int v;

  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}


char* itoa(int i, char b[]) {
    char const digit[] = "0123456789";
    char* p = b;

    if (i < 0){
      *p++ = '-';
      i *= -1;
    }

    // Move to where representation ends
    int shifter = i;
    do {
      ++p;
      shifter = shifter / 10;
    } while (shifter);
    *p = '\0';

    // Move back, inserting digits as u go
    do {
      *--p = digit[i % 10];
      i = i / 10;
    } while (i);

    return b;
}
