/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  HAL           ***************/
/**************   SWC:    DC_Motor      ***************/
/**************   Version: 1.00         ***************/
/******************************************************/
/******************************************************/


#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"


#include  "DC_motor_Private.h"
#include  "DC_Motor_Config.h"
#include  "DC_Motor_Interface.h"


/************************************************************************************/
/************************************************************************************/
/** Function Name   : DC_MOTOR_enuInitialize.                                      **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : Copy_PStrMotorConfig.                                        **/
/** Functionality   : Initializing Motors                                          **/
/*This function take a pointer to struct of type DC_MOTOR_t & we use this          **/
/*pointer to access array elements & set direction of motors & state oF Enabled    **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/


ES_t  DC_MOTOR_enuInitialize(DC_MOTOR_t *Copy_PStrMotorConfig)
{
	ES_t Local_enuErrorState  = ES_NOK;

	if(Copy_PStrMotorConfig != NULL)
	{
		u8  Local_u8Iterator;

		for(Local_u8Iterator = 0 ; Local_u8Iterator < MOTOR_NUM ; Local_u8Iterator++)
		{

			Local_enuErrorState  = DIO_enuSetPinDirection(Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_IN1_PORT , Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_IN1_PIN , OUTPUT);
			Local_enuErrorState |= DIO_enuSetPinDirection(Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_IN2_PORT , Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_IN2_PIN , OUTPUT);
			Local_enuErrorState |= DIO_enuSetPinDirection(Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_ENABLE_PORT , Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_ENABLE_PIN , OUTPUT);
			Local_enuErrorState |=   DIO_enuSetPinValue(Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_ENABLE_PORT , Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_ENABLE_PIN , Copy_PStrMotorConfig[Local_u8Iterator].DC_MOTOR_ENABLE_STATE);
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return  Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/** Function Name   : DC_MOTOR_enuTurnRight.                                       **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : Copy_PStrMotor_ID.                                           **/
/** Functionality   : Turn Motors Right                                            **/
/*This function take a pointer to array element(Desired motor)                     **/
/*& we use it to turn the desired motor right                                      **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

ES_t  DC_MOTOR_enuTurnRight(DC_MOTOR_t *Copy_PStrMotor_ID)
{
	ES_t Local_enuErrorState  = ES_NOK;

	if(Copy_PStrMotor_ID != NULL)
	{
		Local_enuErrorState  = DIO_enuSetPinValue(Copy_PStrMotor_ID->DC_MOTOR_IN1_PORT , Copy_PStrMotor_ID->DC_MOTOR_IN1_PIN , HIGH);
		Local_enuErrorState |= DIO_enuSetPinValue(Copy_PStrMotor_ID->DC_MOTOR_IN2_PORT , Copy_PStrMotor_ID->DC_MOTOR_IN2_PIN , LOW);
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return  Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/** Function Name   : DC_MOTOR_enuTurnLeft.                                        **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : Copy_PStrMotor_ID.                                           **/
/** Functionality   : Turn Motors Left                                             **/
/*This function take a pointer to array element(Desired motor)                     **/
/*& we use it to turn the desired motor left                                       **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

ES_t  DC_MOTOR_enuTurnLeft(DC_MOTOR_t *Copy_PStrMotor_ID)
{
	ES_t Local_enuErrorState  = ES_NOK;

	if(Copy_PStrMotor_ID != NULL)
	{
		Local_enuErrorState  = DIO_enuSetPinValue(Copy_PStrMotor_ID->DC_MOTOR_IN1_PORT , Copy_PStrMotor_ID->DC_MOTOR_IN1_PIN , LOW);
		Local_enuErrorState |= DIO_enuSetPinValue(Copy_PStrMotor_ID->DC_MOTOR_IN2_PORT , Copy_PStrMotor_ID->DC_MOTOR_IN2_PIN , HIGH);
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return  Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/** Function Name   : DC_MOTOR_enuStop.                                            **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : Copy_PStrMotor_ID.                                           **/
/** Functionality   : Stop Motors                                                  **/
/*This function take a pointer to array element(Desired motor)                     **/
/*& we use it to Stop the desired motor                                            **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

ES_t  DC_MOTOR_enuStop(DC_MOTOR_t *Copy_PStrMotor_ID)
{
	ES_t Local_enuErrorState  = ES_NOK;

	if(Copy_PStrMotor_ID != NULL)
	{
		Local_enuErrorState  = DIO_enuSetPinValue(Copy_PStrMotor_ID->DC_MOTOR_IN1_PORT , Copy_PStrMotor_ID->DC_MOTOR_IN1_PIN , LOW);
		Local_enuErrorState |= DIO_enuSetPinValue(Copy_PStrMotor_ID->DC_MOTOR_IN2_PORT , Copy_PStrMotor_ID->DC_MOTOR_IN2_PIN , LOW);
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}



	return  Local_enuErrorState;
}
