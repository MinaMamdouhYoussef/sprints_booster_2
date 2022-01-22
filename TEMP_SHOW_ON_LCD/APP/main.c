/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: MAIN
 *  Layer arch : APP
 *  Created on: Jan 22, 2022
 *	version:1
 *
 */
#include "../LIBRARY/primitive_data_types.h"
#include "../MCAL/dio_interface.h"
#include "../MCAL/timers_interface.h"
#include "../ECUAL/lcd_interface.h"
#include "../ECUAL/temp_sensor_lm35_interface.h"
//#include <util/delay.h>

int main()
{
	uint8_t u8_TempSensorDegree = 0 ;
	LCD_voidInit();
	LM35_voidInit() ;
	LCD_voidPrintStr("Temp now is ");
	while(1)
	{
		LM35_u8GetTempInC(&u8_TempSensorDegree)  ;
		LCD_voidPrintNum(u8_TempSensorDegree) ;
		LCD_voidMoveCursor(u8_LCD_LEFT) ;
		LCD_voidMoveCursor(u8_LCD_LEFT) ;
	}
}
