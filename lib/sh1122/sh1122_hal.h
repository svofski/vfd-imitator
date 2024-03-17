/*
 SH1122 256x64 grayscale driver by Mikhail Tsaryov 
 https://github.com/mikhail-tsaryov/SH1122-STM32-HAL-Driver

 HAL by svofski 2024

*/
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void SH1122_Config(int _pin_cs, int _pin_dc, int _pin_rst);
void SH1122_Reset(void);
void SH1122_SendOneByteCommand(uint8_t cmd);
void SH1122_SendDoubleByteCommand(uint8_t cmd_h, uint8_t cmd_l);
void SH1122_WriteData(uint8_t *pData, uint32_t DataLen);
void SH1122_Delay_Ms(int ms);


#ifdef __cplusplus
}
#endif
