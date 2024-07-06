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


ES_t  ADC_enuAsynchAnalogRead(u8 Copy_u8ChannelID , volatile void(*Copy_pfunNotificationFun)(void*) , void* Copy_pvoidAppParameter);
ES_t  ADC_enuSynchAnalogRead(u8 Copy_u8ChannelID , u16* Copy_pu16Value);

ES_t  ADC_enuGetAnalogValue(u16 Copy_u16DigitalValue , u16* Copy_pu16ReturnValue);

ES_t  ADC_enuEnableTriggeringMode(u8 Copy_u8TriggeringSource);
ES_t  ADC_enuDisableTriggeringMode(void);

ES_t  ADC_enuEnable(void);
ES_t  ADC_enuDisable(void);

ES_t  ADC_enuEnableADCInterrupt(void);
ES_t  ADC_enuDisableADCInterrupt(void);


#endif
