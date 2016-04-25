#include "TWI.h"



TWI::TWI(uint8_t clock) :
    clock(clock), flags(0), error(0)
{}


void TWI::enable() {
  TWBR = clock;
}


void TWI::disable() {
  address = 0;
  flags = 0;
  error = 0;
  TWCR = 0;
  TWBR = 0;
}


void TWI::start(char address_) {
  address = address_;
  uint8_t status;

  if (flags & TWI_FLAGS_START) {
    return restart();
  }
  error = 0;

  begin:

  // Set START condition
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  // Wait for the interrupt bit to get set
  while (!(TWCR & (1 << TWINT)));

  switch ((status = TW_STATUS)) {
    case TW_START:
      flags |= TWI_FLAGS_START;
      break;

    case TW_MT_ARB_LOST:
      goto begin;

    default:
      error = 0x01;
  }
}


void TWI::restart(char address_) {
  if (address_ > 0) {
    address = address_;
  }
  uint8_t status;
  error = 0;
  flags = 0;

  begin:

  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));

  switch ((status = TW_STATUS)) {
    case TW_REP_START:
      flags |= TWI_FLAGS_START;
      break;

    case TW_MT_ARB_LOST:
      goto begin;

    default:
      error = 0x02;
  }
}


void TWI::stop() {
  if (flags & TWI_FLAGS_START) {
    flags = 0;
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
  }
}


void TWI::_address(char address, char mode) {
  uint8_t n, status;
  if (error > 0) { return; }

  if (!(flags & TWI_FLAGS_START)) {
    error = 0x03;
    return;
  }

  switch (mode) {
    case TW_READ:
      if (flags & TWI_FLAGS_WRITE) {
        restart();
      }
      break;

    case TW_WRITE:
      if (flags & TWI_FLAGS_READ) {
        restart();
      }
      break;

    default:
      error = 0x04;
      return;
  }

  if (error > 0) { return; }

  restart:

  if (++n > TWI_MAX_ADDRESS_RETRIES) {
    error = 0x05;
    return;
  }

  begin:

  TWDR = address | mode;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));

  switch ((status = TW_STATUS)) {
    case TW_MT_SLA_NACK:
    case TW_MR_SLA_NACK:
      goto restart;

    case TW_MT_ARB_LOST:
      goto begin;
  }
}


void TWI::write(char value) {
  uint8_t status;

  if (!(flags & TWI_FLAGS_WRITE)) {
    _address(address, TW_WRITE);
    flags |= TWI_FLAGS_WRITE;
  }

  if (error > 0) { return; }

  begin:

  TWDR = value;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));

  switch ((status = TW_STATUS)) {
    case TW_MT_DATA_ACK:
      break;

    case TW_MT_ARB_LOST:
      goto begin;

    default:
      error = 0x06;
  }
}


uint8_t TWI::read(bool sequential) {
  uint8_t value;

  if (!(flags & TWI_FLAGS_READ)) {
    _address(address, TW_READ);
    flags |= TWI_FLAGS_READ;
  }
  if (error > 0) { return 0; }

  if (sequential) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));

    if (TW_STATUS != TW_MR_DATA_ACK) {
      error = 0x08;
      return 0;
    }

  } else {
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));

    if (TW_STATUS != TW_MR_DATA_NACK) {
      error = 0x07;
      return 0;
    }
  }

  value = TWDR;
  return value;
}
