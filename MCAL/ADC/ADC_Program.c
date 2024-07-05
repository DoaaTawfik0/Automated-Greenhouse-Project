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


/********************************************************************/
/*                 ProtoTypes fo Static Functions                   */
/********************************************************************/

static inline ES_t  ADC_enuStartConversion(void);

static inline ES_t  ADC_enuSelectChannel(u8 Copy_u8ChannelID);

static inline ES_t  ADC_enuReadData(u16* Copy_pu16Value);

static inline ES_t  ADC_enuPollingSystem(void);

/********************************************************************/
/*                 End Of Static ProtoTypes                         */
/********************************************************************/



/********************************************************************/
/*                 Global Variables Decleration                     */
/********************************************************************/
volatile static void (* ADC_pfunISRFun)(void*) = NULL;
volatile static void * ADC_pvidISRParameter = NULL;

/********************************************************************/
/*                 End Of Global Variables Decleration              */
/********************************************************************/





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


/*********************************************************************************************************/
/*********************************************************************************************************/
/** Function Name   : ADC_enuAsynchAnalogRead.                                                          **/
/** Return Type     : Error_State enum.                                                                 **/
/** Arguments       : Copy_u8ChannelID , Copy_pfunNotificationFun , Copy_pvoidAppParameter              **/
/** Functionality   : Reading Analog Value With Using Interrupt                                         **/
/*This Function take channel ID to select which Channel We're Working on                                **/
/*This Function take Pointer to Notificatio Function ,This Function Will run @ ISR to Notificate me tha  \
  Conversion is Completed                                                                              **/
/*This Function take Pointer To variable to return Read on It                                          **/
/********************************************************************************************************/
/********************************************************************************************************/

