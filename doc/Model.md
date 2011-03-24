Device model overview.

DS
--
    DS(uint8_t slaveAddress=DSRTC_SLAVE_ADDRESS);
    uint8_t read(uint8_t addr);
    void read(uint8_t addr, uint8_t len, uint8_t * buffer);
    void write(uint8_t addr, uint8_t val);
    void write(uint8_t addr, uint8_t len, uint8_t * buffer);

Time
----
    Time(uint8_t startAddr=0x00);
    time_t time();
    void setTime(time_t t);

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
