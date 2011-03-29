#ifndef __DSTEMP_H
#define __DSTEMP_H

#include "DS.h"

// Temperatures reported by getTemperature() are in celcius;
// this provides convenient conversion.
#define celciusToFahrenheit(c) (9.0/5.0*(c)+32.0)

class DSTemp : public DS {
  public:
    DSTemp(uint8_t tempReg=0x11) : tempReg(tempReg) { DS(); };
    float getTemperature();
  private:
    uint8_t tempReg;  // Clock and Calendar register location
};

#endif // __DSTEMP_H
