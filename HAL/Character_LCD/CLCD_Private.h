/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  HAL           ***************/
/**************   SWC:    CLCD          ***************/
/**************   Version: 2.00         ***************/
/******************************************************/
/******************************************************/

#ifndef   CLCD_PRIVATE_H_
#define   CLCD_PRIVATE_H_

#define    NULL_CHARACTER               '\0'

#define    EIGHT_BIT                    8
#define    FOUR_BIT                     4

/*Function Set 0b00111000*/
#define    FUNCTION_SET_EIGHT_BIT       0x38

/*Function Set 0b00101000*/
#define    FUNCTION_SET_FOUR_BIT        0x28


/*Display on/off 0b00001100*/
#define    DISPLAY_ON_OFF               0x0c

/*Display Clear  0b00000001*/
#define    DISPLAY_CLEAR                0x01

/*Entry Mode Set  0b00000110*/
#define    ENTRY_MODE_SET               0x06


#endif
