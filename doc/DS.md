Dallas Semiconductor/Maxim chip notes
=====================================

There are two major types of RTCs in the DS series: devices that report
the current time as YY-MM-DD/HH:MM:SS, and devices which measure elapsed
time.

Additional features includes watchdogs, EEPROM storage, SRAM, FRAM, alarms,
square-wave output, trickle-charging, microprocessor reset, and power-fail
output.

[All I2C DS parts](http://para.maxim-ic.com/en/search.mvp?fam=rtc&374=I%3Csup%3E2%3C/sup%3EC&tree=timers)

RTC Chips
---------

Applies to:

- DS1307
- DS1337, DS1337C
- DS1338, DS1338Z
- DS1339, DS1339U
- DS1340, DS1340Z
- DS1341, DS1342
- DS1375
- DS1388 (with caveat)
- DS1678
- DS3231
- DS3231M
- DS3232
- DS32B35, DS32C35

Addresses 0x00 through 0x06 store the current time in BCD format:

0. 7-bit seconds
1. 7-bit minutes
2. 6-bit hour, or 5-bit hour and 1-bit AM/PM, followed by 1-bit 12/24
3. 3-bit day-of-week
4. 6-bit date (day-of-month)
5. 5-bit month, with most-significant-bit as 99/00 century rollover (CENT)
6. 8-bit year

The DS1307, DS1338, DS1340, DS1388, and DS1678 do not support CENT.

These registers shift up one byte on the DS1388; address 0x00 contains
hundredths of seconds in addition to the rest.

All chips have a control/status register (or registers), but the address
differs from chip to chip. Additionally, unused bits from the above (bit 7
in seconds, minuts, hours, day, and date, for example) are used for
additional toggles on some chips.

Elapsed Time Chips
------------------

Applies to:

- DS1371
- DS1372
- DS1374, DS1374U
- DS1672
- DS1678
- DS1682

A variable-location register (0x00 for dedicated elapsed-time chips, higher
for others) contains four (two on DS1678) time-of-day/elapsed-time counter
bytes.

On all except DS1672 and DS1678, a variable-location register (0x04 for
deddicated chips, higher for others) contains three watchdog/alarm counter
bytes.

DS1682 is a black sheep here; it has a four-byte alarm register, a
four-byte elapsed time counter, and a two-byte event counter.

DS1307
------

[Datasheet](http://datasheets.maxim-ic.com/en/ds/DS1307.pdf)

Address 0x00, bit 0x80 is the clock-halt (CH) bit. When set to 1, the
oscillator is disabled; when 0, enabled.

Address 0x07 is the control/status byte:

* bits 0x01 and 0x02 are rate-select (RS0 and RS1):

  * 0, 0: 1Hz
  * 0, 1: 4096Hz
  * 1, 0: 8192Hz
  * 1, 1: 32768Hz

* bit 0x10 is square-wave enable (SQWE). If 1, the oscillator output is
  enabled, and the frequency output on the SQW/OUT pin is determined
  by RS0 and RS1.

* bit 0x80 is output control (OUT). When SQWE is disabled, the value of
  out determines the logic level of the SQW/OUT pin (1=high, 0=low).

Address 0x08-0x3F is a battery-backed RAM segment.

DS3231 (and DS3231M)
--------------------

[DS3231 Datasheet](http://datasheets.maxim-ic.com/en/ds/DS3231.pdf)
[DS3231M Datasheet](http://datasheets.maxim-ic.com/en/ds/DS3231M.pdf)

Lots and lots of extra stuff. Will fill in later, but basically:

* two alarms

* detailed control/status bits

* aging offset

* temperature

DS3232
------

[Datasheet](http://datasheets.maxim-ic.com/en/ds/DS3232.pdf)

Same as DS3231, but with battery-backed RAM segment from 0x14-0xFF.

DS32B35 and DS32C35
-------------------

[Datasheet](http://datasheets.maxim-ic.com/en/ds/DS32B35-DS32C35.pdf)

Same as DS3231, but with serial FRAM at a different slave address.

* DS32B35: 0x0000 to 0x07FF, I2C address 1010xyzd, where x/y/z select
  one of eight blocks of data, and d is the direction (1=read, 0=write)

* DS32C35: 0x0000 to 0x1FFF, I2C address 1010000d, where d is the
  direction.
