/********************************************************/
/********************************************************/
/**************   Author: Doaa Tawfik     ***************/
/**************   Layer:  MCAL            ***************/
/**************   SWC:    UART            ***************/
/**************   Version: 1.00           ***************/
/********************************************************/
/********************************************************/


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_



#define       NORMAL_SPEED_MODE           2
#define       DOUBLE_SPEED_MODE           1


#define       ASYNCHRONOUS_MODE           2
#define       SYNCHRONOUS_MODE            3

#define       NO_PARITY                   5
#define       ODD_PARITY                  6
#define       EVEN_PARITY                 7

#define       ONE_STOP_BIT                1
#define       TWO_STOP_BIT                2

#define       FIVE_BIT_SIZE               5
#define       SIX_BIT_SIZE                6
#define       SEVEN_BIT_SIZE              7
#define       EIGHT_BIT_SIZE              8
#define       NINE_BIT_SIZE               9

#define       TX_RISING_RX_FALLING        11
#define       TX_FALLING_RX_RISING        22

#define       TRANSMITTER                 50
#define       RECEIVER                    40
#define       TRANSCIEVER                 30

#define      ASYNCH_BAUD_RATE(BAUD_RATE)              ((F_CPU/(USART_SPEED_MODE*8*BAUD_RATE))-1)
#define      SYNCH_BAUD_RATE(BAUD_RATE)               ((F_CPU/(2*BAUD_RATE))-1)




#endif
