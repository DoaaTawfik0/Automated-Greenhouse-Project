/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  MCAL          ***************/
/**************   SWC:    ADC           ***************/
/**************   Version: 1.00         ***************/
/******************************************************/
/******************************************************/


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/ERROR_STATE.h"
#include "../../LIB/BIT_MATH.h"

#include "../../LIB/Interrupt.h"

#include "ADC_Interface.h"
#include "ADC_Confih.h"
#include "ADC_Private.h"
#include "ADC_Register.h"


volatile static void (* ADC_pfunISRFun)(void*) = NULL;
volatile static void * ADC_pvidISRParameter = NULL;

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuInitialize.                                    **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : void.                                                 **/
/** Functionality   : Setting Pre_Scaler , Voltage_Ref & Adjustment for ADC **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuInitialize(void)
{
	ES_t  Local_enuErrorState = ES_NOK;


	/*Choose ADC Pre_Scaler*/
#if ADC_PRESCALER == PRESCALER_2

	CLEAR_BIT(ADCSRA , ADCSRA_PS0);
	CLEAR_BIT(ADCSRA , ADCSRA_PS1);
	CLEAR_BIT(ADCSRA , ADCSRA_PS2);
	Local_enuErrorState = ES_OK;

#elif ADC_PRESCALER == PRESCALER_4

	CLEAR_BIT(ADCSRA , ADCSRA_PS0);
	SET_BIT(ADCSRA , ADCSRA_PS1);
	CLEAR_BIT(ADCSRA , ADCSRA_PS2);
	Local_enuErrorState = ES_OK;

#elif ADC_PRESCALER == PRESCALER_8

	SET_BIT(ADCSRA , ADCSRA_PS0);
	SET_BIT(ADCSRA , ADCSRA_PS1);
	CLEAR_BIT(ADCSRA , ADCSRA_PS2);
	Local_enuErrorState = ES_OK;

#elif ADC_PRESCALER == PRESCALER_16

	CLEAR_BIT(ADCSRA , ADCSRA_PS0);
	CLEAR_BIT(ADCSRA , ADCSRA_PS1);
	SET_BIT(ADCSRA , ADCSRA_PS2);
	Local_enuErrorState = ES_OK;

#elif ADC_PRESCALER == PRESCALER_32

	SET_BIT(ADCSRA , ADCSRA_PS0);
	CLEAR_BIT(ADCSRA , ADCSRA_PS1);
	SET_BIT(ADCSRA , ADCSRA_PS2);
	Local_enuErrorState = ES_OK;

#elif ADC_PRESCALER == PRESCALER_64

	CLEAR_BIT(ADCSRA , ADCSRA_PS0);
	SET_BIT(ADCSRA , ADCSRA_PS1);
	SET_BIT(ADCSRA , ADCSRA_PS2);
	Local_enuErrorState = ES_OK;

#elif ADC_PRESCALER == PRESCALER_128

	SET_BIT(ADCSRA , ADCSRA_PS0);
	SET_BIT(ADCSRA , ADCSRA_PS1);
	SET_BIT(ADCSRA , ADCSRA_PS2);
	Local_enuErrorState = ES_OK;

#else
#error   "ADC Pre_Scaler is Wrong"

#endif

	/*Choose ADC Voltage Reference*/
#if ADC_VOLTAGE_REF == AREF_VOLTAGE

	CLEAR_BIT(ADMUX , ADMUX_REFS0);
	CLEAR_BIT(ADMUX , ADMUX_REFS1);
	Local_enuErrorState = ES_OK;

#elif ADC_VOLTAGE_REF == AVCC_VOLTAGE

	SET_BIT(ADMUX , ADMUX_REFS0);
	CLEAR_BIT(ADMUX , ADMUX_REFS1);
	Local_enuErrorState = ES_OK;

#elif ADC_VOLTAGE_REF == INTERNAL_VOLTAGE

	SET_BIT(ADMUX , ADMUX_REFS0);
	SET_BIT(ADMUX , ADMUX_REFS1);
	Local_enuErrorState = ES_OK;

#else
#error  "ADC Voltage Reference is Wrong"

