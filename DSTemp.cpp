#include "DSTemp.h"

float DSTemp::getTemperature() {
  int8_t fint = readRegister(tempReg);
  uint8_t ffrac = readRegister(tempReg + 1) >> 6;
  return (float)fint + ((float)ffrac * 0.25);
}
