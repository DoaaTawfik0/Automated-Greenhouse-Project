/******************************************************/
/******************************************************/
/**************   Author: Mahmoud 3id   ***************/
/**************   Layer:  MCAL          ***************/
/**************   SWC:    SPI           ***************/
/**************   Version: 1.00         ***************/
/******************************************************/
/******************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERROR_STATE.h"

#include "SPI_Interface.h"
#include "SPI_Register.h"
#include "SPI_Private.h"
#include "SPI_Config.h"


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_MasterInit.                                       **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : States work of spi                                    **/
/** Functionality   : init for SPI                                          **/
/*This function make init for SPI                                           **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t SPI_MasterInit(SPI_stats spi_stat){

 ES_t  Local_enuErrorState  = ES_NOK;

    if(spi_stat==SPI_POLLING){

    	 /* Set MOSI and SCK output, all others input */
         //code
    	 /* Enable SPI, Master, set clock rate fck/16 */
         SPCR = (1<<6)|(1<<4)|(1<<0);

         Local_enuErrorState=ES_OK;

    }

    return Local_enuErrorState;

}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_SlaveInit.                                        **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : States work of spi                                    **/
/** Functionality   : init for SPI                                          **/
/*This function make init for Slave SPI                                     **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t SPI_SlaveInit(SPI_stats spi_stat){
	
	ES_t  Local_enuErrorState  = ES_NOK;

    if(spi_stat==SPI_POLLING){

    	 /* Set MISO output, all others input */
         //code
         /* Enable SPI */
         SPCR = (1<<6);


         Local_enuErrorState=ES_OK;

    }

    return Local_enuErrorState;

}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_MasterTransmit.                                   **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Data                                           **/
/** Functionality   : MasterTransmit for SPI                                **/
/*This function make SPI_MasterTransmit for SPI                             **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t SPI_MasterTransmit(SPI_stats spi_stat,u8 Copy_u8Data){
	ES_t  Local_enuErrorState  = ES_NOK;

	if(spi_stat==SPI_POLLING){

	     /* Start transmission */
        SPDR = Copy_u8Data;
        /* Wait for transmission complete */
        while(!(SPSR & (1<<7)));
    }


	 return Local_enuErrorState;
 

}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_SlaveReceive.                                     **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_pu8Data                                          **/
/** Functionality   : SlaveReceive for SPI                                  **/
/*This function make SlaveReceive for SPI                                   **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
ES_t SPI_SlaveReceive(SPI_stats spi_stat,u8* Copy_pu8Data){
	ES_t  Local_enuErrorState  = ES_NOK;

	if(spi_stat==SPI_POLLING){

	     /* Wait for reception complete */
         while(!(SPSR & (1<<7)));
         /* Return data register */
         *Copy_pu8Data= SPDR;
    }


	 return Local_enuErrorState;

}
