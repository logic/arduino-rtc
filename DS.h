#ifndef __DS_H
#define __DS_H

#include <Wire.h>

// Slave address (commmon to all Dallas Semiconductor/Maxim RTCs)
#define DSRTC_SLAVE_ADDRESS 0x68

// Convert BCD (binary-coded decimal) to decimal, and vice-versa
// Borrowed from Plan9.
#define bcd2dec(bcd) (((((bcd)>>4) & 0x0F) * 10) + ((bcd) & 0x0F))
#define dec2bcd(dec) ((((dec)/10)<<4)|((dec)%10))

class DS {
  public:
    DS() : slaveAddress(DSRTC_SLAVE_ADDRESS) { Wire.begin(); };

    // Raw register read/write methods
    uint8_t readRegister(uint8_t addr);
    void readRegister(uint8_t addr, uint8_t len, uint8_t * buffer);

    void writeRegister(uint8_t addr, uint8_t val);
    void writeRegister(uint8_t addr, uint8_t len, uint8_t * buffer);

  private:
    uint8_t slaveAddress;
};

#endif // __DSRTC_H
