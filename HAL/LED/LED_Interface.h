/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  HAL           ***************/
/**************   SWC:    LED           ***************/
/**************   Version: 2.00         ***************/
/******************************************************/
/******************************************************/


#ifndef  LED_INTERFACE_H_
#define  LED_INTERFACE_H_



#include "LED_Config.h"


ES_t  LED_enuInitialize(LED_t *Copy_PStrLEDConfig);


ES_t  LED_enuTurn_LED_ON(LED_t *Copy_PArrLED_ID);

ES_t  LED_enuTurn_LED_OFF(LED_t *Copy_PArrLED_ID);



#endif
