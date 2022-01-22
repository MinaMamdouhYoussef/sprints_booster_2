/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: KEYPAD
 *  Layer arch : ECUAL
 *  Created on: Jan 17, 2022
 *	version: 1
 *
 */
 
#ifndef __KEYPAD__INTERFACE__
#define __KEYPAD__INTERFACE__

#define u8_KEYPAD_OK				50	
#define u8_KEYPAD_NOK				51


void KEYPAD_voidInit(void) ;
uint8_t KEYPAD_u8GetKeyNum(uint8_t* pu8_ReturnKeyNumInASCII)  ;

#endif
