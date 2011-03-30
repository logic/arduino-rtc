#include "DS.h"

uint8_t DSI2C::slaveAddress = DSRTC_SLAVE_ADDRESS;

/**
 * Read the value at the given register address.
 * @param addr the register address to read
 * @return The register value.
 */
uint8_t DSI2C::readRegister(uint8_t addr) {
  Wire.beginTransmission(slaveAddress);
  Wire.send(addr);
  Wire.endTransmission();
  Wire.requestFrom(slaveAddress, (uint8_t)1);
  return Wire.receive();
}

/**
 * Read a series of bytes at a given register address.
 * @param addr the register address to begin reading at
 * @param len the number of bytes to read
 * @param buffer a buffer to read the register values into
 */
void DSI2C::readRegister(uint8_t addr, uint8_t len, uint8_t * buffer) {
  Wire.beginTransmission(slaveAddress);
  Wire.send(addr);
  Wire.endTransmission();
  Wire.requestFrom(slaveAddress, len);
  while (len-- > 0) (*buffer++) = Wire.receive();
}

/**
 * Write a value to a given register address.
 * @param addr the register address to write to
 * @param val the value to write to the given register
 */
void DSI2C::writeRegister(uint8_t addr, uint8_t val) {
  Wire.beginTransmission(slaveAddress);
  Wire.send(addr);
  Wire.send(val);
  Wire.endTransmission();
}

/**
 * Write a series of values to register memory, starting at the given address.
 * @param addr the register address to write to
 * @param len the number of values to write
 * @param buffer a buffer containing the values to write
 */
void DSI2C::writeRegister(uint8_t addr, uint8_t len, uint8_t * buffer) {
  Wire.beginTransmission(slaveAddress);
  Wire.send(addr);
  while (len-- > 0) Wire.send((*buffer++));
  Wire.endTransmission();
}

DSI2C RTCI2C = DSI2C();
