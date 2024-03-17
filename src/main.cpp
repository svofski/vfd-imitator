#include <Arduino.h>
#include <SPI.h>
#include <ilc2128l.h>

/* 
SH1122 7pin SPI 256x64 grayscale OLED connections for Pi Pico

NOTE: this display is power hungry. Powering it from PiPico 3V3 rail 
may render rp2040 unstable. Prefer using external 3.3V LDO from VIN.

Display		|		PiPico Pin No. and name
	GND		|		GND
	VCC		|		VCC 	(3.3V, use separate LDO)
	SCL		|		18		PIN_SPI_SCK 
	SDA		|		19		PIN_SPI_MOSI
	RST		|		6		PIN_RST
	DC		|		7		PIN_DC
	CS		|		17 		PIN_SPI_SS
*/

#define PIN_DC 7
#define PIN_RST 6

// declare ILC2-12/8L instance on hardware SPI1
ILC2128L ilc(PIN_SPI_SS, PIN_DC, PIN_RST);

int nframe = 0;

void setup()
{
	ilc.begin();
}

void loop()
{
	static char sbuf[13];
	sprintf(sbuf, " %-8d 00", nframe);
	int dotpos = (nframe / 60) % 12;
	for (int i = 0; i < 12; ++i) {
		ilc.set_digit(i, sbuf[i], i == dotpos);
	}
	ilc.refresh();

	++nframe;
}