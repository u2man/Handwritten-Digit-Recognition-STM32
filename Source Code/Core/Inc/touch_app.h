/*
 * touch_app.h
 *
 *  Created on: Apr 1, 2020
 *      Author: Kang Usman
 */

#ifndef INC_TOUCH_APP_H_
#define INC_TOUCH_APP_H_


AI_ALIGNED(4)
static ai_i8 in_data[AI_NETWORK_IN_1_SIZE_BYTES];
AI_ALIGNED(4)
static ai_i8 out_data[AI_NETWORK_OUT_1_SIZE_BYTES];

extern int status;

void LCD_Config(void);
void Draw_Menu(void);
void Read_TouchPanel(void);


#endif /* INC_TOUCH_APP_H_ */
