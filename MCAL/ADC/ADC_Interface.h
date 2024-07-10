/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  MCAL          ***************/
/**************   SWC:    ADC           ***************/
/**************   Version: 1.2        ***************/
/******************************************************/
/******************************************************/


#ifndef   ADC_INTERFACE_H_
#define   ADC_INTERFACE_H_
typedef enum
{
	channel0=0,
	channel1,
	channel2,
	channel3,
	channel4,
	channel5,
	channel6,
	channel7
}ADC_Channel_t;

typedef struct
{
	ADC_Channel_t Chain_FirstChannel;
	ADC_Channel_t Chain_LastChannel;
	u16 *Chain_ResultArr;


}ADC_Chain_t;


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
ES_t ADC_enuStartChainConversion(ADC_Chain_t *Copy_pstrChain );

//----------------Trigger Modes ------------ //
#define   FREE_RUNNING_MODE                 0
#define   ANALOG_COMPARATOR                 1
#define   EXTERNAL_INTERRUPT_REQUEST_0      2
#define   TIMER_COUNTER0_COMPARE_MATCH      3
#define   TIMER_COUNTER0_OVERFLOW           4
#define   TIMER_COUNTER_COMPARE_MATCH_B     5
#define   TIMER_COUNTER1_OVERFLOW           6
#define   TIMER_COUNTER1_CAPTURE_EVENT      7


#endif
