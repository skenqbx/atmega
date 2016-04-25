#ifndef _ADXL345_H_
  #define _ADXL345_H_

#include <TWI.h>


/**
 * ADXL345 Software Configuration
 */
// #define ADXL345_TWI_STOP


/**
 * ADXL345 Register Map
 */
#define ADXL345_REG_DEVICE_ID       0x00  // Device ID Register
#define ADXL345_REG_THRESH_TAP      0x1D  // Tap Threshold
#define ADXL345_REG_OFFSET_X        0x1E  // X-axis offset
#define ADXL345_REG_OFFSET_Y        0x1F  // Y-axis offset
#define ADXL345_REG_OFFSET_Z        0x20  // Z-axis offset
#define ADXL345_REG_TAP_DURATION    0x21  // Tap Duration
#define ADXL345_REG_TAP_LATENCY     0x22  // Tap latency
#define ADXL345_REG_TAP_WINDOW      0x23  // Tap window
#define ADXL345_REG_THRESH_ACT      0x24  // Activity Threshold
#define ADXL345_REG_THRESH_INACT    0x25  // Inactivity Threshold
#define ADXL345_REG_TIME_INACT      0x26  // Inactivity Time
#define ADXL345_REG_ACT_INACT_CTL   0x27  // Axis enable control for activity and inactivity detection
#define ADXL345_REG_THRESH_FF       0x28  // free-fall threshold
#define ADXL345_REG_TIME_FF         0x29  // Free-Fall Time
#define ADXL345_REG_TAP_AXES        0x2A  // Axis control for tap/double tap
#define ADXL345_REG_ACT_TAP_STATUS  0x2B  // Source of tap/double tap
#define ADXL345_REG_BW_RATE         0x2C  // Data rate and power mode control

#define ADXL345_REG_POWER_CTRL      0x2D  // Power Control Register
  #define ADXL345_WAKE_UP_0   (1 << 0)  // Wake Up Mode - Bit 0
  #define ADXL345_WAKE_UP_1   (1 << 1)  // Wake Up mode - Bit 1
  #define ADXL345_SLEEP       (1 << 2)  // Sleep Mode
  #define ADXL345_MEASURE     (1 << 3)  // Measurement Mode
  #define ADXL345_AUTO_SLEEP  (1 << 4)  // Auto Sleep Mode bit
  #define ADXL345_LINK        (1 << 5)  // Link bit

#define ADXL345_REG_INT_ENABLE      0x2E  // Interrupt Enable Control
#define ADXL345_REG_INT_MAP         0x2F  // Interrupt Mapping Control
#define ADXL345_REG_INT_SOURCE      0x30  // Source of interrupts

#define ADXL345_REG_DATA_FORMAT     0x31  // Data format control
  #define ADXL345_RANGE_2G  0
  #define ADXL345_SCALE_2G  0.0039
  #define ADXL345_RANGE_4G  (1 << 0)
  #define ADXL345_SCALE_4G  0.0078
  #define ADXL345_RANGE_8G  (1 << 1)
  #define ADXL345_SCALE_8G  0.0156
  #define ADXL345_RANGE_16G (1 << 1) | 1
  #define ADXL345_SCALE_16G 0.0312

  #define ADXL345_JUSTIFY   (1 << 2)
  #define ADXL345_FULL_RES  (1 << 3)

#define ADXL345_REG_DATA_X_0        0x32  // X-Axis Data 0
#define ADXL345_REG_DATA_X_1        0x33  // X-Axis Data 1
#define ADXL345_REG_DATA_Y_0        0x34  // Y-Axis Data 0
#define ADXL345_REG_DATA_Y_1        0x35  // Y-Axis Data 1
#define ADXL345_REG_DATA_Z_0        0x36  // Z-Axis Data 0
#define ADXL345_REG_DATA_Z_1        0x37  // Z-Axis Data 1
#define ADXL345_REG_FIFO_CTL        0x38  // FIFO control
#define ADXL345_REG_FIFO_STATUS     0x39  // FIFO status



/**
 *
 */
class ADXL345 {
  public:
    TWI * twi;
    uint8_t address;

    float range;
    float scale;

    float x;
    float y;
    float z;


    ADXL345(TWI * twi_, uint8_t address_ = 0xA6); // A tribute to my beloved colleague Dr. Dangle


    /**
     * Activate measurement mode
     */
    uint8_t enable();


    /**
     * Activate sleep mode
     */
    uint8_t disable();


    /**
     * Set measurment range +/-2,4,8,16g
     */
    uint8_t setRange(uint8_t range);


    /**
     * Update data
     */
    uint8_t update();
};

#endif // _ADXL345_H_
