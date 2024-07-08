/*
 * APP.h
 *
 *  Created on: 8 Jul 2024
 *      Author: Alaraby
 */

#ifndef APP_APP_H_
#define APP_APP_H_
ES_t LDR_enuInit(u8 Copy_u8ChanelNumber);
ES_t LDR_enuON(u16 *Copy_pu16ConversionResult);
ES_t LDR_enuOFF(void);


#define ADC_FREE_RUNING              1
#define ADC_ANALOG_COMPARATOR        2
#define ADC_ETERNAL_INTERRUPT_0      3
#define ADC_TIMERT_0_COMPARE_MATCH   4
#define ADC_TIMERT_0_OVERFLOW        5
#define ADC_TIMERT_1_COMPARE_MATCH_B 6
#define ADC_TIMERT_1_OVERFLOW        7
#define ADC_TIMERT_1_CAPTURE_EVENT   8

#endif /* APP_APP_H_ */
