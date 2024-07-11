/*
 * APP.h
 *
 *  Created on: 8 Jul 2024
 *      Author: Alaraby
 */

#ifndef APP_APP_H_
#define APP_APP_H_
ES_t LDR_enuInit(u8 Copy_u8ChanelNumber);
ES_t LDR_enuON(u8 Copy_u8Channel_ID , u16 *Copy_pu16ConversionResult);
ES_t LDR_enuOFF(void);




#endif /* APP_APP_H_ */