#endif

	/*Choose ADC Adjustment*/
#if ADC_ADJUSTMENT == RIGHT_ADJUST

	CLEAR_BIT(ADMUX , ADMUX_ADLAR);
	Local_enuErrorState = ES_OK;

#elif ADC_ADJUSTMENT == LEFT_ADJUST

	SET_BIT(ADMUX , ADMUX_ADLAR);
	Local_enuErrorState = ES_OK;

#else
#error  "ADC Adjustment is Wrong"

#endif

	return  Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuStartConversion.                               **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : void.                                                 **/
/** Functionality   : Start ADC Conversion                                  **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuStartConversion(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	SET_BIT(ADCSRA , ADCSRA_ADSC);//start conversion by setting ADSC bit with 1
	Local_enuErrorState = ES_OK;

	return   Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuPollingSystem.                                 **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : void.                                                 **/
/** Functionality   : Use Polling System                                    **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuPollingSystem(void)
{
	ES_t Local_enuErrorState = ES_NOK;


	while(GET_BIT(ADCSRA , ADCSRA_ADIF) == 0);//wait on flag
	CLEAR_BIT(ADCSRA , ADCSRA_ADIF);//Clear Flag BY Sstting bit to 1
	Local_enuErrorState = ES_OK;

	return   Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuReadHighValue.                                 **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_pu8Value.                                        **/
/** Functionality   : Reading High Value AKA  Highest 8 bits from 2 to 9    **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuReadHighValue(u8* Copy_pu8Value)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pu8Value != NULL)
	{
		if(ADC_ADJUSTMENT == LEFT_ADJUST)
		{
			*Copy_pu8Value = ADCH;
		}
		else if(ADC_ADJUSTMENT == RIGHT_ADJUST)
		{
			*Copy_pu8Value = (ADCL >> 2);
			*Copy_pu8Value |= (ADCH << 6);
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return   Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuReadData.                                      **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_pu16Value.                                       **/
/** Functionality   : Reading All Ten Bits from 0 to 9                      **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuReadData(u16* Copy_pu16Value)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pu16Value != NULL)
	{
		if(ADC_ADJUSTMENT == LEFT_ADJUST)
		{
			*Copy_pu16Value  = (ADCL >> 6);
			*Copy_pu16Value |= (ADCH << 2);
		}
		else if(ADC_ADJUSTMENT == RIGHT_ADJUST)
		{
			*Copy_pu16Value = ADCL;
			*Copy_pu16Value |= ((u16)ADCH << 8);
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return   Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuCallBack.                                      **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_pfunAppFun , Copy_pvidAppParameter.              **/
/** Functionality   : Call Back Fun To call App Function                    **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuCallBack(volatile void(*Copy_pfunAppFun)(void*) , void* Copy_pvidAppParameter)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pfunAppFun != NULL)
	{
		ADC_pfunISRFun = Copy_pfunAppFun;
		ADC_pvidISRParameter = Copy_pvidAppParameter;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return   Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuSelectChannel.                                 **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8ChannelID                                      **/
/** Functionality   : Selecting Channel for ADC                             **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuSelectChannel(u8 Copy_u8ChannelID)
{
	ES_t Local_enuErrorState = ES_NOK;

	ADMUX &= ~0x1f;//clearing first 5 bits

	if(Copy_u8ChannelID >= 0 && Copy_u8ChannelID < 32)
	{
		ADMUX |= Copy_u8ChannelID;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return   Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuEnableTriggeringMode.                          **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8TriggeringSource                               **/
