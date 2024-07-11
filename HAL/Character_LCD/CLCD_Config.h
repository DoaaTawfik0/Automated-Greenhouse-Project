/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  HAL           ***************/
/**************   SWC:    CLCD          ***************/
/**************   Version: 2.00         ***************/
/******************************************************/
/******************************************************/

#ifndef   CLCD_CONFIG_H_
#define   CLCD_CONFIG_H_



/******************************************************/
/*                    CLCD MODE                       */
/******************************************************/

#define     CLCD_MODE                       FOUR_BIT


/******************************************************/
/*                    Control PINS                    */
/******************************************************/
#define     CLCD_REGISTER_SELECT_PORT       DIO_PORTC
#define     CLCD_REGISTER_SELECT_PIN        DIO_PIN0

#define     CLCD_READ_WRITE_PORT            DIO_PORTC
#define     CLCD_READ_WRITE_PIN             DIO_PIN1

#define     CLCD_ENABLE_PORT                DIO_PORTC
#define     CLCD_ENABLE_PIN                 DIO_PIN2


/******************************************************/
/*                    DATA PINS                       */
/******************************************************/

#define     CLCD_DATA_PORT0                  DIO_PORTA
#define     CLCD_DATA_PIN0                   DIO_PIN3

#define     CLCD_DATA_PORT1                  DIO_PORTA
#define     CLCD_DATA_PIN1                   DIO_PIN4

#define     CLCD_DATA_PORT2                 DIO_PORTA
#define     CLCD_DATA_PIN2                  DIO_PIN5

#define     CLCD_DATA_PORT3                 DIO_PORTA
#define     CLCD_DATA_PIN3                  DIO_PIN6

#define     CLCD_DATA_PORT4                 DIO_PORTC
#define     CLCD_DATA_PIN4                  DIO_PIN3

#define     CLCD_DATA_PORT5                 DIO_PORTC
#define     CLCD_DATA_PIN5                  DIO_PIN4

#define     CLCD_DATA_PORT6                 DIO_PORTC
#define     CLCD_DATA_PIN6                  DIO_PIN5

#define     CLCD_DATA_PORT7                 DIO_PORTC
#define     CLCD_DATA_PIN7                  DIO_PIN6


#endif
