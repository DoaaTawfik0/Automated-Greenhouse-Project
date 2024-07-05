/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  MCAL          ***************/
/**************   SWC:    ADC           ***************/
/**************   Version: 1.00         ***************/
/******************************************************/
/******************************************************/


#ifndef   ADC_INTERFACE_H_
#define   ADC_INTERFACE_H_

ES_t  ADC_enuInitialize(void);
ES_t  ADC_enuStartConversion(void);
ES_t  ADC_enuPollingSystem(void);

ES_t  ADC_enuReadData(u16* Copy_pu16Value);
ES_t  ADC_enuReadHighValue(u8* Copy_pu8Value);

ES_t  ADC_enuCallBack(volatile void(*Copy_pfunAppFun)(void*) , void* Copy_pvidAppParameter);

ES_t  ADC_enuSelectChannel(u8 Copy_u8ChannelID);

ES_t  ADC_enuEnableTriggeringMode(u8 Copy_u8TriggeringSource);
ES_t  ADC_enuDisableTriggeringMode(void);

ES_t  ADC_enuEnable(void);
ES_t  ADC_enuDisable(void);

ES_t  ADC_enuEnableInterruptMode(void);
ES_t  ADC_enuDisableInterruptMode(void);



#define   FREE_RUNNING_MODE                 0
#define   ANALOG_COMPARATOR                 1
#define   EXTERNAL_INTERRUPT_REQUEST_0      2
#define   TIMER_COUNTER0_COMPARE_MATCH      3
#define   TIMER_COUNTER0_OVERFLOW           4
#define   TIMER_COUNTER_COMPARE_MATCH_B     5
#define   TIMER_COUNTER1_OVERFLOW           6
#define   TIMER_COUNTER1_CAPTURE_EVENT      7

#endif
