/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  MCAL          ***************/
/**************   SWC:    ADC           ***************/
/**************   Version: 1.00         ***************/
/******************************************************/
/******************************************************/

#ifndef   ADC_REGISTER_H_
#define   ADC_REGISTER_H_


/*ADC Multiplexer Selection Register -> ADMUX*/

#define      ADMUX              *((volatile u8*) 0x27)

//Bits 0:4 Analog Channel and Gain Selection Bits
#define      ADMUX_MUX0         0
#define      ADMUX_MUX1         1
#define      ADMUX_MUX2         2
#define      ADMUX_MUX3         3
#define      ADMUX_MUX4         4

//Bit 5 ADC Left Adjust Result
#define      ADMUX_ADLAR        5

//Bit 6:7 Reference Selection Bits
#define      ADMUX_REFS0        6
#define      ADMUX_REFS1        7


/*ADC Control & Status Register A -> ADCSRA*/

#define      ADCSRA             *((volatile u8*)0x26)

//Bits 0:2  ADC Pre_scaler Select bits
#define      ADCSRA_PS0         0
#define      ADCSRA_PS1         1
#define      ADCSRA_PS2         2

//Bit 3 ADC interrupt Enable
#define      ADCSRA_ADIE        3

//Bit 4 ADC Interrupt Flag
#define      ADCSRA_ADIF        4

//Bit 5 ADC Auto Trigger Enable
#define      ADCSRA_ADATE       5

//Bit 6 ADC Start Conversion
#define      ADCSRA_ADSC        6

//Bit 7 ADC Enable
#define      ADCSRA_ADEN        7


/*ADC Data Register ADCL&ADCH */

#define      ADCH               *((volatile u8*)0x25)
#define      ADCL               *((volatile u8*)0x24)

/*Special FunctionIO Register SFIOR*/

#define      SFIOR              *((volatile u8*)0x50)

//Bits 5:7 ADC Auto Trigger Source

#define      SFIOR_ADTS0        5
#define      SFIOR_ADTS1        6
#define      SFIOR_ADTS2        7






#endif

