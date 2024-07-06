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

#include "../DIO/DIO_Interface.h"

#include "SPI_Register.h"
#include "SPI_Interface.h"
#include "SPI_Private.h"
#include "SPI_Config.h"


<<<<<<< HEAD

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_enuMasterInit.                                    **/
=======
/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_MasterInit.                                       **/
>>>>>>> a2a4c3c30ff1cee76f31c0b391fda441fb059b0f
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : States work of spi                                    **/
/** Functionality   : init for SPI                                          **/
/*This function make init for SPI                                           **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
<<<<<<< HEAD
ES_t  SPI_enuMasterInit(SPI_State_t Copy_enuSPI_State)
{
	ES_t  Local_enuErrorState = ES_NOK;

	if(Copy_enuSPI_State == SPI_POLLING)
	{
=======

ES_t SPI_MasterInit(SPI_stats spi_stat)
{

	ES_t  Local_enuErrorState  = ES_NOK;

	if(spi_stat==SPI_POLLING)
	{

>>>>>>> a2a4c3c30ff1cee76f31c0b391fda441fb059b0f
		/* Set MOSI and SCK output, all others input */
		DIO_enuSetPinDirection(MOSI_PORT , MOSI_PIN , OUTPUT);
		DIO_enuSetPinDirection(SCK_PORT , SCK_PIN , OUTPUT);

		DIO_enuSetPinDirection(MISO_PORT , MISO_PIN , INPUT);
		DIO_enuSetPinDirection(SS_PORT , SS_PIN , INPUT);


		/* Enable SPI, Master, set clock rate fck/16 */
		SPCR = (1<<6)|(1<<4)|(1<<0);

		/* If SS is configured as an input and is
<<<<<<< HEAD
	       driven low while MSTR is set, MSTR will
=======
		   driven low while MSTR is set, MSTR will
>>>>>>> a2a4c3c30ff1cee76f31c0b391fda441fb059b0f
           be cleared*/
		if (!(GET_BIT(SPCR , 4)))
		{
			// Re-enable Master mode
			SPCR |= (1<<4);
		}

		Local_enuErrorState=ES_OK;

	}
<<<<<<< HEAD
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}



/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_enuSlaveInit.                                     **/
=======

	return Local_enuErrorState;

}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_SlaveInit.                                        **/
>>>>>>> a2a4c3c30ff1cee76f31c0b391fda441fb059b0f
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : States work of spi                                    **/
/** Functionality   : init for SPI                                          **/
/*This function make init for Slave SPI                                     **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
<<<<<<< HEAD
ES_t  SPI_enuSlaveInit(SPI_State_t  Copy_enuSPI_State)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_enuSPI_State == SPI_POLLING)
=======

ES_t SPI_SlaveInit(SPI_stats spi_stat)
{

	ES_t  Local_enuErrorState  = ES_NOK;

	if(spi_stat==SPI_POLLING)
>>>>>>> a2a4c3c30ff1cee76f31c0b391fda441fb059b0f
	{

		/* Set MISO output, all others input */
		DIO_enuSetPinDirection(MISO_PORT , MISO_PIN , OUTPUT);

		DIO_enuSetPinDirection(SCK_PORT , SCK_PIN , INPUT);
		DIO_enuSetPinDirection(MISO_PORT , MISO_PIN , INPUT);
		DIO_enuSetPinDirection(SS_PORT , SS_PIN , INPUT);


		/* Enable SPI */
		SPCR = (1<<6);


		Local_enuErrorState=ES_OK;

	}
<<<<<<< HEAD
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_enuMasterTransmit.                                **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Data , Copy_enuSPI_State                       **/
=======

	return Local_enuErrorState;

}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_MasterTransmit.                                   **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_u8Data                                           **/
>>>>>>> a2a4c3c30ff1cee76f31c0b391fda441fb059b0f
/** Functionality   : MasterTransmit for SPI                                **/
/*This function make SPI_MasterTransmit for SPI                             **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
<<<<<<< HEAD
ES_t  SPI_enuMasterTransmit(SPI_State_t Copy_enuSPI_State , u8 Copy_u8Data)
{
	ES_t  Local_enuErrorState = ES_NOK;

	if(Copy_enuSPI_State == SPI_POLLING)
	{
=======

ES_t SPI_MasterTransmit(SPI_stats spi_stat,u8 Copy_u8Data)
{
	ES_t  Local_enuErrorState  = ES_NOK;

	if(spi_stat==SPI_POLLING){

>>>>>>> a2a4c3c30ff1cee76f31c0b391fda441fb059b0f
		/* Start transmission */
		SPDR = Copy_u8Data;
		/* Wait for transmission complete */
		while(!(SPSR & (1<<7)));
<<<<<<< HEAD

		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}




/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_enuSlaveReceive.                                  **/
=======
	}


	return Local_enuErrorState;


}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_SlaveReceive.                                     **/
>>>>>>> a2a4c3c30ff1cee76f31c0b391fda441fb059b0f
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_pu8Data                                          **/
/** Functionality   : SlaveReceive for SPI                                  **/
/*This function make SlaveReceive for SPI                                   **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
<<<<<<< HEAD
ES_t  SPI_enuSlaveReceive(SPI_State_t Copy_enuSPI_State , u8* Copy_pu8Data)
{
	ES_t  Local_enuErrorState = ES_NOK;

	if(Copy_pu8Data != NULL)
	{

		if(Copy_enuSPI_State == SPI_POLLING)
		{
			/* Wait for reception complete */
			while(!(SPSR & (1<<7)));
			/* Return data register */
			*Copy_pu8Data= SPDR;

			Local_enuErrorState = ES_OK;
		}

	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
=======
ES_t SPI_SlaveReceive(SPI_stats spi_stat,u8* Copy_pu8Data)
{
	ES_t  Local_enuErrorState  = ES_NOK;

	if(spi_stat==SPI_POLLING){

		/* Wait for reception complete */
		while(!(SPSR & (1<<7)));
		/* Return data register */
		*Copy_pu8Data= SPDR;
	}


	return Local_enuErrorState;

>>>>>>> a2a4c3c30ff1cee76f31c0b391fda441fb059b0f
}
