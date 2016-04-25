#include "ADXL345.h"



ADXL345::ADXL345(TWI * twi, uint8_t address) :
    twi(twi), address(address),
    range(ADXL345_RANGE_4G), scale(ADXL345_SCALE_4G)
{}


uint8_t ADXL345::enable() {
  twi->start(address);
  twi->write(ADXL345_REG_POWER_CTRL);
  twi->write(ADXL345_MEASURE);

#ifdef ADXL345_TWI_CHECK_ERROR
  if (twi->error > 0) { return twi->error; }
#endif

  return setRange(range);
}


uint8_t ADXL345::disable() {
  twi->start(address);
  twi->write(ADXL345_REG_POWER_CTRL);
  twi->write(ADXL345_SLEEP);

#ifdef ADXL345_TWI_STOP
  twi->stop();
#endif

  return twi->error;
}


uint8_t ADXL345::setRange(uint8_t range) {
  switch (range) {
    case ADXL345_RANGE_2G:
      scale = ADXL345_SCALE_2G; break;

    case ADXL345_RANGE_4G:
      scale = ADXL345_SCALE_4G; break;

    case ADXL345_RANGE_8G:
      scale = ADXL345_SCALE_8G; break;

    case ADXL345_RANGE_16G:
      scale = ADXL345_SCALE_16G; break;

    default:
      return 10;
  }

  twi->start(address);
  twi->write(ADXL345_REG_DATA_FORMAT);
  twi->write(range);

#ifdef ADXL345_TWI_STOP
  twi->stop();
#endif

  return twi->error;
}


uint8_t ADXL345::update() {
  char valueL;
  char valueH;
  int16_t temp;

  twi->start(address);
  twi->write(ADXL345_REG_DATA_X_0);

#ifdef ADXL345_TWI_CHECK_ERROR
  if (twi->error > 0) { return twi->error; }
#endif

  valueL = twi->read(true);
  valueH = twi->read(true);
  temp = (valueH << 8) | valueL;
  x = (float) temp * scale;

  valueL = twi->read(true);
  valueH = twi->read(true);
  temp = (valueH << 8) | valueL;
  y = (float) temp * scale;

  valueL = twi->read(true);
  valueH = twi->read();
  temp = (valueH << 8) | valueL;
  z = (float) temp * scale;

#ifdef ADXL345_TWI_STOP
  twi->stop();
#endif

  return twi->error;
}
