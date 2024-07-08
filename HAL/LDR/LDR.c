/*
 * APP.c
 *
 *  Created on: 8 Jul 2024
 *      Author: Alaraby
 */
#include "../LIBERARY/stdTypes.h"
#include "../LIBERARY/Error_State.h"
#include "APP.h"
#include "../MCAL/ADC_MCAL_int.h"
#include "../MCAL/DIO_int.h"

ES_t LDR_enuInit(u8 Copy_u8ChanelNumber)
{
	ES_t Local_errorState=ES_NOK;
	if(Copy_u8ChanelNumber >= 0 && Copy_u8ChanelNumber <=7)
	{
		DIO_enuInit();
		DIO_enuSet_PinDirection(DIO_u8PORTA,Copy_u8ChanelNumber,DIO_u8INPUT);
		ADC_enuInit();
		ADC_enuEnable();
		ADC_enuSelectChannel(Copy_u8ChanelNumber);

		ADC_enuEnableTriggerMode(ADC_FREE_RUNING);
		Local_errorState =ES_OK;
	}
	else
	{
		Local_errorState =ES_OUT_OF_RANGE;
	}
	return Local_errorState;
}


ES_t LDR_enuON(u16 *Copy_pu16ConversionResult)
{
	ES_t Local_errorState=ES_NOK;
	ADC_enuStartConversion();
	ADC_enuRead(Copy_pu16ConversionResult);
	return Local_errorState;
}


ES_t LDR_enuOFF(void)
{
	ES_t Local_errorState=ES_NOK;
	ADC_enuDisble();
	return Local_errorState;
}

