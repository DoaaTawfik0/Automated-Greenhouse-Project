/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  HAL           ***************/
/**************   SWC:    LM35          ***************/
/**************   Version: 1.00         ***************/
/******************************************************/
/******************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/ERROR_STATE.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_Interface.h"

#include "../../MCAL/ADC/ADC_Interface.h"


#include "LM35_Private.h"
#include "LM35_Config.h"
#include "LM35_Interface.h"


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : LM35_enuInitialize.                                   **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : void.                                                 **/
/** Functionality   : Initializing Lm35 Sensor (Config of pin)              **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  LM35_enuInitialize(void)
{
	ES_t Local_enuErrorState   = ES_NOK;

	Local_enuErrorState = DIO_enuSetPinDirection(LM35_PORT_ID , LM35_PIN_ID , INPUT);

	return  Local_enuErrorState;
}


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : LM35_enuGetTemperature.                               **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Channel_ID , Copy_pu8TempValue.                **/
/** Functionality   : Getting Temperature of Sensor                         **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  LM35_enuGetTemperature(u8 Copy_u8Channel_ID  , u8* Copy_pu8TempValue)
{
	ES_t Local_enuErrorState = ES_NOK;

	u16 Local_u16Digital_Value , Local_u16Analog_Value;

	ADC_enuEnable();
	ADC_enuInitialize();
	ADC_enuDisableTriggeringMode();
	ADC_enuSynchAnalogRead(Copy_u8Channel_ID , &Local_u16Digital_Value);
	ADC_enuGetAnalogValue(Local_u16Digital_Value , &Local_u16Analog_Value);
	ADC_enuDisable();

	if(Copy_pu8TempValue != NULL)
	{
		*Copy_pu8TempValue = (u8)((Local_u16Analog_Value)/10);

		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}
