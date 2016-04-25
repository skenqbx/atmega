# ATmega Libraries

  * [TWI](lib/TWI/TWI.h) - Hardware TWI/I2C [C++]
  * [USART](lib/USART/USART.h) - Hardware USART0/1 [C++]
  * [ADXL345](lib/ADXL345/ADXL345.h) - 3-Axis Digital I2C Accelerometer [C++]
  * [ITG3200](lib/ITG3200/ITG3200.h) - 3-Axis Digital I2C Gyroscope + Thermometer [C++]
  * [pimp](lib/pimp/pimp.h) - Miscellaneous Utilities [C]

## Currently Supported MCUs

  * ATmega2560

## Example

```c
// main.cpp
#include <TWI.h>
#include <USART.h>
#include <ADXL345.h>
#include <ITG3200.h>

extern "C" {
  #include <avr/delay.h>
  #include <pimp.h>
}

#define ADXL345_ADDRESS 0xA6
#define ITG3200_ADDRESS 0xD0


int main() {
  char buffer[10];    // a small buffer for `itoa()`
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

  serial.write(FF("Hello World!\n"));     // print a string stored in flash
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
```

## Acknowledgements
The code has been developed using the incredible [ATOM](https://atom.io) and [PlatformIO](http://platformio.org/), see [setup](doc/setup.markdown) for details.
