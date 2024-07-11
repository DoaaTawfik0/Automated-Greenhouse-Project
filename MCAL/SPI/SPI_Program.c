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



/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_enuMasterInit.                                    **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : States work of spi                                    **/
/** Functionality   : init for SPI                                          **/
/*This function make init for SPI                                           **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
ES_t  SPI_enuMasterInit(SPI_State_t Copy_enuSPI_State)
{
	ES_t  Local_enuErrorState = ES_NOK;

	if(Copy_enuSPI_State == SPI_POLLING)
	{
		/* Set MOSI and SCK output, all others input */
		DIO_enuSetPinDirection(MOSI_PORT , MOSI_PIN , OUTPUT);
		DIO_enuSetPinDirection(SCK_PORT , SCK_PIN , OUTPUT);

		DIO_enuSetPinDirection(MISO_PORT , MISO_PIN , INPUT);
		DIO_enuSetPinDirection(SS_PORT , SS_PIN , INPUT);


		/* Enable SPI, Master, set clock rate fck/16 */
		SPCR = (1<<6)|(1<<4)|(1<<0);

		/* If SS is configured as an input and is
	       driven low while MSTR is set, MSTR will
           be cleared*/
		if (!(GET_BIT(SPCR , 4)))
		{
			// Re-enable Master mode
			SPCR |= (1<<4);
		}

		Local_enuErrorState=ES_OK;

	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}



/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_enuSlaveInit.                                     **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : States work of spi                                    **/
/** Functionality   : init for SPI                                          **/
/*This function make init for Slave SPI                                     **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
ES_t  SPI_enuSlaveInit(SPI_State_t  Copy_enuSPI_State)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_enuSPI_State == SPI_POLLING)
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
/** Functionality   : MasterTransmit for SPI                                **/
/*This function make SPI_MasterTransmit for SPI                             **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
ES_t  SPI_enuMasterTransmit(SPI_State_t Copy_enuSPI_State , u8 Copy_u8Data)
{
	ES_t  Local_enuErrorState = ES_NOK;

	if(Copy_enuSPI_State == SPI_POLLING)
	{
		/* Start transmission */
		SPDR = Copy_u8Data;
		/* Wait for transmission complete */
		while(!(SPSR & (1<<7)));

		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}




/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : SPI_enuSlaveReceive.                                  **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : Copy_pu8Data                                          **/
/** Functionality   : SlaveReceive for SPI                                  **/
/*This function make SlaveReceive for SPI                                   **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
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
}
