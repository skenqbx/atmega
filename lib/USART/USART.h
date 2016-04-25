#ifndef _USART_H_
  #define _USART_H_

extern "C" {
  #include <avr/io.h>
  #include <avr/interrupt.h>
  #include <util/atomic.h>
}


/**
 * USART Ports
 */
#define USART_PORT0   0x00
#define USART_PORT1   0x01


/**
 * Baudrates
 */
#define USART_BAUDRATE(baud) ((F_CPU / 4 / baud - 1) / 2)

#define USART_BAUDRATE_112K   USART_BAUDRATE(115200L)
#define USART_BAUDRATE_56K    USART_BAUDRATE(57600L)


/**
 * Frame Formats
 */
#define USART_FRAME_5N1 0x00
#define USART_FRAME_6N1 0x02    // (1 << UCSZn0)
#define USART_FRAME_7N1 0x04    // (1 << UCSZn1)
#define USART_FRAME_8N1 0x06    // (1 << UCSZn1) | (1 << UCSZn0)
#define USART_FRAME_5N2 0x08    // (1 << USBSn)
#define USART_FRAME_6N2 0x0A    // (1 << UCSZn0) | (1 << USBSn)
#define USART_FRAME_7N2 0x0C    // (1 << UCSZn1) | (1 << USBSn)
#define USART_FRAME_8N2 0x0E    // (1 << UCSZn1) | (1 << UCSZn0) | (1 << USBSn)
#define USART_FRAME_5E1 0x20
#define USART_FRAME_6E1 0x22
#define USART_FRAME_7E1 0x24
#define USART_FRAME_8E1 0x26
#define USART_FRAME_5E2 0x28
#define USART_FRAME_6E2 0x2A
#define USART_FRAME_7E2 0x2C
#define USART_FRAME_8E2 0x2E
#define USART_FRAME_5O1 0x30
#define USART_FRAME_6O1 0x32
#define USART_FRAME_7O1 0x34
#define USART_FRAME_8O1 0x36
#define USART_FRAME_5O2 0x38
#define USART_FRAME_6O2 0x3A
#define USART_FRAME_7O2 0x3C
#define USART_FRAME_8O2 0x3E



/**
 *
 */
class USART {
  public:
    uint16_t baudrate;
    uint8_t frame;

    USART(
        volatile uint8_t * ucsra,
        volatile uint8_t * ucsrb,
        volatile uint8_t * ucsrc,
        volatile uint16_t * ubrr,
        volatile uint8_t * udr,
        uint16_t baudrate,
        uint8_t frame
    );


    /**
     * Static USART Factory Method
     */
    static USART factory(
        uint8_t port = USART_PORT0,
        uint16_t baudrate = USART_BAUDRATE_112K,
        uint8_t frame = USART_FRAME_8N1
    ) {
      switch (port) {
        case USART_PORT1:
          return USART(&UCSR1A, &UCSR1B, &UCSR1C, &UBRR1, &UDR1, baudrate, frame);
        default:
          return USART(&UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, &UDR0, baudrate, frame);
      }
    }

    void enable();

    void disable();

    void write(unsigned char data);
    void write(const char *data);

    bool readable();

    uint8_t read();

  private:
    volatile uint16_t * const _ubrr;
    volatile uint8_t * const _ucsra;
    volatile uint8_t * const _ucsrb;
    volatile uint8_t * const _ucsrc;
    volatile uint8_t * const _udr;
};

#endif // _USART_H_
