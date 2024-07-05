/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  MCAL          ***************/
/**************   SWC:    DIO           ***************/
/**************   Version: 2.00         ***************/
/******************************************************/
/******************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERROR_STATE.h"

#include "DIO_Interface.h"
#include "DIO_Register.h"
#include "DIO_Private.h"
#include "DIO_Config.h"



/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : DIO_enuSetPortValue.                                  **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Port ,  Copy_u8Value.                          **/
/** Functionality   : Setting Port Value                                    **/
/*This function is responsible for taking port name from user & value to    **/
/*be set on this port (this value must be in the range from 0 to 255)       **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  DIO_enuSetPortValue(u8 Copy_u8Port , u8 Copy_u8Value)
{
	ES_t  Local_enuErrorState  = ES_NOK;

	if((Copy_u8Port >= DIO_u8PORTA) && (Copy_u8Port <= DIO_u8PORTD))
	{

		if((Copy_u8Value >= 0) && (Copy_u8Value <= 255))
		{
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA : PORTA = Copy_u8Value ; break;
			case DIO_u8PORTB : PORTB = Copy_u8Value ; break;
			case DIO_u8PORTC : PORTC = Copy_u8Value ; break;
			case DIO_u8PORTD : PORTD = Copy_u8Value ; break;
			}
		}
		else
		{
			Local_enuErrorState  = ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState  = ES_OUT_OF_RANGE;
	}

	return  Local_enuErrorState;
}


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : DIO_enuSetPinValue.                                   **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Port , Copy_u8Pin , Copy_u8Value.              **/
/** Functionality   : Setting Pin Value                                     **/
/*This function is responsible for taking from user port name , pin Number  **/
/*&Value to be set on this Pin (this value must be 0 or 1)                  **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  DIO_enuSetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Value)
{

	ES_t  Local_enuErrorState  = ES_NOK;

	if((Copy_u8Port >= DIO_u8PORTA) && (Copy_u8Port <= DIO_u8PORTD))
	{

		if((Copy_u8Pin >= DIO_u8PIN0) && (Copy_u8Pin <= DIO_u8PIN7))
		{
			if(Copy_u8Value == DIO_u8HIGH)
			{
				switch(Copy_u8Port)
				{
				case DIO_u8PORTA : SET_BIT(PORTA , Copy_u8Pin) ; break;
				case DIO_u8PORTB : SET_BIT(PORTB , Copy_u8Pin) ; break;
				case DIO_u8PORTC : SET_BIT(PORTC , Copy_u8Pin) ; break;
				case DIO_u8PORTD : SET_BIT(PORTD , Copy_u8Pin) ; break;
				}
				Local_enuErrorState = ES_OK;
			}
			else if(Copy_u8Value == DIO_u8LOW)
			{
				switch(Copy_u8Port)
				{
				case DIO_u8PORTA : CLEAR_BIT(PORTA , Copy_u8Pin) ; break;
				case DIO_u8PORTB : CLEAR_BIT(PORTB , Copy_u8Pin) ; break;
				case DIO_u8PORTC : CLEAR_BIT(PORTC , Copy_u8Pin) ; break;
				case DIO_u8PORTD : CLEAR_BIT(PORTD , Copy_u8Pin) ; break;
				}
				Local_enuErrorState = ES_OK;
			}
			else
			{
				Local_enuErrorState = ES_OUT_OF_RANGE;
			}

		}
		else
		{
			Local_enuErrorState  = ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState  = ES_OUT_OF_RANGE;
	}

	return  Local_enuErrorState;
}


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : DIO_enuClearPortValue.                                **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Port                                           **/
/*This function is responsible for taking port name  from user & Clearing   **/
/*it's Value                                                                **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  DIO_enuClearPortValue(u8 Copy_u8Port)
{
	ES_t  Local_enuErrorState  = ES_NOK;

	if((Copy_u8Port >= DIO_u8PORTA) && (Copy_u8Port <= DIO_u8PORTD))
	{
		switch(Copy_u8Port)
		{
		case DIO_u8PORTA : PORTA = 0x00 ; break;
		case DIO_u8PORTB : PORTB = 0x00 ; break;
		case DIO_u8PORTC : PORTC = 0x00 ; break;
		case DIO_u8PORTD : PORTD = 0x00 ; break;
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState  = ES_OUT_OF_RANGE;
	}

	return  Local_enuErrorState;
}


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : DIO_enuTogglePortValue.                               **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Port                                           **/
/*This function is responsible for taking port name  from user & Toggling   **/
/*it's Value                                                                **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  DIO_enuTogglePortValue(u8 Copy_u8Port)
{

	ES_t  Local_enuErrorState  = ES_NOK;

	if((Copy_u8Port >= DIO_u8PORTA) && (Copy_u8Port <= DIO_u8PORTD))
	{
		switch(Copy_u8Port)
		{
		case DIO_u8PORTA : PORTA = ~(PORTA) ; break;
		case DIO_u8PORTB : PORTB = ~(PORTB) ; break;
		case DIO_u8PORTC : PORTC = ~(PORTC) ; break;
		case DIO_u8PORTD : PORTD = ~(PORTD) ; break;
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState  = ES_OUT_OF_RANGE;
	}

	return  Local_enuErrorState;
}


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : DIO_enuTogglePinValue.                                **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Port , Copy_u8Pin                              **/
/*This function is responsible for taking port name & pin number from user  **/
/*& Toggle Value of this pin                                                **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  DIO_enuTogglePinValue(u8 Copy_u8Port , u8 Copy_u8Pin)
{

	ES_t  Local_enuErrorState  = ES_NOK;

	if((Copy_u8Port >= DIO_u8PORTA) && (Copy_u8Port <= DIO_u8PORTD))
	{

		if((Copy_u8Pin >= DIO_u8PIN0) && (Copy_u8Pin <= DIO_u8PIN7))
		{
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA : TOGGLE_BIT(PORTA , Copy_u8Pin) ; break;
			case DIO_u8PORTB : TOGGLE_BIT(PORTB , Copy_u8Pin) ; break;
			case DIO_u8PORTC : TOGGLE_BIT(PORTC , Copy_u8Pin) ; break;
			case DIO_u8PORTD : TOGGLE_BIT(PORTD , Copy_u8Pin) ; break;
			}
			Local_enuErrorState = ES_OK;
		}
		else
		{
			Local_enuErrorState  = ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState  = ES_OUT_OF_RANGE;
	}

	return  Local_enuErrorState;
}


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : DIO_enuGetPortValue.                                  **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Port , Copy_pu8ReturnValue                     **/
/*This function is responsible for taking port name & Pointer to return     **/
/*value of this port                                                        **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  DIO_enuGetPortValue(u8 Copy_u8Port , u8* Copy_pu8ReturnValue)
{

	ES_t  Local_enuErrorState  = ES_NOK;

	if(Copy_pu8ReturnValue != NULL)
	{

		if((Copy_u8Port >= DIO_u8PORTA) && (Copy_u8Port <= DIO_u8PORTD))
		{

			switch(Copy_u8Port)
			{
			case DIO_u8PORTA : *Copy_pu8ReturnValue = PINA ; break;
			case DIO_u8PORTB : *Copy_pu8ReturnValue = PINB ; break;
			case DIO_u8PORTC : *Copy_pu8ReturnValue = PINC ; break;
			case DIO_u8PORTD : *Copy_pu8ReturnValue = PIND ; break;
			}
			Local_enuErrorState = ES_OK;
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
/** Function Name   : DIO_enuGetPinValue.                                   **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Port ,Copy_u8Pin , Copy_pu8ReturnValue         **/
/*This function is responsible for taking port name ,Pin number & Pointer   **/
/*to return value of specific pin in this port                              **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  DIO_enuGetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8* Copy_pu8ReturnValue)
{

	ES_t  Local_enuErrorState  = ES_NOK;

	if(Copy_pu8ReturnValue != NULL)
	{

		if((Copy_u8Port >= DIO_u8PORTA) && (Copy_u8Port <= DIO_u8PORTD))
		{
			if((Copy_u8Pin >= DIO_u8PIN0) && (Copy_u8Pin <= DIO_u8PIN7))
			{
				switch(Copy_u8Port)
				{
				case DIO_u8PORTA : *Copy_pu8ReturnValue = GET_BIT(PINA , Copy_u8Pin); break;
				case DIO_u8PORTB : *Copy_pu8ReturnValue = GET_BIT(PINB , Copy_u8Pin) ; break;
				case DIO_u8PORTC : *Copy_pu8ReturnValue = GET_BIT(PINC , Copy_u8Pin) ; break;
				case DIO_u8PORTD : *Copy_pu8ReturnValue = GET_BIT(PIND , Copy_u8Pin) ; break;
				}
				Local_enuErrorState = ES_OK;
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
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return  Local_enuErrorState;

}


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : DIO_enuSetPinDirection.                               **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Port ,Copy_u8Pin , Copy_u8Direction.           **/
/** Functionality   : Setting pin Direction (OUTPUT/INPUT)                  **/
/*This function is responsible for taking from user port name & pin name    **/
/*  & Direction  of this pin                                                **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  DIO_enuSetPinDirection(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Direction)
{

	ES_t  Local_enuErrorState  = ES_NOK;

	if((Copy_u8Port >= DIO_u8PORTA) && (Copy_u8Port <= DIO_u8PORTD))
	{

		if((Copy_u8Pin >= DIO_u8PIN0) && (Copy_u8Pin <= DIO_u8PIN7))
		{
			if(Copy_u8Direction == DIO_u8PIN_OUTPUT)
			{
				switch(Copy_u8Port)
				{
				case DIO_u8PORTA : SET_BIT(DDRA  , Copy_u8Pin) ; break;
				case DIO_u8PORTB : SET_BIT(DDRB  , Copy_u8Pin) ; break;
				case DIO_u8PORTC : SET_BIT(DDRC  , Copy_u8Pin) ; break;
				case DIO_u8PORTD : SET_BIT(DDRD , Copy_u8Pin) ; break;
				}
				Local_enuErrorState = ES_OK;
			}
			else if(Copy_u8Direction == DIO_u8PIN_INPUT)
			{
				switch(Copy_u8Port)
				{
				case DIO_u8PORTA : CLEAR_BIT(DDRA  , Copy_u8Pin) ; break;
				case DIO_u8PORTB : CLEAR_BIT(DDRB  , Copy_u8Pin) ; break;
				case DIO_u8PORTC : CLEAR_BIT(DDRC  , Copy_u8Pin) ; break;
				case DIO_u8PORTD : CLEAR_BIT(DDRD , Copy_u8Pin) ; break;
				}
				Local_enuErrorState = ES_OK;
			}
			else
			{
				Local_enuErrorState = ES_OUT_OF_RANGE;
			}

		}
		else
		{
			Local_enuErrorState  = ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState  = ES_OUT_OF_RANGE;
	}

	return  Local_enuErrorState;

}


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : DIO_enuSetPortDirection.                              **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Port ,  Copy_u8Direction.                      **/
/** Functionality   : Setting Port Direction (OUTPUT/INPUT)                 **/
/*This function is responsible for taking port name from user & Direction   **/
/*of this port                                                              **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  DIO_enuSetPortDirection(u8 Copy_u8Port , u8 Copy_u8Direction)
{

	ES_t  Local_enuErrorState  = ES_NOK;

	if((Copy_u8Port >= DIO_u8PORTA) && (Copy_u8Port <= DIO_u8PORTD))
	{

		if(Copy_u8Direction == DIO_u8PORT_OUTPUT)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA : DDRA  = 0xFF ; break;
			case DIO_u8PORTB : DDRB  = 0xFF ; break;
			case DIO_u8PORTC : DDRC  = 0xFF ; break;
			case DIO_u8PORTD : DDRD  = 0xFF ; break;
			}
		}
		else if(Copy_u8Direction == DIO_u8PORT_INPUT)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA : DDRA  = 0x00 ; break;
			case DIO_u8PORTB : DDRB  = 0x00 ; break;
			case DIO_u8PORTC : DDRC  = 0x00 ; break;
			case DIO_u8PORTD : DDRD  = 0x00 ; break;
			}
		}
		else
		{
			Local_enuErrorState  = ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState  = ES_OUT_OF_RANGE;
	}

	return  Local_enuErrorState;

}

