/*****************************************************/
/*****************************************************/
/**************   Author: Doaa Tawfik  ***************/
/**************   Layer: MCAL          ***************/
/**************   SWC: Port            ***************/
/**************   Version: 1.00        ***************/
/*****************************************************/
/*****************************************************/
#ifndef PORT_REGISTER_H_
#define PORT_REGISTER_H_

//PORTA
#define PORTA  *((volatile u8*)(0x3B))
#define DDRA  *((volatile u8*)(0x3A))

//PORTB
#define PORTB  *((volatile u8*)(0x38))
#define DDRB  *((volatile u8*)(0x37))

//PORTC
#define PORTC  *((volatile u8*)(0x35))
#define DDRC  *((volatile u8*)(0x34))

//PORTD
#define PORTD  *((volatile u8*)(0x32))
#define DDRD  *((volatile u8*)(0x31))


#endif
