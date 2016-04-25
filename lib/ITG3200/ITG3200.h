#ifndef _ITG3200_H_
  #define _ITG3200_H_

#include <TWI.h>

// Fixed usage of 17 Bytes SRAM

/**
 * ITG3200 Software Configuration
 */
// #define ITG3200_TWI_STOP


/**
 * ITG3200 Register Map
 */
#define ITG3200_REG_DEVICE_ID       0x00
#define ITG3200_REG_SMPLRT_DIV      0x15

  // Sample Rate Divider
  // Fsample = Fint / (divider + 1) where Fint is either 1kHz or 8kHz
  // Fint is set to 1kHz
  // Set divider to 9 for 100 Hz sample rate

#define ITG3200_REG_DLPF_FS         0x16

  // DLPF, Full Scale Register Bits
  // FS_SEL must be set to 3 for proper operation
  // Set DLPF_CFG to 3 for 1kHz Fint and 42 Hz Low Pass Filter
  #define ITG3200_DLPF_CFG_0      (1 << 0)
  #define ITG3200_DLPF_CFG_1      (1 << 1)
  #define ITG3200_DLPF_CFG_2      (1 << 2)
  #define ITG3200_DLPF_FS_SEL_0   (1 << 3)
  #define ITG3200_DLPF_FS_SEL_1   (1 << 4)

#define ITG3200_REG_INT_CFG         0x17

  // Interrupt Configuration Bist
  #define ITG3200_INT_CFG_ACTL            (1 << 7)
  #define ITG3200_INT_CFG_OPEN            (1 << 6)
  #define ITG3200_INT_CFG_LATCH_INT_EN    (1 << 5)
  #define ITG3200_INT_CFG_INT_ANYRD       (1 << 4)
  #define ITG3200_INT_CFG_ITG_RDY_EN      (1 << 2)
  #define ITG3200_INT_CFG_RAW_RDY_EN      (1 << 0)

#define ITG3200_REG_INT_STATUS      0x1A
#define ITG3200_REG_TEMP_OUT_H      0x1B
#define ITG3200_REG_TEMP_OUT_L      0x1C
#define ITG3200_REG_GYRO_XOUT_H     0x1D
#define ITG3200_REG_GYRO_XOUT_L     0x1E
#define ITG3200_REG_GYRO_YOUT_H     0x1F
#define ITG3200_REG_GYRO_YOUT_L     0x20
#define ITG3200_REG_GYRO_ZOUT_H     0x21
#define ITG3200_REG_GYRO_ZOUT_L     0x22
#define ITG3200_REG_PWR_MGM         0x3E

  // Power Management Register Bits
  // Recommended to set CLK_SEL to 1,2 or 3 at startup for more stable clock
  #define ITG3200_PWR_MGM_CLK_SEL_0     (1 << 0)
  #define ITG3200_PWR_MGM_CLK_SEL_1     (1 << 1)
  #define ITG3200_PWR_MGM_CLK_SEL_2     (1 << 2)
  #define ITG3200_PWR_MGM_STBY_Z        (1 << 3)
  #define ITG3200_PWR_MGM_STBY_Y        (1 << 4)
  #define ITG3200_PWR_MGM_STBY_X        (1 << 5)
  #define ITG3200_PWR_MGM_SLEEP         (1 << 6)
  #define ITG3200_PWR_MGM_H_RESET       (1 << 7)



class ITG3200 {
  public:
    TWI * twi;
    uint8_t address;

    float x;
    float y;
    float z;
    float t; // temperature in degree celcius

    ITG3200(TWI * twi, uint8_t address = 0xD0);

    uint8_t enable();
    uint8_t disable();
    uint8_t update();
    uint8_t temperature();
};

#endif // _ITG3200_H_
