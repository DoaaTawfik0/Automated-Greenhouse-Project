/******************************************************/
/******************************************************/
/**************   Author: mahmoud 3id   ***************/
/**************   Layer:  HAL           ***************/
/**************   SWC:    HIH5030       ***************/
/**************   Version: 1.00         ***************/
/******************************************************/
/******************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/ERROR_STATE.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_Interface.h"

#include "../../MCAL/ADC/ADC_Interface.h"

#include "util/delay.h"

#include "HIH5030_Private.h"
#include "HIH5030_Config.h"
#include "HIH5030_Interface.h"



/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : HIH5030_enuInit.                                      **/
/** Return Type     : ES_t.                                                 **/
/** Arguments       : void.                                                 **/
/** Functionality   : Setup sensor.                                         **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  HIH5030_enuInit(void)
{
	ES_t  Local_enuErrorState = ES_NOK;

	Local_enuErrorState  = DIO_enuSetPinDirection(HUMIDITY_PORT , HUMIDITY_PIN , INPUT);

	//Local_enuErrorState |= ADC_enuInitialize();



	return Local_enuErrorState;
}



/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : HIH5030_enuGet_Hum_Data.                              **/
/** Return Type     : Copy_u8Channel_ID , Copy_pu16RetValue.                **/
/** Arguments       : void.                                                 **/
/** Functionality   : Get humidity Data..                                   **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  HIH5030_enuGet_Hum_Data(u8 Copy_u8Channel_ID , u16* Copy_pu16RetValue)
{
	ES_t  Local_enuErrorState = ES_NOK;

	 ADC_enuEnable();
	 ADC_enuDisableTriggeringMode();
	u16 Local_u16Adc_Val , Local_u16AnalogVolt;

	if(Copy_pu16RetValue != NULL)
	{
		ADC_enuSynchAnalogRead(Copy_u8Channel_ID , &Local_u16Adc_Val);
		Local_u16AnalogVolt = ((Local_u16Adc_Val * 5.0 * 1000) / 1024.0);

		*Copy_pu16RetValue = ((Local_u16AnalogVolt - 756)/31.64) ;

		ADC_enuDisable();
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;

}





