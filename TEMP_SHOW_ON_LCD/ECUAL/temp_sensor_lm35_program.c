/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: LM35 TEMP SENSOR
 *  Layer arch : ECUAL
 *  Created on: Jan 22, 2022
 *	version:1
 *
 */
#include "../LIBRARY/primitive_data_types.h"
#include "../MCAL/adc_interface.h"
#include "../MCAL/dio_interface.h"
#include "temp_sensor_lm35_interface.h"





void LM35_voidInit(void) 
{
	DIO_u8SetPinDir(u8_DIO_PORTA,u8_DIO_PIN0,u8_DIO_INPUT_PIN); // INTIALIZING THE PIN OF SENSOR AS INPUT PIN 
	DIO_u8SetPinVal(u8_DIO_PORTA,u8_DIO_PIN0,u8_DIO_PIN_LOW); // MAKE THE PULL UP OFF 
	ADC_voidInit(); //INTIALIZING ADC 
	ADC_voidStartConversion();//MAKE THE CONVERSION START 
} 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTION THAT TAKE ARGUMENT (POINTER TO UINT8_T) TO RETURN AVERAGE TEMP VALUE OF LAST 4 READS AND RETURN ERROR FLAG IG POINTER = NULL_POINTER
uint8_t LM35_u8GetTempInC(uint8_t* pu8_ReturnAvgTemp) 
{
	static uint8_t su8_Temp1= u8_LM35_INTIALIZE_VAR, su8_Temp2=u8_LM35_INTIALIZE_VAR, su8_NewTemp3 = u8_LM35_INTIALIZE_VAR, su8_Temp4 = u8_LM35_INTIALIZE_VAR; 
	uint8_t u8_AdcIntFlag = u8_LM35_INTIALIZE_VAR, u8_ErrorState = u8_LM35_OK ; 
	uint16_t u16_AdcResult = u8_LM35_INTIALIZE_VAR ;
	if(pu8_ReturnAvgTemp!=NULL_POINTER)
	{
		ADC_u8GetFlagInt(&u8_AdcIntFlag); 
		if(u8_AdcIntFlag==u8_ADC_FLAG_RISE )
		{
			ADC_u8GetResult(&u16_AdcResult) ;
			if(u8_ADC_VREF== u8_ADC_VCC_INTERNAL_REF )
			{
				//CALC. THE NEW TEMP IN CASE OF VCC VREF 
				su8_NewTemp3 = (uint8_t)((uint32_t)(u8_ADC_STEP_SIZE_IN_VCC_UV*(uint32_t)(u16_AdcResult))/(uint32_t)(u16_LM35_CONVERT_UV_TO_MV*u8_LM35_SCALE_FACTOR)) ; 
			}
			else if(u8_ADC_VREF== u8_ADC_2560mV_INTERNAL_REF)
			{
				//CALC. THE NEW TEMP IN CASE OF VCC VREf/2
				su8_NewTemp3 = (uint8_t)((uint32_t)(u8_ADC_STEP_SIZE_IN_HALF_VCC_UV*(uint32_t)(u16_AdcResult))/(uint32_t)(u16_LM35_CONVERT_UV_TO_MV*u8_LM35_SCALE_FACTOR)) ; 
			}
			u8_ErrorState = u8_LM35_NEW_TEMP_OK ; 
		}
		//update 3 temp readings to the current reading if this is the first read 
		if(su8_Temp2==0)
		{
			su8_Temp2 = su8_NewTemp3 ; 
		}
		if(su8_Temp1==0)
		{
			su8_Temp1 = su8_Temp2 ; 
		}
		if(su8_Temp4==0)
		{
			su8_Temp4 = su8_Temp1;
		}
		//put the average of last 4 readings in the pointer that return the value 
		*pu8_ReturnAvgTemp = (su8_Temp1 + su8_Temp2 + su8_Temp4 + su8_NewTemp3) / u8_LM35_NUM_OF_READINGS ; 
		//update remaning 3 temp readings 
		su8_Temp4 = su8_Temp1 ; 
		su8_Temp1 = su8_Temp2 ;
		su8_Temp2 = su8_NewTemp3; 
	}
	else //return error state if the pointer = NULL_POINTER
	{
		u8_ErrorState = u8_LM35_NOK ;
	}
	return u8_ErrorState ; 
}
