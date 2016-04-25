#include "ITG3200.h"



ITG3200::ITG3200(TWI * twi, uint8_t address) :
    twi(twi), address(address)
{}


uint8_t ITG3200::enable() {
  // Set internal clock to 1kHz with 42Hz LPF and Full Scale to 3 for proper operation
  twi->start(address);
  twi->write(ITG3200_REG_DLPF_FS);
  twi->write(ITG3200_DLPF_FS_SEL_0 | ITG3200_DLPF_FS_SEL_1 | ITG3200_DLPF_CFG_0);
  if (twi->error > 0) { return twi->error; }

  // Set sample rate divider for 100 Hz operation
  // Fsample = Fint / (divider + 1) where Fint is 1kHz
  twi->restart();
  twi->write(ITG3200_REG_SMPLRT_DIV);
  twi->write(9);
  if (twi->error > 0) { return twi->error; }

  // Select X gyro PLL for clock source
  twi->restart();
  twi->write(ITG3200_REG_PWR_MGM);
  twi->write(ITG3200_PWR_MGM_CLK_SEL_0);

#ifdef ITG3200_TWI_STOP
  twi->stop();
#endif

  return twi->error;
}


uint8_t ITG3200::disable() {
  // Select X gyro PLL for clock source
  twi->start(address);
  twi->write(ITG3200_REG_PWR_MGM);
  twi->write(ITG3200_PWR_MGM_SLEEP);

#ifdef ITG3200_TWI_STOP
  twi->stop();
#endif

  return twi->error;
}


uint8_t ITG3200::temperature() {
  char valueH;
  char valueL;
  int16_t temp;

  twi->start(address);
  twi->write(ITG3200_REG_TEMP_OUT_H);

  valueH = twi->read(true);
  valueL = twi->read();
  temp = (valueH << 8) | valueL;
  t = 35 + ((temp + 13200) / 280);

#ifdef ITG3200_TWI_STOP
  twi->stop();
#endif

  return twi->error;
}


uint8_t ITG3200::update() {
  char valueH;
  char valueL;
  int16_t temp;

  twi->start(address);
  twi->write(ITG3200_REG_GYRO_XOUT_H);

  valueH = twi->read(true);
  valueL = twi->read(true);
  temp = (valueH << 8) | valueL;
  x = temp / 14.375;

  valueH = twi->read(true);
  valueL = twi->read(true);
  temp = (valueH << 8) | valueL;
  y = temp / 14.375;

  valueH = twi->read(true);
  valueL = twi->read();
  temp = (valueH << 8) | valueL;
  z = temp / 14.375;

#ifdef ITG3200_TWI_STOP
  twi->stop();
#endif

  return twi->error;
}
