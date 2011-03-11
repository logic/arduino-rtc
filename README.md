arduino-RTC
===========

An Arduino library for communicating with real-time clock devices.

This library attempts to provide a user-friendly interface to the features
of the DS I2C real-time clocks, specifically in such a manner than it can
be reused with the [Arduino Time library] [1] ([project page] [2]).

While the suppled example code worked well, it did not provide easy access
to the extended features of the RTC chip (battery-backed RAM, temperature,
alarms, etc).

Today, I'm concentrating on Maxim/Dallas I2C RTCs, as interfacing with
them is similar across the entire IC line. Eventually, I'd like to include
support for their SPI devices, as well as NXP's PCF lineup and TI's BQ
series.

[1]: http://www.arduino.cc/playground/Code/Time
[2]: http://code.google.com/p/arduino-time/
