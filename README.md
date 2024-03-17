# vfd-imitator

Fake ИЛЦ2-12/8Л on a 256x64 OLED.

![8093151710707960434](https://github.com/svofski/vfd-imitator/assets/6445874/32b0bb52-30a0-430e-89ff-854d59f14c36)

Developed on Raspberry Pi Pico with MBED Arduino Framework. It should be very easy to port to any controller or framework. For SH1122 driver abstraction look into [sh1122_hal.h](lib/sh1122/sh1122_hal.h)

SH1122 driver is based on SH1122-STM32-HAL-Driver by Mikhail Tsaryov: https://github.com/mikhail-tsaryov/SH1122-STM32-HAL-Driver/

# Connections

NOTE: this display is power hungry. Powering it from PiPico 3V3 rail 
may render rp2040 unstable. Prefer using external 3.3V LDO from VIN.

```
Display		|		PiPico Pin No. and name
GND		|		GND
VCC		|		VCC 		(3.3V, use separate LDO)
SCL		|		18		PIN_SPI_SCK 
SDA		|		19		PIN_SPI_MOSI
RST		|		6		PIN_RST
DC		|		7		PIN_DC
CS		|		17 		PIN_SPI_SS
```

