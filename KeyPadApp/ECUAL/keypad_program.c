/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: KEYPAD
 *  Layer arch : ECUAL
 *  Created on: Jan 17, 2022
 *	version: 1
 *
 */

#include "../LIBRARY/primitive_data_types.h"
#include "../LIBRARY/BIT_MATH.h"
#include "../MCAL/dio_interface.h"
#include "keypad_private.h"
#include "keypad_interface.h"




void KEYPAD_voidInit(void) 
{
	//SETTING ROWS AS OUTPUT PINS
	DIO_u8SetPinDir(u8_KEYPAD_PORT,u8_KEYPAD_ROW1,u8_DIO_OUTPUT_PIN) ; 
	DIO_u8SetPinDir(u8_KEYPAD_PORT,u8_KEYPAD_ROW2,u8_DIO_OUTPUT_PIN) ; 
	DIO_u8SetPinDir(u8_KEYPAD_PORT,u8_KEYPAD_ROW3,u8_DIO_OUTPUT_PIN) ; 
	//SETTING COL PINS AS INPUT PINS
	DIO_u8SetPinDir(u8_KEYPAD_PORT,u8_KEYPAD_COL1,u8_DIO_INPUT_PIN) ; 
	DIO_u8SetPinDir(u8_KEYPAD_PORT,u8_KEYPAD_COL2,u8_DIO_INPUT_PIN) ; 
	DIO_u8SetPinDir(u8_KEYPAD_PORT,u8_KEYPAD_COL3,u8_DIO_INPUT_PIN) ;
	//ENABLE ALL PULL-UP PINS
	DIO_voidEnablePullUps() ;      
	//SETTING INTIAL HIGH VALUE FOR OUTPUT ROW PINS		
	DIO_u8SetPinVal(u8_KEYPAD_PORT,u8_KEYPAD_ROW1,u8_DIO_PIN_HIGH) ; 
	DIO_u8SetPinVal(u8_KEYPAD_PORT,u8_KEYPAD_ROW2,u8_DIO_PIN_HIGH) ; 
	DIO_u8SetPinVal(u8_KEYPAD_PORT,u8_KEYPAD_ROW3,u8_DIO_PIN_HIGH) ;
	//SETTING PULL-UP FOR INPUT PINS
	DIO_u8SetPinVal(u8_KEYPAD_PORT,u8_KEYPAD_COL1,u8_DIO_PIN_HIGH) ; 
	DIO_u8SetPinVal(u8_KEYPAD_PORT,u8_KEYPAD_COL2,u8_DIO_PIN_HIGH) ; 
	DIO_u8SetPinVal(u8_KEYPAD_PORT,u8_KEYPAD_COL3,u8_DIO_PIN_HIGH) ;
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

//FUNCTION KEYPAD_u8GetKeyNum RETURN ERROR STATE AND TAKE POINTER TO RETURN PRESSED KEY NUM IN ASCII OR ASCII OF ZERO IF NO KEY PRESSED 
uint8_t KEYPAD_u8GetKeyNum(uint8_t* pu8_ReturnKeyNum )
{
	uint8_t u8_ErrorFlag = u8_KEYPAD_OK , u8_ColCounter = u8_KEYPAD_COL1,u8_RowCounter = u8_KEYPAD_ROW1,u8_TotalCount = u8_KEYPAD_INTIALIZING_VAR ;
	uint8_t	u8_ButtonState = u8_KEYPAD_NOT_PRESSED; 
	if(pu8_ReturnKeyNum!=NULL_POINTER)
	{	
		//INTIALIZING THE RETURN POINTER
		*pu8_ReturnKeyNum = u8_KEYPAD_ALL_KEYS_NOT_PRESSED ;
		//LOOP TO PASS ON ALL COLUMNS 
		for(u8_RowCounter = u8_KEYPAD_ROW1; u8_RowCounter<=u8_KEYPAD_ROW3;u8_RowCounter++)   
		{
			//SETTING PIN OF ONE COL. TO LOW SO THAT WE CAN CHECK IF ANY KEY PRESSED 
			DIO_u8SetPinVal(u8_KEYPAD_PORT,u8_RowCounter,u8_DIO_PIN_LOW) ; 
			//LOOP TO PASS ON ALL ROWS 
			for (u8_ColCounter = u8_KEYPAD_COL1; u8_ColCounter<=u8_KEYPAD_COL3;u8_ColCounter++)
			{	
				 // CHECK IF THE KEY PRESSED WITHOUT THE BOUNCING EFFECT 
				//TOTAL NUMBER OF BUTTONS WE CHECK SO THAT WHEN THEY ARE ADDED TO INTIAL '0' VALUE, WE CAN RETURN THE BUTTON NUM PRESSED
				u8_TotalCount++ ;
				DIO_u8GetPinVal(u8_KEYPAD_PORT,u8_ColCounter,&u8_ButtonState) ;
				if(u8_ButtonState==u8_KEYPAD_PRESSED)
				{
					 KEYPAD_voidDebouncing(u8_ColCounter,&u8_ButtonState) ;
					 while(DIO_u8GetPinVal(u8_KEYPAD_PORT,u8_ColCounter,&u8_ButtonState)==u8_KEYPAD_PRESSED) ;
					 DIO_u8SetPinVal(u8_KEYPAD_PORT,u8_RowCounter,u8_DIO_PIN_HIGH) ;
					 (*pu8_ReturnKeyNum) = u8_TotalCount ;
				   	 break ;
				}
			}
			// MAKE THE COL HIGH AGAIN SO THAT WE CAN CHECK SAME ROWS WITH DIFFERENT COLs. 
			DIO_u8SetPinVal(u8_KEYPAD_PORT,u8_RowCounter,u8_DIO_PIN_HIGH) ; 

		}
	}
	else 
	{
		//IF THE POINTER IS SEND AS NULL_POINTER, RETURN ERROR STATE 
		 u8_ErrorFlag = u8_KEYPAD_NOK ;
	}
	return u8_ErrorFlag ; 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTION TO TAKE POINTER TO RETURN BUTTON STATE IF PRESSED OR NOT (WITHOUT THE EFFECT OF BOUNCING) AND ROW NUM
void KEYPAD_voidDebouncing(uint8_t u8_ColNum,uint8_t* pu8_ReturnButtonState)
{
	uint8_t u8_DebouncingCountPressed = u8_KEYPAD_INTIALIZING_VAR , u8_DebouncingCountNotPressed = u8_KEYPAD_INTIALIZING_VAR ;
	//CHECK IF THERE IS SAME READING FOR BUTTON SUCCESSIVE NUMBER OF TIMES, RETURN BUTTON STATE USING THE POINTER IN ARGUMENT
	while (u8_DebouncingCountPressed <= u8_KEYPAD_DEBOUNCE_SUCCESSIVE_COUNT && u8_DebouncingCountNotPressed <= u8_KEYPAD_DEBOUNCE_SUCCESSIVE_COUNT)
	{
		DIO_u8GetPinVal(u8_KEYPAD_PORT,u8_ColNum,pu8_ReturnButtonState) ;
		if(pu8_ReturnButtonState==u8_KEYPAD_PRESSED) 
		{
			u8_DebouncingCountPressed++ ; 
			u8_DebouncingCountNotPressed = u8_KEYPAD_INTIALIZING_VAR ;
			*pu8_ReturnButtonState = u8_KEYPAD_PRESSED ; 
		}
		else 
		{
			u8_DebouncingCountNotPressed++ ; 
			u8_DebouncingCountPressed = u8_KEYPAD_INTIALIZING_VAR ;
			*pu8_ReturnButtonState = u8_KEYPAD_NOT_PRESSED ; 
		}
	}
}
