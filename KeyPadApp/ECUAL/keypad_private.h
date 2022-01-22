/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: KEYPAD
 *  Layer arch : ECUAL
 *  Created on: Jan 17, 2022
 *	version: 1
 *
 */
 
#ifndef __KEYPAD__PRIVATE__
#define __KEYPAD__PRIVATE__

#define u8_KEYPAD_PORT											u8_DIO_PORTC
				
#define u8_KEYPAD_ROW1											u8_DIO_PIN2
#define u8_KEYPAD_ROW2                          				u8_DIO_PIN3
#define u8_KEYPAD_ROW3                          				u8_DIO_PIN4
#define u8_KEYPAD_COL1                          				u8_DIO_PIN5
#define u8_KEYPAD_COL2                          				u8_DIO_PIN6
#define u8_KEYPAD_COL3                          				u8_DIO_PIN7
				
#define u8_KEYPAD_PRESSED										u8_DIO_PIN_LOW
#define u8_KEYPAD_NOT_PRESSED									u8_DIO_PIN_HIGH
				
#define u8_KEYPAD_INTIALIZING_VAR								0
#define u8_KEYPAD_DEBOUNCE_SUCCESSIVE_COUNT						4
#define u8_KEYPAD_ALL_KEYS_NOT_PRESSED							0

void KEYPAD_voidDebouncing(uint8_t u8_RowNum,uint8_t* pu8_ReturnButtonState) ;




#endif
