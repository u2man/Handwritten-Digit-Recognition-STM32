/*
 * global.h
 *
 *  Created on: Apr 1, 2020
 *      Author: Kang Usman
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "crc.h"
#include "dma2d.h"
#include "i2c.h"
#include "ltdc.h"
#include "spi.h"
#include "usart.h"

#include "fmc.h"
#include "app_x-cube-ai.h"
#include "ts_calibration.h"
#include "touch_app.h"

#include <stdio.h>

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_sdram.h"
#include "stm32f429i_discovery_ts.h"

#define IMAGE_HEIGHT 320
#define IMAGE_WIDTH  240
#define LCD_BUFFER   0xD0000000

#define WINDOWS_WITH		140
#define WINDOWS_HEIGHT		140

extern TS_StateTypeDef  TS_State;

void Touchscreen_Calibration(void);
uint16_t Calibration_GetX(uint16_t x);



#endif /* INC_GLOBAL_H_ */
