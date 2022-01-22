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
#include "../ECUAL/keypad_interface.h"
#include "../ECUAL/lcd_interface.h"

//#include <util/delay.h>

int main()
{
	uint8_t u8_KeyPadRead = 0 ;
    KEYPAD_voidInit() ;
    LCD_voidInit();
	while(1)
	{
		KEYPAD_u8GetKeyNum(&u8_KeyPadRead) ;
		if(u8_KeyPadRead>0 && u8_KeyPadRead<=9)
		{
			LCD_voidPrintNum(u8_KeyPadRead) ;
			LCD_voidMoveCursor(u8_LCD_LEFT) ;
		}
	}
}
