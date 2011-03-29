#include "DS3231.h"

float DS3231::temperature()
{
  Wire.beginTransmission(DS3231_SLAVE_ADDRESS);
  Wire.send(DS3231_REG_TEMP);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_SLAVE_ADDRESS, 2);
  return (float)((int8_t)Wire.receive() & 0x7F) +
         ((float)((uint8_t)Wire.receive() >> 6) * 0.25);
}

void DS3231::setSQW(uint16_t hz)
{
  uint16_t ctrl = readControl();

  switch (hz) {
    case 1:
      ctrl &= ~(DS3231_CONTROL_RS1 | DS3231_CONTROL_RS2);
      break;
    case 1024:
      ctrl |= DS3231_CONTROL_RS1;
      ctrl &= ~(DS3231_CONTROL_RS2);
      break;
    case 4096:
      ctrl &= ~(DS3231_CONTROL_RS1);
      ctrl |= DS3231_CONTROL_RS2;
      break;
    case 8192:
      ctrl |= DS3231_CONTROL_RS1 | DS3231_CONTROL_RS2;
      break;
    default:
      return; // Invalid frequency; do nothing.
  }

  // Switch from alarm interrupts to square-wave output.
  ctrl &= ~(DS3231_CONTROL_INTCN);

  writeControl(ctrl);
}

inline void DS3231::setAlarm(alarm_t alarm, time_t t, alarmRate_t rate) {
  tmElements_t tm;
  breakTime(t, tm);

  uint8_t alarmReg = (alarm == alarm1) ? DS3231_REG_ALARM1 : DS3231_REG_ALARM2;
  Wire.beginTransmission(DS3231_SLAVE_ADDRESS);
  Wire.send(alarmReg);
  Wire.send(dec2bcd(tm.Second));
  Wire.send(dec2bcd(tm.Minute));
  Wire.send(dec2bcd(tm.Hour));
  //Wire.send(dec2bcd(tm.Wday));
  Wire.send(dec2bcd(tm.Day));
  Wire.send(dec2bcd(tm.Month));
  Wire.send(dec2bcd(tmYearToY2k(tm.Year)));
  Wire.endTransmission();

  // Switch from square-wave output to alarm interrupts,
  // and enable the alarm we just set.
  writeControl(readControl() | DS3231_CONTROL_INTCN |
    (alarm == alarm1 ? DS3231_CONTROL_A1E : DS3231_CONTROL_A2E));
}

uint16_t DS3231::readControl()
{
  Wire.beginTransmission(DS3231_SLAVE_ADDRESS);
  Wire.send(DS3231_REG_CONTROL);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_SLAVE_ADDRESS, 2);
  return (uint16_t)Wire.receive() | ((uint16_t)Wire.receive() << 8);
}

void DS3231::writeControl(uint16_t ctrl)
{
  Wire.beginTransmission(DS3231_SLAVE_ADDRESS);
  Wire.send(DS3231_REG_CONTROL);
  Wire.send((uint8_t)(ctrl & 0xFF));
  Wire.send((uint8_t)(ctrl >> 8));
  Wire.endTransmission();
}

DS3231 RTC = DS3231(); // create an instance for the user
