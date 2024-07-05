/********************************************************/
/********************************************************/
/**************   Author: Doaa Tawfik     ***************/
/**************   Layer:  MCAL            ***************/
/**************   SWC:    UART            ***************/
/**************   Version: 1.00           ***************/
/********************************************************/
/********************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/ERROR_STATE.h"

ES_t   USART_enuInitialize(void);

ES_t   USART_enuSynchSendChar(u8  Copy_u8Data);


ES_t   USART_enuSynchReceiveChar(u8*  Copy_pu8Data);


ES_t   USART_enuSynchSendString(char*  Copy_pcData);

ES_t   USART_enuSynchReceiveString(char*  Copy_pcData);


#endif
