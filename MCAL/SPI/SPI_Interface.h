/******************************************************/
/******************************************************/
/**************   Author: Mahmoud 3id   ***************/
/**************   Layer:  MCAL          ***************/
/**************   SWC:    SPI           ***************/
/**************   Version: 1.00         ***************/
/******************************************************/
/******************************************************/


#ifndef  SPI_INTERFACE_H_
#define  SPI_INTERFACE_H_

ES_t SPI_MasterInit(void);

ES_t SPI_MasterTransmit(u8 Copy_u8Data);

ES_t SPI_SlaveInit(void);

ES_t SPI_SlaveReceive(u8* Copy_u8Data);

#endif