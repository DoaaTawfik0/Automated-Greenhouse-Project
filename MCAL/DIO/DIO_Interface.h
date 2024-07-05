/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  MCAL          ***************/
/**************   SWC:    DIO           ***************/
/**************   Version: 2.00         ***************/
/******************************************************/
/******************************************************/


#ifndef  DIO_INTERFACE_H_
#define  DIO_INTERFACE_H_


#define   DIO_PORTA         1
#define   DIO_PORTB         2
#define   DIO_PORTC         3
#define   DIO_PORTD         4


#define   DIO_PIN0          0
#define   DIO_PIN1          1
#define   DIO_PIN2          2
#define   DIO_PIN3          3
#define   DIO_PIN4          4
#define   DIO_PIN5          5
#define   DIO_PIN6          6
#define   DIO_PIN7          7


#define   OUTPUT            1
#define   INPUT             0


#define   HIGH              1
#define   LOW               0






ES_t  DIO_enuSetPortValue(u8 Copy_u8Port , u8 Copy_u8Value);
ES_t  DIO_enuSetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Value);


ES_t  DIO_enuClearPortValue(u8 Copy_u8Port);

ES_t  DIO_enuTogglePortValue(u8 Copy_u8Port);
ES_t  DIO_enuTogglePinValue(u8 Copy_u8Port , u8 Copy_u8Pin);


ES_t  DIO_enuGetPortValue(u8 Copy_u8Port , u8* Copy_pu8ReturnValue);
ES_t  DIO_enuGetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8* Copy_pu8ReturnValue);

ES_t  DIO_enuSetPinDirection(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Direction);
ES_t  DIO_enuSetPortDirection(u8 Copy_u8Port , u8 Copy_u8Direction);



#endif
