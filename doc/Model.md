Device model overview.

DS
--
    DS(uint8_t slaveAddress=DSRTC_SLAVE_ADDRESS);
    uint8_t registerRead(uint8_t addr);
    void registerRead(uint8_t addr, uint8_t len, uint8_t * buffer);
    void registerWrite(uint8_t addr, uint8_t val);
    void registerWrite(uint8_t addr, uint8_t len, uint8_t * buffer);

Time
----
    Time(uint8_t startAddr=0x00);

    time_t getTime();
    void setTime(time_t t);

    uint8_t getSecond();
    void setSecond(uint8_t s);
    uint8_t getMinute();
    void setMinute(uint8_t m);
    uint8_t getHour();
    void setHour(uint8_t h);
    uint8_t getWeekDay();
    void setWeekDay(uint8_t d);
    uint8_t getDay();
    void setDay(uint8_t d);
    uint8_t getMonth();
    void setMonth(uint8_t d);
    uint16_t getYear();
    void setYear(uint16_t d);

For DS1388, with hundredths-of-seconds reporting:

    uint8_t getHundredthSeconds();
    void setHundredthSeconds(uint8_t s);

Year requires special handling; DS RTCs track year as 0-99, and *some* RTCs
have a century overflow bit (ie. when the current year wraps from 99 to 0,
the bit is set).

We will probably want to track century independently; on RTCs with EEPROM
or SRAM available, we can do this without intervention by reserving storage
for our use. For those without, we can use Arduino EEPROM.

For devices that support century overflow, we increment our tracked
century whenever we see the bit, and reset it to zero at that time. For
devices without, we will need to track the last queried time ourselves.

Rather than time_t, might be more appropriate to represent time in a
more hardware-representative way, and provide convenience functions for
conversion to and from that time. See Alarm below; it is similar, but
just different enough (either day/date, and alarm2 has no seconds) to
cause problems.

Alarm
-----
    Alarm(uint8_t startAddr=0x07);
    time_t alarm(uint8_t alarmNum);

Trickle Charger
---------------
    TrickleCharger();

Elapsed Time
------------

Watchdog
--------

Temperature
-----------
    Temp(uint8_t startReg=0x11);
    int getTemperature();

Provides a celciusToFahrenheit() convenience macro.

NV SRAM
-------
    RAM(uint8_t startAddr, uint8_t len);
    uint8_t& operator[] (uint8_t t);

FRAM/EEPROM
-----------

Per-device classes
------------------

Each inherits a combination of the base classes above, calling the base
class constructor to configure it as appropriate for the specific device.
User instantiates the class for the chip they actually have; this allows
for special-case variants, like "DS1375WithRAMInsteadOfWatchdog". ;) It
should also give a minimal compile-time footprint for the device.

A pre-allocated instance should be provided to the user; it is physically
impossible for multiple devices to exist on the same I2C bus (because they
all have the same slave address), so there is no reason for multiple
instances to be created.
