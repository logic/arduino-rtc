arduino-RTC
===========

An Arduino library for communicating with real-time clock devices.

This library attempts to provide a user-friendly interface to the features
of the DS I2C real-time clocks, specifically in such a manner than it can
be reused with the Arduino Time library at:

http://www.arduino.cc/playground/Code/Time
http://code.google.com/p/arduino-time/

While the suppled example code worked well, it did not provide easy access
to the extended features of the RTC chip (battery-backed RAM, temperature,
alarms, etc).

Today, I'm concentrating on Maxim/Dallas I2C RTCs, as interfacing with
them is similar across the entire IC line. Eventually, I'd like to include
support for their SPI devices, as well as NXP's PCF lineup and TI's BQ
series as well.

Chip differentiation notes
==========================

There are two major types of RTCs in the DS series: devices that report
the current time as YY-MM-DD/HH:MM:SS, and devices which measure elapsed
time.

Additional features includes watchdogs, EEPROM storage, SRAM, FRAM, alarms,
square-wave output, trickle-charging, microprocessor reset, and power-fail
output.

DS1307
------
http://datasheets.maxim-ic.com/en/ds/DS1307.pdf

Address 0x00, bit 0x80 is the clock-halt (CH) bit. When set to 1, the
oscillator is disabled; when 0, enabled.

Address 0x07 is the control/status byte:
- 0x01 and 0x02 are rate-select (RS0 and RS1):
  - 0, 0: 1Hz
  - 0, 1: 4096Hz
  - 1, 0: 8192Hz
  - 1, 1: 32768Hz
- 0x10 is square-wave enable (SQWE). If 1, the oscillator output is
  enabled, and the frequency output on the SQW/OUT pin is determined
  by RS0 and RS1.
- 0x80 is output control (OUT). When SQWE is disabled, the value of out
  determines the logic level of the SQW/OUT pin (1=high, 0=low).

Address 0x08-0x3F is a battery-backed RAM segment.

DS3231 (and DS3231M)
--------------------
Lots and lots of extra stuff. Will fill in later, but basically:
- two alarms
- detailed control/status bits
- aging offset
- temperature

DS3232
------
Same as DS3231, but with battery-backed RAM segment from 0x14-0xFF.

DS32B35 and DS32C35
-------------------
Same as DS3231, but with serial FRAM at a different slave address.
- DS32B35: 0x0000 to 0x07FF, I2C address 1010xyzd, where x/y/z select
  one of eight blocks of data, and d is the direction (1=read, 0=write)
- DS32C35: 0x0000 to 0x1FFF, I2C address 1010000d, where d is the
  direction.