ES_t  ADC_enuAsynchAnalogRead(u8 Copy_u8ChannelID , volatile void(*Copy_pfunNotificationFun)(void*) , void* Copy_pvoidAppParameter)
{
	ES_t  Local_enuErrorState = ES_NOK;

	if(Copy_pfunNotificationFun != NULL)
	{
		/*Selecting ADC Channel*/
		Local_enuErrorState  = ADC_enuSelectChannel(Copy_u8ChannelID);

		/*Assignment Arguments of this Fun To glopal variables to use them in ISR*/
		ADC_pfunISRFun = Copy_pfunNotificationFun;
		ADC_pvidISRParameter = Copy_pvoidAppParameter;

		/*Starting Conversion & This Jop will be Completed When entering ISR*/
		Local_enuErrorState |= ADC_enuStartConversion();

		/*Enable ADC Interrupt*/
		Local_enuErrorState |= ADC_enuEnableADCInterrupt();

		/*Reading ADC Value From ADCL&ADCH*/
		Local_enuErrorState |= ADC_enuReadData((u16*)Copy_pvoidAppParameter);

	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}


/*********************************************************************************************************/
/*********************************************************************************************************/
/** Function Name   : ADC_enuSynchAnalogRead.                                                           **/
/** Return Type     : Error_State enum.                                                                 **/
/** Arguments       : Copy_u8ChannelID , Copy_pu16Value                                                 **/
/** Functionality   : Reading Analog Value With Using Polling                                           **/
/* This Function take channel ID to select which Channel We're Working on                                */
/* This Function take Pointer to u16 variable to return value of ADC On it                               */
/*********************************************************************************************************/
/*********************************************************************************************************/

ES_t ADC_enuSynchAnalogRead(u8 Copy_u8ChannelID , u16* Copy_pu16Value)
{

	ES_t  Local_enuErrorState = ES_NOK;

	if(Copy_pu16Value != NULL)
	{
		/*Selecting ADC Channel*/
		Local_enuErrorState  = ADC_enuSelectChannel(Copy_u8ChannelID);

		/*Starting Conversion & This Jop will be Completed When entering ISR*/
		Local_enuErrorState |= ADC_enuStartConversion();

		/*Disable Interrupt Mode*/
		Local_enuErrorState |= ADC_enuDisableADCInterrupt();

		/*Waiting on ADC Complete Conversion Flag to be Set*/
		Local_enuErrorState |= ADC_enuPollingSystem();

		/*Reading ADC Value From ADCL&ADCH*/
		Local_enuErrorState |= ADC_enuReadData(Copy_pu16Value);
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;

}


/*********************************************************************************************************/
/*********************************************************************************************************/
/** Function Name   : ADC_enuGetAnalogValue.                                                            **/
/** Return Type     : Error_State enum.                                                                 **/
/** Arguments       : Copy_u16DigitalValue , Copy_pu16ReturnValue                                       **/
/** Functionality   : Reading Analog Voltage in mv                                                      **/
/*This Function take digital value which ADC Read & pointer to variable to return analog voltage on it   */
/*********************************************************************************************************/
/*********************************************************************************************************/

ES_t  ADC_enuGetAnalogValue(u16 Copy_u16DigitalValue , u16* Copy_pu16ReturnValue)
{

	ES_t  Local_enuErrorState = ES_NOK;

	if(Copy_pu16ReturnValue != NULL)
	{
		*Copy_pu16ReturnValue = (u16)(((u32)Copy_u16DigitalValue*5000UL)/1024UL);
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;

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
/** Function Name   : ADC_enuEnableADCInterrupt.                            **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : void                                                  **/
/** Functionality   : Enable Interrupt Mode                                 **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuEnableADCInterrupt(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	SET_BIT(ADCSRA , ADCSRA_ADIE); //set ADC Interrupt enable bit to one
	Local_enuErrorState = ES_OK;

	return   Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : ADC_enuDisableADCInterrupt.                           **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : void                                                  **/
/** Functionality   : Disable Interrupt Mode                                **/
/*****************************************************************************/
/*****************************************************************************/

ES_t  ADC_enuDisableADCInterrupt(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	CLEAR_BIT(ADCSRA , ADCSRA_ADIE); //clear ADC Interrupt enable bit
	Local_enuErrorState = ES_OK;

	return   Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/*    Static inline Function helps me to Read Data From ADCL & ADCH                 */
/************************************************************************************/
/************************************************************************************/

static inline ES_t  ADC_enuReadData(u16* Copy_pu16Value)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pu16Value != NULL)
	{
		if(ADC_ADJUSTMENT == LEFT_ADJUST)
		{
			*((u16*)Copy_pu16Value)  = (ADCL >> 6);
			*((u16*)Copy_pu16Value) |= (ADCH << 2);
		}
		else if(ADC_ADJUSTMENT == RIGHT_ADJUST)
		{
			*((u16*)Copy_pu16Value) = ADCL;
			*((u16*)Copy_pu16Value) |= ((u16)ADCH << 8);
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return   Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/*    Static inline Function helps me to Start Conversion                           */
/************************************************************************************/
/************************************************************************************/

static inline ES_t  ADC_enuStartConversion(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	SET_BIT(ADCSRA , ADCSRA_ADSC);//start conversion by setting ADSC bit with 1
	Local_enuErrorState = ES_OK;

	return   Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/*    Static inline Function helps me to Select ADC Channel                         */
/************************************************************************************/
/************************************************************************************/

static inline ES_t  ADC_enuSelectChannel(u8 Copy_u8ChannelID)
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


/************************************************************************************/
/************************************************************************************/
/*    Static inline Function helps me to wait on Flag Until it's  Set               */
/************************************************************************************/
/************************************************************************************/

static inline ES_t  ADC_enuPollingSystem(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	while(GET_BIT(ADCSRA , ADCSRA_ADIF) == 0);//wait on flag
	CLEAR_BIT(ADCSRA , ADCSRA_ADIF);//Clear Flag BY Setting bit to 1
	Local_enuErrorState = ES_OK;

	return   Local_enuErrorState;
}

/************************************************************************************/
/*                                ISR For ADC                                       */
/************************************************************************************/

ISR(VECT_ADC)
{
	if(ADC_pfunISRFun != NULL)
	{
		ADC_pfunISRFun((u16*)ADC_pvidISRParameter);
	}

}
