#include "USART.h"



USART::USART(
    volatile uint8_t * ucsra,
    volatile uint8_t * ucsrb,
    volatile uint8_t * ucsrc,
    volatile uint16_t * ubrr,
    volatile uint8_t * udr,
    uint16_t baudrate,
    uint8_t frame
) :
    _ucsra(ucsra), _ucsrb(ucsrb), _ucsrc(ucsrc),
    _ubrr(ubrr), _udr(udr),
    baudrate(baudrate), frame(frame)
{}


void USART::enable() {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    // Set fast mode
    *_ucsra |= (1 << U2X0);
    // Set baud rate
    *_ubrr = baudrate;
    // Set frame format
    *_ucsrc = frame;
    // Enable receiver and transmitter
    *_ucsrb |= (1 << RXEN0) | (1 << TXEN0);
  }
}


void USART::disable() {
  *_ucsrb = 0;
}


void USART::write(unsigned char data) {
  // Wait for empty transmit buffer
  while (!(*_ucsra & (1 << UDRE0)));
  // Put data into buffer, sends the data
  *_udr = data;
}


void USART::write(const char *data) {
  while (*data) {
    write(*data++);
  };
}


bool USART::readable() {
  return *_ucsra & (1 << UDRE0);
}


uint8_t USART::read() {
  // Wait for data to be received
  while (!(*_ucsra & (1 << RXC0)));
  // Get and return received data from buffer
  return *_udr;
}
