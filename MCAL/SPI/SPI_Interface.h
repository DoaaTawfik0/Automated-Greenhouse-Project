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


typedef enum
{
	SPI_POLLING ,
	SPI_INTERRUPT
}SPI_State_t;



ES_t   SPI_enuMasterInit(SPI_State_t Copy_enuSPI_State);
ES_t   SPI_enuSlaveInit(SPI_State_t  Copy_enuSPI_State);
ES_t   SPI_enuEnable_Peripheral(void);
ES_t   SPI_enuDisable_Peripheral(void);
ES_t   SPI_enuINT_Enable(void);
ES_t   SPI_enuINT_Disable(void);
ES_t   SPI_enuMasterTransmit(SPI_State_t Copy_enuSPI_State , u8 Copy_u8Data);
ES_t   SPI_enuSlaveSyncReceive(SPI_State_t Copy_enuSPI_State , u8* Copy_pu8Data);
ES_t  SPI_enuSlaveASyncReceive(volatile void(*Copy_Pfun_AppFun)(void) , volatile u8* Copy_pu8_AppParameter);



#endif

