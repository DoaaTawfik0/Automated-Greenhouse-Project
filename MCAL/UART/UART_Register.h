/********************************************************/
/********************************************************/
/**************   Author: Doaa Tawfik     ***************/
/**************   Layer:  MCAL            ***************/
/**************   SWC:    UART            ***************/
/**************   Version: 1.00           ***************/
/********************************************************/
/********************************************************/

#ifndef UART_REGISTER_H_
#define UART_REGISTER_H_

/*****************************************************************************/
/*****************************************************************************/
/**                                                                         **/
/**                     USART I/O Data Register->>UDR                       **/
/**                                                                         **/
/*****************************************************************************/
/*****************************************************************************/

#define     UDR                *((volatile u8*) 0x2C)



/*****************************************************************************/
/*****************************************************************************/
/**                                                                         **/
/**                     USART Control & Status Register A->>UCSRA           **/
/**                                                                         **/
/*****************************************************************************/
/*****************************************************************************/

#define     UCSRA              *((volatile u8*) 0x2B)

#define     UCSRA_RXC          7      //USART Receive Complete
#define     UCSRA_TXC          6      //USART Transmit Complete
#define     UCSRA_UDRE         5      //USART Data Register Empty
#define     UCSRA_FE           4      //Frame Error
#define     UCSRA_DOR          3      //Data OverRun
#define     UCSRA_PE           2      //Parity Error
#define     UCSRA_U2X          1      //Double The USART Transmission Speed
#define     UCSRA_MPCM         0      //Multi-Processor Communication Mode


/*****************************************************************************/
/*****************************************************************************/
/**                                                                         **/
/**                     USART Control & Status Register B->>UCSRC           **/
/**                                                                         **/
/*****************************************************************************/
/*****************************************************************************/

#define     UCSRB              *((volatile u8*) 0x2A)

#define     UCSRB_RXCIE        7      //RX Complete Interrupt Enable
#define     UCSRB_TXCIE        6      //TX Complete Interrupt Enable
#define     UCSRB_UDRIE        5      //USART Data Register Empty Interrupt Enable
#define     UCSRB_RXEN         4      //Receiver Enable
#define     UCSRB_TXEN         3      //Transmitter Enable
#define     UCSRB_UCSZ2        2      //Character Size
#define     UCSRB_RXB8         1      //Receive Data bit 8
#define     UCSRB_TXB8         0      //Transmit Data bit 8


/*****************************************************************************/
/*****************************************************************************/
/**                                                                         **/
/**                     USART Control & Status Register C->>UCSRC                     **/
/**                                                                         **/
/*****************************************************************************/
/*****************************************************************************/

#define     UCSRC             *((volatile u8*) 0x40)

#define     UCSRC_URSEL        7      //Register Select
#define     UCSRC_UMSEL        6      //USART Mode Select
#define     UCSRC_UPM1         5      //Parity Mode
#define     UCSRC_UPM0         4      //Parity Mode
#define     UCSRC_USBS         3      //Stop Bit Select
#define     UCSRC_UCSZ1        2      //Character Size
#define     UCSRC_UCSZ0        1      //Character Size
#define     UCSRC_UCPOL        0      //Clock Polarity



/***************************** ************************************************/
/***************************** ************************************************/
/**                                                                          **/
/**                     USART  Baud Rate Registers->>UBRRL &UBRRH            **/
/**                                                                          **/
/***************************** ************************************************/
/***************************** ************************************************/

#define     UBRRL              *((volatile u8*) 0x29)
#define     UBRRH              *((volatile u8*) 0x40)

#endif
