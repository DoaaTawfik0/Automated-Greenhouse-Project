/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  HAL           ***************/
/**************   SWC:    LED           ***************/
/**************   Version: 2.00         ***************/
/******************************************************/
/******************************************************/


#include  "../../LIB/STD_TYPES.h"
#include  "../../LIB/ERROR_STATE.h"
#include  "../../LIB/BIT_MATH.h"

#include  "../../MCAL/DIO/DIO_Interface.h"

#include  "LED_Config.h"
#include  "LED_Private.h"
#include  "LED_Interface.h"


LED_t LED_AStrConfig[LED_NUM] =
{
		{DIO_PORTD , DIO_PIN6 , LED_SOURCE},
		{DIO_PORTD , DIO_PIN7 , LED_SOURCE},
		{DIO_PORTD , DIO_PIN0 , LED_SOURCE},
		{DIO_PORTD , DIO_PIN1 , LED_SOURCE},
		{DIO_PORTD , DIO_PIN2 , LED_SOURCE}
};

