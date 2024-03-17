/*
 SH1122 256x64 grayscale driver by Mikhail Tsaryov 
 https://github.com/mikhail-tsaryov/SH1122-STM32-HAL-Driver

 Arduino-based HAL by svofski 2024

*/

#include <Arduino.h>
#include <SPI.h>
#include "sh1122_hal.h"

static int pin_cs = 17;
static int pin_dc = 7;
static int pin_rst = 6;

static SPISettings spi_settings(18000000, MSBFIRST, SPI_MODE3);

void SH1122_Config(int _pin_cs, int _pin_dc, int _pin_rst)
{
    pin_cs = _pin_cs;
    pin_dc = _pin_dc;
    pin_rst = _pin_rst;

    pinMode(pin_cs, OUTPUT);
    pinMode(pin_dc, OUTPUT);
    pinMode(pin_rst, OUTPUT);

    SPI.begin();
    SPI.beginTransaction(spi_settings);
}

void SH1122_Reset(void)
{
    digitalWrite(pin_rst, 0);
    delay(10);
    digitalWrite(pin_rst, 1);
    delay(10);
}

void SH1122_SendOneByteCommand(uint8_t cmd)
{
    digitalWrite(pin_cs, 0);    // select oled
    digitalWrite(pin_dc, 0);    // command mode
    SPI.transfer(cmd);
    digitalWrite(pin_cs, 1);    // deselect oled
}

void SH1122_SendDoubleByteCommand(uint8_t cmd_h, uint8_t cmd_l)
{
    digitalWrite(pin_cs, 0);    // select oled
    digitalWrite(pin_dc, 0);    // command mode
    SPI.transfer(cmd_h);
    SPI.transfer(cmd_l);
    digitalWrite(pin_cs, 1);    // deselect oled
}

void SH1122_WriteData(uint8_t *pData, uint32_t DataLen)
{
    digitalWrite(pin_cs, 0);    // select oled
    digitalWrite(pin_dc, 1);    // data mode
    SPI.transfer(pData, DataLen);

    digitalWrite(pin_cs, 1);    // deselect oled
}

void SH1122_Delay_Ms(int ms)
{
    delay(ms);
}