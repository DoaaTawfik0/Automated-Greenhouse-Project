/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  HAL           ***************/
/**************   SWC:    LED           ***************/
/**************   Version: 2.00         ***************/
/******************************************************/
/******************************************************/


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/ERROR_STATE.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_Interface.h"


#include "LED_Config.h"
#include "LED_Private.h"
#include "LED_Interface.h"




/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : LED_enuInitialize.                                    **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_PStrLEDConfig.                                   **/
/** Functionality   : Initializing Leds                                     **/
/*This function take a pointer to struct of type LED_t & we use this        **/
/*pointer to access array elements & set direction of this led......        **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  LED_enuInitialize(LED_t *Copy_PStrLEDConfig)
{
	ES_t Local_enuErrorState   = ES_NOK;

	if(Copy_PStrLEDConfig != NULL)
	{
		u8 Local_u8Iterator;

		for(Local_u8Iterator = 0 ; Local_u8Iterator < LED_NUM ; Local_u8Iterator++)
		{

			if((Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Port_ID >= DIO_PORTA) && ( Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Port_ID <= DIO_PORTD))
			{
				if((Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Pin_ID >= DIO_PIN0) && ( Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Pin_ID <= DIO_PIN7))
				{
					if(Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Pin_Connection == LED_SOURCE)
					{
						Local_enuErrorState  = DIO_enuSetPinDirection(Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Port_ID , Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Pin_ID , OUTPUT);
						Local_enuErrorState |= DIO_enuSetPinValue(Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Port_ID , Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Pin_ID , LOW);
					}
					else if(Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Pin_Connection == LED_SINK)
					{
						Local_enuErrorState  = DIO_enuSetPinDirection(Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Port_ID , Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Pin_ID , OUTPUT);
						Local_enuErrorState |= DIO_enuSetPinValue(Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Port_ID , Copy_PStrLEDConfig[Local_u8Iterator].LED_u8Pin_ID , HIGH);

					}
					else
					{
						Local_enuErrorState = ES_OUT_OF_RANGE;
					}
				}
				else
				{
					Local_enuErrorState = ES_OUT_OF_RANGE;

				}

			}
			else
			{
				Local_enuErrorState = ES_OUT_OF_RANGE;

			}
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return  Local_enuErrorState;
}


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : LED_enuTurn_LED_ON.                                   **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_PArrLED_ID.                                      **/
/** Functionality   : Turn led on                                           **/
/*This function take a pointer to array element(Desired led)                **/
/*& we use it to turn the desired led on(source/sink)                       **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  LED_enuTurn_LED_ON(LED_t *Copy_PArrLED_ID)
{
	ES_t Local_enuErrorState   = ES_NOK;

	if(Copy_PArrLED_ID != NULL)
	{
		if(Copy_PArrLED_ID->LED_u8Pin_Connection == LED_SOURCE)
		{
			Local_enuErrorState = DIO_enuSetPinValue(Copy_PArrLED_ID->LED_u8Port_ID , Copy_PArrLED_ID->LED_u8Pin_ID , HIGH);
		}
		else if(Copy_PArrLED_ID->LED_u8Pin_Connection == LED_SINK)
		{
			Local_enuErrorState = DIO_enuSetPinValue(Copy_PArrLED_ID->LED_u8Port_ID , Copy_PArrLED_ID->LED_u8Pin_ID , LOW);
		}
		else
		{
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return  Local_enuErrorState;
}


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : LED_enuTurn_LED_OFF.                                  **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_PArrLED_ID.                                      **/
/** Functionality   : Turn led off                                          **/
/*This function take a pointer to array element(Desired led)                **/
/*& we use it to turn the desired led off(source/sink)                      **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  LED_enuTurn_LED_OFF(LED_t *Copy_PArrLED_ID)
{
	ES_t Local_enuErrorState   = ES_NOK;

	if(Copy_PArrLED_ID != NULL)
	{
		if(Copy_PArrLED_ID->LED_u8Pin_Connection == LED_SOURCE)
		{
			Local_enuErrorState = DIO_enuSetPinValue(Copy_PArrLED_ID->LED_u8Port_ID , Copy_PArrLED_ID->LED_u8Pin_ID , LOW);
		}
		else if(Copy_PArrLED_ID->LED_u8Pin_Connection == LED_SINK)
		{
			Local_enuErrorState = DIO_enuSetPinValue(Copy_PArrLED_ID->LED_u8Port_ID , Copy_PArrLED_ID->LED_u8Pin_ID , HIGH);
		}
		else
		{
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return  Local_enuErrorState;
}
