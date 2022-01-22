/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: LCD
 *  Layer arch : ECUAL
 *  Created on: Jan 22, 2022
 *	version:1
 *
 */

#include "../LIBRARY/primitive_data_types.h"
#include "../LIBRARY/BIT_MATH.h"
#include "../MCAL/timers_interface.h"
#include "../MCAL/dio_interface.h"
#include "lcd_interface.h"




void LCD_voidInit(void) 
{
	TIMER0_u8BusyWaitMS(u8_INTIAL_1st_WAITING_TIME_MS)  ;
	DIO_u8SetPinDir(u8_DIO_PORTA,u8_LCD_RS,u8_DIO_OUTPUT_PIN) ; 
	DIO_u8SetPinDir(u8_DIO_PORTA,u8_LCD_RW,u8_DIO_OUTPUT_PIN) ;
	DIO_u8SetPinDir(u8_DIO_PORTA,u8_LCD_E,u8_DIO_OUTPUT_PIN) ;
	DIO_u8SetPinDir(u8_DIO_PORTA,u8_LCD_D4,u8_DIO_OUTPUT_PIN) ;
	DIO_u8SetPinDir(u8_DIO_PORTA,u8_LCD_D5,u8_DIO_OUTPUT_PIN) ;
	DIO_u8SetPinDir(u8_DIO_PORTA,u8_LCD_D6,u8_DIO_OUTPUT_PIN) ;
	DIO_u8SetPinDir(u8_DIO_PORTA,u8_LCD_D7,u8_DIO_OUTPUT_PIN) ;


	//INTIALIZING COMMANDS TO LCD
	LCD_voidsendCommandData(0x3,0,0) ;
	TIMER0_u8BusyWaitMS(10) ;
	LCD_voidsendCommandData(0x3,0,0) ;
	TIMER0_u8BusyWaitMS(10) ;

	LCD_voidsendCommandData(0x3,0,0) ;
	TIMER0_u8BusyWaitMS(10) ;

	LCD_voidsendCommandData(0x2,0,0) ;
	TIMER0_u8BusyWaitMS(10) ;

	LCD_voidsendCommandData(0x20,0,0) ;
	TIMER0_u8BusyWaitMS(10) ;

	LCD_voidsendCommandData(0x08,0,0) ;
	TIMER0_u8BusyWaitMS(10) ;

	LCD_voidsendCommandData(0x01,0,0) ;
	TIMER0_u8BusyWaitMS(10) ;

	LCD_voidsendCommandData(0x06,0,0) ;
	TIMER0_u8BusyWaitMS(10) ;

	LCD_voidsendCommandData(0x0C,0,0) ;
	TIMER0_u8BusyWaitMS(10) ;


	
	
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//CHOOSE TO VALUES OF RS AND RW AND SEND THE COMMAND OR DATA YOU WANT 
void LCD_voidsendCommandData(uint8_t u8_WantedCommand,uint8_t u8_SetRsVal,uint8_t u8_SetRwVal)
{
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_E,u8_DIO_PIN_HIGH) ;
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_RS,u8_SetRsVal) ;
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_RW,u8_SetRwVal) ;
	
	/*SETTING HIGHER SIGNIFICANT BITS */
	TIMER0_u8BusyWaitMS(10) ;
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_D7,GET_BIT(u8_WantedCommand,u8_LCD_D7_BIT));
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_D6,GET_BIT(u8_WantedCommand,u8_LCD_D6_BIT));
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_D5,GET_BIT(u8_WantedCommand,u8_LCD_D5_BIT)) ;
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_D4,GET_BIT(u8_WantedCommand,u8_LCD_D4_BIT)) ;
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_E,u8_DIO_PIN_LOW) ;
	TIMER0_u8BusyWaitMS(10) ;
	
	/*SETTING LOWER SIGNIFICANT BITS */
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_E,u8_DIO_PIN_HIGH) ;
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_D7,GET_BIT(u8_WantedCommand,u8_LCD_D3_BIT));
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_D6,GET_BIT(u8_WantedCommand,u8_LCD_D2_BIT));
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_D5,GET_BIT(u8_WantedCommand,u8_LCD_D1_BIT)) ;
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_D4,GET_BIT(u8_WantedCommand,u8_LCD_D0_BIT)) ;
	TIMER0_u8BusyWaitMS(10) ;
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_LCD_E,u8_DIO_PIN_LOW) ;
	TIMER0_u8BusyWaitMS(10) ;
	
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//PRINT CHAR ON LCD
void LCD_voidPrintChar(uint8_t u8_WantedCharPrint)
{
	LCD_voidsendCommandData(u8_WantedCharPrint,1,0) ; 
}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//PRINT STRING ON LCD 
void LCD_voidPrintStr(uint8_t* u8_WantedStrPrint) 
{
	uint8_t u8_IndexCounter = u8_LCD_INTIALIZING_VAR ; 
	while(u8_WantedStrPrint[u8_IndexCounter]!=NULL_CHAR)
	{
		LCD_voidsendCommandData(u8_WantedStrPrint[u8_IndexCounter],1,0) ; 
		u8_IndexCounter++ ; 
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//PRINT NUMBER TO LCD 
void LCD_voidPrintNum(uint32_t u32_WantedNumPrint) 
{
	uint8_t u8_PrintCounter =  u8_LCD_INTIALIZING_VAR  ;
	uint8_t u8_TempPrintVal = u8_LCD_INTIALIZING_VAR  ; 
	uint32_t u32_CopyNumPrint = u32_WantedNumPrint ; 
	uint32_t u32_u32WeightOfPrnitedNum = u8_INTIALIZING_WEIGHT_VAR ;
	//GET THE WEIGHT OF THE PRINTED NUMBERS AND THE NUBER OF ITERATION NEEDED 
	while(u32_CopyNumPrint>u8_LCD_INTIALIZING_VAR)
	{
		u8_PrintCounter++ ;
		if(u8_PrintCounter>u8_INTIALIZING_WEIGHT_VAR)
			u32_u32WeightOfPrnitedNum*= 10 ;  
		u32_CopyNumPrint = u32_CopyNumPrint/10 ; 
	}
	//PRINT THE WANTED NUMBER FROM THE HIGHER ORDER NUMBERS TO THE LOWER ORDER ONE 
	while(u8_PrintCounter>u8_LCD_INTIALIZING_VAR)
	{
		
		u8_TempPrintVal = u32_WantedNumPrint /u32_u32WeightOfPrnitedNum ; //GET THE HIGHEST ORDER NUMBER TO PRINT 
		u32_WantedNumPrint = u32_WantedNumPrint - (u32_WantedNumPrint/u32_u32WeightOfPrnitedNum)*u32_u32WeightOfPrnitedNum ; //UPDATE THE PRINTED VAR BY DECREMENT THE PRINTED DIGIT
		u32_u32WeightOfPrnitedNum = u32_u32WeightOfPrnitedNum / 10 ; // UPDATE THE WEGHT OG THE VALUE REMAINNING 
		u8_TempPrintVal = u8_TempPrintVal + u8_CONVERT_NUM_TO_ASCII ; // CONVERT VALUE OF THE PRINTED NUMBER TO ASCII
		LCD_voidPrintChar(u8_TempPrintVal) ; //PRINT THE NUMBER 
		u8_PrintCounter-- ; //DECREMENT BY 1 
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//MOVING THE CURSOR TO THE LEFT OR RIGHT BY SENDING COMMAND TO LCD_voidsendCommandData
void LCD_voidMoveCursor(uint8_t u8_WantedDir) 
{
	if(u8_WantedDir==u8_LCD_RIGHT)
	{
		LCD_voidsendCommandData(u8_LCD_RIGHT,0,0) ;
	}
	else 
	{
		LCD_voidsendCommandData(u8_LCD_LEFT,0,0) ;
	}
	TIMER0_u8BusyWaitMS(10) ;

}
