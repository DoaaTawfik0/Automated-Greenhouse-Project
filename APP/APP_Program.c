/******************************************************/
/******************************************************/
/**************   Layer:  APP           ***************/
/**************   Created: Jul 7, 2024  ***************/
/******************************************************/
/******************************************************/



#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/ERROR_STATE.h"


#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/Port/Port_Interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/SPI/SPI_Interface.h"


#include "../HAL/Character_LCD/CLCD_Interface.h"
#include "../HAL/DC_Motor/DC_Motor_Interface.h"
#include "../HAL/Soil_Moisture/Soil_Moisture_Interface.h"
#include "../HAL/LED/LED_Interface.h"
#include "../HAL/LM35/LM35_Interface.h"

#include "APP_Private.h"
#include "APP_Interface.h"
#include "APP_Config.h"




/********************************************************************/
/*                 ProtoTypes for Static Functions                 */
/*******************************************************************/
static ES_t  APP_enuMaster_Init(void);
static ES_t  APP_enuSlave_Init(void);



/********************************************************************/
/*                 Definition for Variables                         */
/*******************************************************************/
extern DC_MOTOR_t  DC_MOTOR_AStrConfig[MOTOR_NUM];
extern LED_t       LED_AStrConfig[LED_NUM];




/************************************************************************************/
/************************************************************************************/
/** Function Name   : APP_enuMain_Fun.                                             **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : void.                                                        **/
/** Functionality   : Main Function to be called in main                           **/
/*This function should include all code to be done by Master/Slave                 **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
ES_t  APP_enuMain_Fun(void)
{
	ES_t  Local_enuErrorState = ES_NOK;

#if SPI_STATE == SPI_MASTER

	/*1-Make Master Initialization*/
	APP_enuMaster_Init();


	/***************************This Should be done in while one********************/

	/*2-Activate Channels in a Periodic way to get Readings*/


	/*3-Print Readings on Character LCD*/


	/*4-Check on Readings if in range send some value to Slave to enable specific Actuators*/


	/*5-Check on Readings if out of range send some value to Slave to enable specific Alerts*/


#elif SPI_STATE == SPI_SLAVE

	/*Make Slave Initialization*/
	APP_enuSlave_Init();


	/***************************This Should be done in while one********************/

	/*2-Read From Master & based on value take an action*/
	/*enable [Actuators/Alerts]*/


#else
#error "SPI is Out Of Range....."

#endif


	return Local_enuErrorState;
}





/************************************************************************************/
/************************************************************************************/
/*        Static Function helps me to Initialize Master & Slave                     */
/************************************************************************************/
/************************************************************************************/
static ES_t  APP_enuMaster_Init(void)
{
	ES_t  Local_enuErrorState = ES_NOK;


	/*1-Initialize Soil Moisture->Master->look@ Soil_Moisture_Config.h*/
	SoilMoisture_enuInitialize();

	/*2-Initialize LDR->Master->look@ LDR_Config.h*/
	/*Fun*/

	/*3-Initialize Temp&Humidity Sensor*/
	/*Fun*/

	/*4-Initialize Character LCD->Master->look@ CLCD_Config.h*/
	CLCD_enuInitialize();

	/*5-Initialize SPI as Mater->look@ SPI_Config.h*/
	SPI_enuMasterInit(SPI_POLLING);


	return Local_enuErrorState;
}



static ES_t  APP_enuSlave_Init(void)
{
	ES_t  Local_enuErrorState = ES_NOK;


	/*1-Initialize Motors->Slave->look@ DC_Motor_Config.c*/
	DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[0]);

	/*2-Initialize LEDS->Slave->look@ LED_Config.c*/
	LED_enuInitialize(&LED_AStrConfig[0]);

	/*3-Initialize SPI as Slave->look@ SPI_Config.h*/
	SPI_enuSlaveInit(SPI_POLLING);


	return Local_enuErrorState;
}
