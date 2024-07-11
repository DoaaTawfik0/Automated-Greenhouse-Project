
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/ERROR_STATE.h"
#include "LDR.h"
#include "../../MCAL/ADC/ADC_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"

ES_t LDR_enuInit(u8 Copy_u8ChanelNumber)
{
	ES_t Local_errorState=ES_NOK;
	if(Copy_u8ChanelNumber >= 0 && Copy_u8ChanelNumber <=7)
	{

		DIO_enuSetPinDirection(DIO_PORTA,Copy_u8ChanelNumber,INPUT);
		ADC_enuInitialize();

		Local_errorState =ES_OK;
	}
	else
	{
		Local_errorState =ES_OUT_OF_RANGE;
	}
	return Local_errorState;
}


ES_t LDR_enuON(u8 Copy_u8Channel_ID , u16 *Copy_pu16ConversionResult)
{
	ES_t Local_errorState=ES_NOK;

	if(Copy_pu16ConversionResult != NULL)
	{
		ADC_enuEnable();
		ADC_enuInitialize();
		ADC_enuDisableTriggeringMode();
		ADC_enuSynchAnalogRead(Copy_u8Channel_ID , Copy_pu16ConversionResult);
		ADC_enuDisable();

		Local_errorState = ES_OK;
	}
	else
	{
		Local_errorState = ES_NULL_POINTER;
	}

	return Local_errorState;
}


ES_t LDR_enuOFF(void)
{
	ES_t Local_errorState=ES_NOK;
	ADC_enuDisable();
	return Local_errorState;
}

