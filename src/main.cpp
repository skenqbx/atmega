#include "main.h"


int main() {
  char buffer[10]; // a small buffer for `itoa()`
  const char newline = '\n';

  USART serial = USART::factory(
      USART_PORT0,
      USART_BAUDRATE_112K,
      USART_FRAME_8N1
  );
  TWI twi(TWI_CLOCK_400KHZ);
  ITG3200 itg3200(&twi, ITG3200_ADDRESS);
  ADXL345 adxl345(&twi, ADXL345_ADDRESS);

  serial.enable();
  twi.enable();
  itg3200.enable();
  adxl345.enable();

  serial.write(FF("Hello World!\n"));
  serial.write(itoa(mem_free(), buffer));

  for (;;) {
    itg3200.update();
    serial.write(itoa(itg3200.z * 1000, buffer));
    serial.write(newline);

    adxl345.update();
    serial.write(itoa(adxl345.z * 1000, buffer));
    serial.write(newline);

    serial.write(itoa(mem_free(), buffer));
    serial.write(newline);

    _delay_ms(100);
  }
}
