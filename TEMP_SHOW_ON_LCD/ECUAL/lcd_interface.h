/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: LCD
 *  Layer arch : ECUAL
 *  Created on: Jan 22, 2022
 *	version:1
 *
 */

#ifndef __LCD__INTERFACE__
#define __LCD__INTERFACE__


#define u8_INTIAL_1st_WAITING_TIME_MS					50
#define u8_INTIAL_2nd_WAITING_TIME_MS					5




#define u8_LCD_RS										u8_DIO_PIN1
#define u8_LCD_RW										u8_DIO_PIN2
#define u8_LCD_E										u8_DIO_PIN3
#define u8_LCD_D4										u8_DIO_PIN4
#define u8_LCD_D5										u8_DIO_PIN5
#define u8_LCD_D6										u8_DIO_PIN6
#define u8_LCD_D7										u8_DIO_PIN7
	
#define u8_LCD_D0_BIT									0									
#define u8_LCD_D1_BIT									1									
#define u8_LCD_D2_BIT									2									
#define u8_LCD_D3_BIT									3								
#define u8_LCD_D4_BIT									4									
#define u8_LCD_D5_BIT									5									
#define u8_LCD_D6_BIT									6									
#define u8_LCD_D7_BIT									7									

#define u8_LCD_INTIALIZING_VAR 							0
#define u8_CONVERT_NUM_TO_ASCII							'0'
#define u8_INTIALIZING_WEIGHT_VAR						1



#define u8_LCD_1ST_INTIALIZING_COM						0b00110000
#define u8_LCD_2ND_INTIALIZING_COM						0b00110000
#define u8_LCD_LEFT										0x10
#define u8_LCD_RIGHT									0x14



void LCD_voidInit(void) ; 
void LCD_voidsendCommandData(uint8_t u8_WantedCommand,uint8_t u8_SetRsVal,uint8_t u8_SetRwVal) ; 
void LCD_voidPrintChar(uint8_t u8_WantedCharPrint) ;
void LCD_voidPrintStr(uint8_t* u8_WantedStrPrint) ;
void LCD_voidPrintNum(uint32_t u32_WantedNumPrint) ;
void LCD_voidMoveCursor(uint8_t u8_WantedDir)  ;









#endif
