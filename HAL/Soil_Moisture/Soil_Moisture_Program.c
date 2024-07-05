/*******************************************************/
/*******************************************************/
/**************   Author: Doaa Tawfik    ***************/
/**************   Layer:  HAL            ***************/
/**************   SWC:    SOIL_MOISTURE  ***************/
/**************   Version: 1.00          ***************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"

#include "ADC_Interface.h"
#include "Soil_Moisture_Config.h"

#include "Soil_Moisture_Interface.h"
#include "Soil_Moisture_Private.h"



/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SoilMoisture_enuInitialize.                           **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : void.                                                 **/
/** Functionality   : Initializing Soil Moisture Sensor (Config of pin)     **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  SoilMoisture_enuInitialize(void)
{
	ES_t Local_enuErrorState   = ES_NOK;

	Local_enuErrorState = DIO_enuSetPinDirection(SM_PORT_ID , SM_PIN_ID , INPUT);

	return  Local_enuErrorState;
}


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SoilMoisture_enuGetPercentage.                        **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Channel_ID , Copy_pu8RetValue.                 **/
/** Functionality   : Get reading of Soil_Moisture sensor as a percentage   **/
/*              Range should be kept between ADC_DRY & ADC_WET values       **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  SoilMoisture_enuGetPercentage(u8 Copy_u8Channel_ID  , u8* Copy_pu8RetValue)
{
	ES_t Local_enuErrorState = ES_NOK;

	u16 Local_u16Digital_Value;

	if(Copy_pu8RetValue != NULL)
	{
		/*Using ADC Peripheral to read values from Sensor*/
		ADC_enuEnable();
		ADC_enuInitialize();
		ADC_enuDisableTriggeringMode();
		ADC_enuSynchAnalogRead(Copy_u8Channel_ID , &Local_u16Digital_Value);
		ADC_enuDisable();

		/*Calculating Percentage*/
		if(Local_u16Digital_Value < ADC_DRY)
		{
			*Copy_pu8RetValue = 0u;
		}
		else
		{
			*Copy_pu8RetValue = (u8)(((((f32)Local_u16Digital_Value)-ADC_DRY)/(ADC_WET-ADC_DRY))*100);
		}

		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}
