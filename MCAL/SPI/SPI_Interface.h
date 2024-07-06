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

<<<<<<< HEAD

typedef enum
{
	SPI_POLLING ,
	SPI_INTERRUPT
}SPI_State_t;

typedef enum
{
	SPI_MASTER ,
	SPI_SLAVE
}SPI_MS_State_t;

ES_t  SPI_enuMasterInit(SPI_State_t Copy_enuSPI_State);
ES_t  SPI_enuSlaveInit(SPI_State_t  Copy_enuSPI_State);
ES_t  SPI_enuMasterTransmit(SPI_State_t Copy_enuSPI_State , u8 Copy_u8Data);
ES_t  SPI_enuSlaveReceive(SPI_State_t Copy_enuSPI_State , u8* Copy_pu8Data);


#endif

=======
ES_t SPI_MasterInit(void);

ES_t SPI_MasterTransmit(u8 Copy_u8Data);

ES_t SPI_SlaveInit(void);

ES_t SPI_SlaveReceive(u8* Copy_u8Data);

#endif
>>>>>>> a2a4c3c30ff1cee76f31c0b391fda441fb059b0f
