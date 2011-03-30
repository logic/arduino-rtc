#ifndef __DS3231_H
#define __DS3231_H

#include "utility/DSTemp.h"

class DS3231 : public DSTemp {
  public:
    DS3231() : rtc(DS()) { };
  private:
    DS& rtc;

DS3231 RTC = DS3231();

#endif // __DS3231_H