/** Functionality   : Select & Enable Triggering Mode                       **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuEnableTriggeringMode(u8 Copy_u8TriggeringSource)
{
	ES_t Local_enuErrorState = ES_NOK;

	CLEAR_BIT(ADCSRA , ADCSRA_ADATE);//close Triggering Source Before choosing channel

	switch(ADC_TRIGGER_SOURCE)
	{

	case FREE_RUNNING_MODE:

		CLEAR_BIT(SFIOR , SFIOR_ADTS0);
		CLEAR_BIT(SFIOR , SFIOR_ADTS1);
		CLEAR_BIT(SFIOR , SFIOR_ADTS2);
		Local_enuErrorState = ES_OK;


		break;
	case ANALOG_COMPARATOR:

		SET_BIT(SFIOR , SFIOR_ADTS0);
		CLEAR_BIT(SFIOR , SFIOR_ADTS1);
		CLEAR_BIT(SFIOR , SFIOR_ADTS2);
		Local_enuErrorState = ES_OK;

		break;
	case EXTERNAL_INTERRUPT_REQUEST_0:

		CLEAR_BIT(SFIOR , SFIOR_ADTS0);
		SET_BIT(SFIOR , SFIOR_ADTS1);
		CLEAR_BIT(SFIOR , SFIOR_ADTS2);
		Local_enuErrorState = ES_OK;

		break;
	case TIMER_COUNTER0_COMPARE_MATCH:

		SET_BIT(SFIOR , SFIOR_ADTS0);
		SET_BIT(SFIOR , SFIOR_ADTS1);
		CLEAR_BIT(SFIOR , SFIOR_ADTS2);
		Local_enuErrorState = ES_OK;

		break;
	case TIMER_COUNTER0_OVERFLOW:

		CLEAR_BIT(SFIOR , SFIOR_ADTS0);
		CLEAR_BIT(SFIOR , SFIOR_ADTS1);
		SET_BIT(SFIOR , SFIOR_ADTS2);
		Local_enuErrorState = ES_OK;

		break;
	case TIMER_COUNTER_COMPARE_MATCH_B:

		SET_BIT(SFIOR , SFIOR_ADTS0);
		CLEAR_BIT(SFIOR , SFIOR_ADTS1);
		SET_BIT(SFIOR , SFIOR_ADTS2);
		Local_enuErrorState = ES_OK;

		break;
	case TIMER_COUNTER1_OVERFLOW:

		CLEAR_BIT(SFIOR , SFIOR_ADTS0);
		SET_BIT(SFIOR , SFIOR_ADTS1);
		SET_BIT(SFIOR , SFIOR_ADTS2);
		Local_enuErrorState = ES_OK;

		break;
	case TIMER_COUNTER1_CAPTURE_EVENT:

		SET_BIT(SFIOR , SFIOR_ADTS0);
		SET_BIT(SFIOR , SFIOR_ADTS1);
		SET_BIT(SFIOR , SFIOR_ADTS2);
		Local_enuErrorState = ES_OK;

		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	SET_BIT(ADCSRA , ADCSRA_ADATE);//Enable Triggering Source after choosing channel

	return   Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuDisableTriggeringMode.                         **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : void                                                  **/
/** Functionality   : Disable Triggering Mode                               **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuDisableTriggeringMode(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	CLEAR_BIT(ADCSRA , ADCSRA_ADATE);//disable auto triggering bit
	Local_enuErrorState = ES_OK;

	return   Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuEnable.                                        **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : void                                                  **/
/** Functionality   : Enable ADC                                            **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuEnable(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	SET_BIT(ADCSRA , ADCSRA_ADEN);
	Local_enuErrorState = ES_OK;

	return   Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuDisable.                                       **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : void                                                  **/
/** Functionality   : Disable ADC                                           **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuDisable(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	CLEAR_BIT(ADCSRA , ADCSRA_ADEN);
	Local_enuErrorState = ES_OK;

	return   Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuEnableInterruptMode.                           **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : void                                                  **/
/** Functionality   : Enable Interrupt Mode                                 **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuEnableInterruptMode(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	SET_BIT(ADCSRA , ADCSRA_ADIE); //set ADC Interrupt enable bit to one
	Local_enuErrorState = ES_OK;

	return   Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuDisableInterruptMode.                          **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : void                                                  **/
/** Functionality   : Disable Interrupt Mode                                **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuDisableInterruptMode(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	CLEAR_BIT(ADCSRA , ADCSRA_ADIE); //clear ADC Interrupt enable bit
	Local_enuErrorState = ES_OK;

	return   Local_enuErrorState;
}


/*ISR Fun For ADC*/
ISR(VECT_ADC)
{
	if(ADC_pfunISRFun != NULL)
	{
		ADC_pfunISRFun(ADC_pvidISRParameter);
	}

}
