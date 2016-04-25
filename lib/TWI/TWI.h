#ifndef _TWI_H_
  #define _TWI_H_

extern "C" {
  #include <avr/io.h>
  #include <util/twi.h>
}


/**
 * TWI Software Configuration
 */
#define TWI_MAX_ADDRESS_RETRIES 100

// SCL_FREQ = F_CPU / (16 + 2 * TWBR)
#define TWI_CLOCK(frequency) (F_CPU / (2 * frequency) - 8)


/**
 * TWI Clock Selection
 */
#define TWI_CLOCK_50KHZ     TWI_CLOCK(50000L)
#define TWI_CLOCK_100KHZ    TWI_CLOCK(100000L)
#define TWI_CLOCK_400KHZ    TWI_CLOCK(400000L)


/**
 * Internal Flags
 */
#define TWI_FLAGS_START         0x01
#define TWI_FLAGS_WRITE         0x02
#define TWI_FLAGS_READ          0x04


/**
 * Error Codes
 */
#define TWI_ERROR_FAILED_START            0x01
#define TWI_ERROR_FAILED_RESTART          0x02
#define TWI_ERROR_NOT_STARTED             0x03
#define TWI_ERROR_INVALID_ADDRESS_MODE    0x04
#define TWI_ERROR_ADDRESS_MAX_RETRIES     0x05
#define TWI_ERROR_FAILED_WRITE            0x06
#define TWI_ERROR_FAILED_READ             0x07
#define TWI_ERROR_FAILED_SEQ_READ         0x08



/**
 * Hardware TWI/I2C Driver for ATmega
 */
class TWI {
  public:
    char address;       // Active device address
    uint8_t clock;      // Selected bus clock (See TWI_CLOCK_* defines)
    char flags;         // Bus Status Flags (See TWI_FLAGS_* defines)
    uint8_t error;      // Error code (See TWI_ERROR_* defines)

    TWI(uint8_t clock = TWI_CLOCK_100KHZ);

    void enable();

    void disable();

    /**
     * Set TWI clock speed (use TWI_CLOCK_* defines)
     */
    void setClock(uint32_t clock);

    /**
     * Set START condition
     */
    void start(char address_);

    /**
     * Set REPEATED_START condition
     */
    void restart(char address_ = 0);

    /**
     * Write a byte
     */
    void write(char value);

    /**
     * Read a byte
     */
    uint8_t read(bool sequential = false);

    /**
     * Set STOP condition
     */
    void stop();

  private:
    /**
     *
     */
    void _address(char address, char mode);
};

#endif // _TWI_H_
