/*
 * touch_app.c
 *
 *  Created on: Apr 1, 2020
 *      Author: Kang Usman
 */

#include "global.h"

static uint32_t radius = 5;
float Digit_Data[28*28];
int ai_status;
float predictionval[10];
class_name_index[10];
const uint8_t* digit_label[]={"0","1","2","3","4","5","6","7","8","9"};


void Read_Image(void);
void Convert_To_AIIn_Data(void);
void Display_AI_Output(void);
static void Bubblesort(void);

void Read_TouchPanel(void){
  static uint32_t x = 0, y = 0;
  static TS_StateTypeDef  TS_State;
  uint8_t bfr[32];

  /* Get Touch screen position */
  BSP_TS_GetState(&TS_State);

  //Return if not touched
  if(!TS_State.TouchDetected)
	  return;

  /* Read the coordinate */
  x = Calibration_GetX(TS_State.X);
  y = Calibration_GetX(TS_State.Y);
  BSP_LCD_SetFont(&Font12);
  sprintf((char*)bfr,"%lu,%lu      ",x,y);
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
  BSP_LCD_DisplayStringAt(3, 300, (uint8_t*)bfr, LEFT_MODE);
  BSP_LCD_SetFont(&Font16);
  //Draw in the box
  if (( x > ((BSP_LCD_GetXSize()/2)-(WINDOWS_WITH/2)+1 + radius)) & (y > 46+radius) & ( x < (BSP_LCD_GetXSize()-((BSP_LCD_GetXSize()/2)-(WINDOWS_WITH/2)-1  + radius )) ) & ( y < 45+WINDOWS_HEIGHT-radius))
   {
	 BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
     BSP_LCD_FillCircle((x), (y), 4);
     //BSP_LED_On(LED3);
     BSP_LED_Off(LED4);
   }

  //Read Clear Bu Button
  if((x>177) && (x < 200) && (y>187)&&(y<210)){
	  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	  BSP_LCD_FillCircle((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1,WINDOWS_HEIGHT+65, 15);

	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	  BSP_LCD_DrawCircle((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1,WINDOWS_HEIGHT+65, 15);
	  BSP_LCD_DisplayStringAt((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1-10,WINDOWS_HEIGHT+60,(uint8_t*)"CL",LEFT_MODE);

	  HAL_Delay(100);
	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	  BSP_LCD_FillCircle((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1,WINDOWS_HEIGHT+65, 15);
	  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	  BSP_LCD_DisplayStringAt((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1-10,WINDOWS_HEIGHT+60,(uint8_t*)"CL",LEFT_MODE);

	  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	  BSP_LCD_FillRect((BSP_LCD_GetXSize()/2)-(WINDOWS_WITH/2)-1, 45, WINDOWS_WITH+2, WINDOWS_HEIGHT+2);

	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	  BSP_LCD_DrawRect((BSP_LCD_GetXSize()/2)-(WINDOWS_WITH/2)-1, 45, WINDOWS_WITH+2, WINDOWS_HEIGHT+2);

  }

  //Read OK Button
  if((x>144) && (x < 169) && (y>187)&&(y<210)){
	  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	  BSP_LCD_FillCircle((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1-35,WINDOWS_HEIGHT+65, 15);

	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	  BSP_LCD_DrawCircle((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1-35,WINDOWS_HEIGHT+65, 15);
	  BSP_LCD_DisplayStringAt((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1-45,WINDOWS_HEIGHT+60,(uint8_t*)"OK",LEFT_MODE);

	  HAL_Delay(100);
	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	  BSP_LCD_FillCircle((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1-35,WINDOWS_HEIGHT+65, 15);
	  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	  BSP_LCD_DisplayStringAt((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1-45,WINDOWS_HEIGHT+60,(uint8_t*)"OK",LEFT_MODE);

	  Read_Image();
	  Convert_To_AIIn_Data();
	  ai_status  = aiRun(in_data, out_data);
	  Display_AI_Output();
  }


}

void Read_Image(void){
	uint16_t xpos, ypos;
	uint16_t xsrc, ysrc,x;
	uint32_t tmp;
	float tmpflt;



	x=0;
	//	BSP_LCD_DrawRect((BSP_LCD_GetXSize()/2)-(WINDOWS_WITH/2)-1, 45, WINDOWS_WITH+2, WINDOWS_HEIGHT+2);
	for(ysrc=45+1;ysrc<45+1+WINDOWS_HEIGHT;ysrc+=5){
		for(xsrc=49+1;xsrc<49+1+WINDOWS_WITH;xsrc+=5){
			for(ypos=0;ypos<5;ypos++){
				for(xpos=0;xpos<5;xpos++){
					tmp = BSP_LCD_ReadPixel(xsrc+xpos, ysrc+ypos) & 0xFF;
				}
			}
			tmpflt = tmp/255;
			Digit_Data[x++]=tmpflt;
		}
	}
}

void Convert_To_AIIn_Data(void){
	uint16_t i,x,j;

	x=0;
	for(i=0;i<784;i++){
		uint8_t* bfr=(uint8_t*)(void*)&Digit_Data[i];
	   	for(j=0;j<4;j++){
	   		//x++;
	   		in_data[x++]=bfr[j];
	   	}
	}
}

void Display_AI_Output(void){
	uint32_t u32dummy;
	uint16_t i,j,x=0;
	float dummyfloat;
	uint8_t lcdbfr[128];

	BSP_LCD_SetFont(&Font20);

	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);

	  if(!ai_status){
		  BSP_LCD_DisplayStringAt(2, 80+WINDOWS_HEIGHT, (uint8_t*)"PREDICTION:",LEFT_MODE);

			for(i=0;i<10;i++){
				uint8_t* p = (uint8_t*)(void*)&dummyfloat;
				u32dummy = (uint8_t)out_data[x+3];
				u32dummy = (u32dummy << 8)|(uint8_t)out_data[x+2];
				u32dummy = (u32dummy << 8)|(uint8_t)out_data[x+1];
				u32dummy = (u32dummy << 8)|(uint8_t)out_data[x];
				x+=4;
				for(j=0;j<4;j++){
					p[j]=u32dummy >> (8*j);
				}
		       predictionval[i]=dummyfloat*100;

			}

			Bubblesort();
			x=80+WINDOWS_HEIGHT+15;
			//for(i=9;i>=7;i--){
				sprintf((char*)lcdbfr,"DIGIT %s (%.2f%%)  ",digit_label[class_name_index[9]],predictionval[9]);
				BSP_LCD_DisplayStringAt(2, x, (uint8_t*)lcdbfr,LEFT_MODE);
				//x+=15;
			//}


	  }
	  else{
		  BSP_LCD_DisplayStringAt(2, 50+WINDOWS_HEIGHT, (uint8_t*)"AI ERROR   ",LEFT_MODE);
	  }
}

static void Bubblesort(void){
	int total_count, counter, counter1,swap_rank;
	float swap_var;
	 total_count=10;

	 for(counter=0;counter<10;counter++){
		 class_name_index[counter]= counter;
	 }

	for (counter = 0 ; counter < total_count - 1; counter++){
		for (counter1 = 0 ; counter1 < total_count - counter - 1; counter1++){
			if(predictionval[counter1]>predictionval[ counter1+1]){
				swap_var = predictionval[counter1];
				predictionval[counter1]=predictionval[counter1+1];
				predictionval[counter1+1]=swap_var;

				swap_rank = class_name_index[counter1];
				class_name_index[counter1]=class_name_index[counter1+1];
				class_name_index[counter1+1]=swap_rank;
			}
		}
	}

}


void LCD_Config(void)
{
  /* Initialize the LCD */
  BSP_LCD_Init();

  /* Background Layer Initialization */
  BSP_LCD_LayerDefaultInit(0, LCD_BUFFER);

  /* Set Foreground Layer */
  BSP_LCD_SelectLayer(0);

  /* Enable the LCD */
  BSP_LCD_DisplayOn();

  /* Set the layer window */
  //BSP_LCD_SetLayerWindow(0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);

  /* Clear the LCD Background layer */
  BSP_LCD_SetTransparency(0,255);
  BSP_LCD_Clear(LCD_COLOR_BLUE);
  BSP_LCD_SetFont(&Font16);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_SetFont(&Font12);
}

void Draw_Menu(void)
{
  /* Set background Layer */
  BSP_LCD_SelectLayer(0);

  /* Clear the LCD */

	BSP_LCD_Clear(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	//BSP_LCD_DrawRect((BSP_LCD_GetXSize()/2)-(WINDOWS_WITH/2)-1, 45, WINDOWS_WITH+2, WINDOWS_HEIGHT+2);
	BSP_LCD_DrawRect(49, 45, WINDOWS_WITH+2, WINDOWS_HEIGHT+2);
	/* OK */
	BSP_LCD_FillCircle((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1,WINDOWS_HEIGHT+65, 15);
	/* CL */
	BSP_LCD_FillCircle((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1-35,WINDOWS_HEIGHT+65, 15);

	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1-45,WINDOWS_HEIGHT+60,(uint8_t*)"OK",LEFT_MODE);
	BSP_LCD_DisplayStringAt((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1-10,WINDOWS_HEIGHT+60,(uint8_t*)"CL",LEFT_MODE);
	/* msg */
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_DisplayStringAt(3, 3, (uint8_t*)"Handwritten Recognition", CENTER_MODE);
	BSP_LCD_DisplayStringAt(3, 15, (uint8_t*)"www.karedox.com", CENTER_MODE);

	BSP_LCD_DisplayStringAt((BSP_LCD_GetXSize()/2)-(WINDOWS_WITH/2)-1, 32,(uint8_t*)"Write a number in the box",LEFT_MODE);
	//BSP_LCD_DisplayStringAt((BSP_LCD_GetXSize()/2)+(WINDOWS_WITH/2)-1, 32,(uint8_t*)"Click OK",LEFT_MODE);

}
