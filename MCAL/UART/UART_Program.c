/********************************************************/
/********************************************************/
/**************   Author: Doaa Tawfik     ***************/
/**************   Layer:  MCAL            ***************/
/**************   SWC:    UART            ***************/
/**************   Version: 1.00           ***************/
/********************************************************/
/********************************************************/

#include "../../LIB/ERROR_STATE.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../Interrupt.h"

#include "UART_Register.h"
#include "UART_Interface.h"
#include "UART_Config.h"
#include "UART_Private.h"

/*********************************************************************************************************/
/*********************************************************************************************************/
/** Function Name   : USART_enuInitialize.                                                              **/
/** Return Type     : Error_State enum.                                                                 **/
/** Arguments       : void.                                                                             **/
/** Functionality   : Selecting Synchronisation Mode ,  Select Speed for Asynchronous Mode              **/
/**                   Clock Polarity for Synchronous Mode , USART State Mode TX,RX,Both                 **/
/**                   Parity Mode , Stop Bit Number , character size                                    **/
/**                   Setting Value of UBRR                                                             **/
/*********************************************************************************************************/
/*********************************************************************************************************/

ES_t   USART_enuInitialize(void)
{
	ES_t   Local_enuErrorState = ES_NOK;
	u8     Local_u8UCSRCValue = 0;
	u16    Local_u16UBRRValue = 0;

	/*  Select Synchronisation Mode     */
#if   USART_SYNCHRONIZATION_MODE == ASYNCHRONOUS_MODE

	Local_u8UCSRCValue &= ~(1<<UCSRC_UMSEL);//Active ASYNCHRONOUS MODE

	/*  Select Speed Mode     */
#if   USART_SPEED_MODE == NORMAL_SPEED_MODE

	CLEAR_BIT(UCSRA , UCSRA_U2X);//Active Normal Speed Mode

#elif USART_SPEED_MODE == DOUBLE_SPEED_MODE

	SET_BIT(UCSRA , UCSRA_U2X);//Active Double Speed Mode

#else
#error  "Speed Mode Is Incorrect"

#endif

	Local_enuErrorState = ES_OK;

#elif USART_SYNCHRONIZATION_MODE == SYNCHRONOUS_MODE

	Local_u8UCSRCValue |= (1<<UCSRC_UMSEL);//Active SYNCHRONOUS MODE
	CLEAR_BIT(UCSRA , UCSRA_U2X);//Deactive Double Speed Mode

	/*Choose Clock Polarity for Synchronous Mode*/
#if CLOCK_POLARITY  == TX_RISING_RX_FALLING

	Local_u8UCSRCValue &= ~(1<<UCSRC_UCPOL);

#elif  CLOCK_POLARITY  == TX_FALLING_RX_RISING

	Local_u8UCSRCValue |= (1<<UCSRC_UCPOL);

#else
#error  "Clock Polarity Is Incorrect"
#endif

	Local_enuErrorState = ES_OK;

#else
#error  "Synchronization Mode Is Incorrect"

#endif


	/*USART State Mode TX,RX,Both*/
#if  USART_STATE_MODE  == TRANSMITTER

	SET_BIT(UCSRB , UCSRB_TXEN);

#elif   USART_STATE_MODE  == RECEIVER

	SET_BIT(UCSRB , UCSRB_RXEN);

#elif   USART_STATE_MODE == TRANSCIEVER
	SET_BIT(UCSRB , UCSRB_RXEN);
	SET_BIT(UCSRB , UCSRB_TXEN);

#else
#error
#endif


	/*  Select Parity Mode     */
#if   PARITY_MODE  == NO_PARITY

	Local_u8UCSRCValue &= ~(1<<UCSRC_UPM0);
	Local_u8UCSRCValue &= ~(1<<UCSRC_UPM1);
	Local_enuErrorState = ES_OK;

#elif   PARITY_MODE  == EVEN_PARITY

	Local_u8UCSRCValue &= ~(1<<UCSRC_UPM0);
	Local_u8UCSRCValue |= (1<<UCSRC_UPM1);
	Local_enuErrorState = ES_OK;

#elif   PARITY_MODE  == ODD_PARITY

	Local_u8UCSRCValue |= (1<<UCSRC_UPM0);
	Local_u8UCSRCValue |= (1<<UCSRC_UPM1);
	Local_enuErrorState = ES_OK;

#else
#error  "Parity Mode Is Incorrect"
#endif

	/*   Stop Bit Select      */
#if   STOP_BIT_SELECT  == ONE_STOP_BIT

	Local_u8UCSRCValue &= ~(1<<UCSRC_USBS);
	Local_enuErrorState = ES_OK;

#elif   STOP_BIT_SELECT  == TWO_STOP_BIT

	Local_u8UCSRCValue |= (1<<UCSRC_USBS);
	Local_enuErrorState = ES_OK;

#else
#error  "Stop Bit Is Incorrect"
#endif

	/*   Character Size Select      */
#if   CHARACTER_SIZE  == FIVE_BIT_SIZE

	Local_u8UCSRCValue &= ~(1<<UCSRC_UCSZ0);
	Local_u8UCSRCValue &= ~(1<<UCSRC_UCSZ1);
	CLEAR_BIT(UCSRB , UCSRB_UCSZ2);

	Local_enuErrorState = ES_OK;

#elif   CHARACTER_SIZE  == SIX_BIT_SIZE

	Local_u8UCSRCValue |= (1<<UCSRC_UCSZ0);
	Local_u8UCSRCValue &= ~(1<<UCSRC_UCSZ1);
	CLEAR_BIT(UCSRB , UCSRB_UCSZ2);

	Local_enuErrorState = ES_OK;

#elif   CHARACTER_SIZE  == SEVEN_BIT_SIZE

	Local_u8UCSRCValue &= ~(1<<UCSRC_UCSZ0);
	Local_u8UCSRCValue |= (1<<UCSRC_UCSZ1);
	CLEAR_BIT(UCSRB , UCSRB_UCSZ2);

	Local_enuErrorState = ES_OK;

#elif   CHARACTER_SIZE  == EIGHT_BIT_SIZE

	Local_u8UCSRCValue |= (1<<UCSRC_UCSZ0);
	Local_u8UCSRCValue |= (1<<UCSRC_UCSZ1);
	CLEAR_BIT(UCSRB , UCSRB_UCSZ2);

	Local_enuErrorState = ES_OK;

#elif   CHARACTER_SIZE  == NINE_BIT_SIZE

	Local_u8UCSRCValue |= (1<<UCSRC_UCSZ0);
	Local_u8UCSRCValue |= (1<<UCSRC_UCSZ1);
	SET_BIT(UCSRB , UCSRB_UCSZ2);

	Local_enuErrorState = ES_OK;

#else
#error  "Character Size Is Incorrect"
#endif


	Local_u8UCSRCValue |= (1<<UCSRC_URSEL);//Set URSEL bit to choose UCSRC Reg Over UBBRH Reg

	UCSRC = Local_u8UCSRCValue;//Assigning Local Variable UCSRC_VALUE To UCSRC Register

	/*Calculating Value of UBRR USART Baud Rate Register*/
#if   USART_SYNCHRONIZATION_MODE == SYNCHRONOUS_MODE

	Local_u16UBRRValue = SYNCH_BAUD_RATE(BAUD_RATE);

	UBRRL = (u8)Local_u16UBRRValue;//Assigning First 8 bits of Local Variable UBRR_VALUE To UBRRL Register
	UBRRH |= (Local_u16UBRRValue>>8);//Assigning next 4 bits of Local Variable UBRR_VALUE To UBRRH Register

	Local_enuErrorState = ES_OK;
#elif   USART_SYNCHRONIZATION_MODE  == ASYNCHRONOUS_MODE

	Local_u16UBRRValue = ASYNCH_BAUD_RATE(BAUD_RATE);

	UBRRL = (u8)Local_u16UBRRValue;//Assigning First 8 bits of Local Variable UBRR_VALUE To UBRRL Register
	UBRRH |= (Local_u16UBRRValue>>8);//Assigning next 4 bits of Local Variable UBRR_VALUE To UBRRH Register

	Local_enuErrorState = ES_OK;

#else
#error
#endif

	return   Local_enuErrorState;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
/** Function Name   : USART_enuSynchSendChar.                                                           **/
/** Return Type     : Error_State enum.                                                                 **/
/** Arguments       : Copy_u8Data.                                                                      **/
/** Functionality   : Printing Char on Terminal                                                         **/
/*********************************************************************************************************/
/*********************************************************************************************************/

ES_t   USART_enuSynchSendChar(u8  Copy_u8Data)
{
	ES_t   Local_enuErrorState = ES_NOK;

	while(GET_BIT(UCSRA , UCSRA_UDRE) == 0);
	UDR = Copy_u8Data;
	Local_enuErrorState = ES_OK;

	return   Local_enuErrorState;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
/** Function Name   : USART_enuSynchReceiveChar.                                                        **/
/** Return Type     : Error_State enum.                                                                 **/
/** Arguments       : Copy_pu8Data.                                                                     **/
/** Functionality   : Receiving Char From User                                                          **/
/*********************************************************************************************************/
/*********************************************************************************************************/

ES_t   USART_enuSynchReceiveChar(u8*  Copy_pu8Data)
{
	ES_t   Local_enuErrorState = ES_NOK;

	if(Copy_pu8Data != NULL)
	{
		while(GET_BIT(UCSRA , UCSRA_RXC) == 0);
		*Copy_pu8Data = UDR;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return   Local_enuErrorState;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
/** Function Name   : USART_enuSynchSendString.                                                         **/
/** Return Type     : Error_State enum.                                                                 **/
/** Arguments       : Copy_pcData.                                                                      **/
/** Functionality   : Printing String on Terminal                                                       **/
/*********************************************************************************************************/
/*********************************************************************************************************/

ES_t   USART_enuSynchSendString(char*  Copy_pcData)
{
	ES_t   Local_enuErrorState = ES_NOK;
	if(Copy_pcData != NULL)
	{
		while(*Copy_pcData != '\0')
		{
			while(GET_BIT(UCSRA , UCSRA_UDRE) == 0);
			UDR = *Copy_pcData;
			Copy_pcData++;
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return   Local_enuErrorState;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
/** Function Name   : USART_enuSynchReceiveString.                                                      **/
/** Return Type     : Error_State enum.                                                                 **/
/** Arguments       : Copy_pcData.                                                                      **/
/** Functionality   : Receiving String From User                                                        **/
/*********************************************************************************************************/
/*********************************************************************************************************/

ES_t   USART_enuSynchReceiveString(char*  Copy_pcData)
{
	ES_t   Local_enuErrorState = ES_NOK;
	u8     Local_u8Data = 0;
	u8     Local_u8Index = 0;
	if(Copy_pcData != NULL)
	{
		while(1)
		{
			while(GET_BIT(UCSRA , UCSRA_RXC) == 0);
			Local_u8Data = UDR;
			if(Local_u8Data == '\r' || Local_u8Data == '\n')
			{
				Copy_pcData[Local_u8Index] = '\0';
				break;
			}
			Copy_pcData[Local_u8Index] = Local_u8Data;
			Local_u8Index++;
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	return   Local_enuErrorState;
}


