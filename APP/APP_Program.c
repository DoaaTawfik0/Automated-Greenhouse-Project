/******************************************************/
/******************************************************/
/**************   Layer:  APP           ***************/
/**************   Created: Jul 7, 2024  ***************/
/******************************************************/
/******************************************************/


#include "../LIB/STD_TYPES.h"
#include "../LIB/ERROR_STATE.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/Interrupt.h"


#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/Port/Port_Interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/SPI/SPI_Interface.h"


#include "../HAL/Character_LCD/CLCD_Interface.h"
#include "../HAL/DC_Motor/DC_Motor_Interface.h"
#include "../HAL/LED/LED_Interface.h"
#include "../HAL/LM35/LM35_Interface.h"
#include "../HAL/HIH5030/HIH5030_Interface.h"
#include "../HAL/Soil_Moisture/Soil_Moisture_Interface.h"
#include "../HAL/LDR/LDR.h"

#include "../MCAL/GIE/GIE_Interface.h"

#include "util/delay.h"


#include "APP_Interface.h"
#include "APP_Private.h"
#include "APP_Config.h"

//###########################################33333/
#include "../MCAL/DIO/DIO_Register.h"
//#############################################33

/********************************************************************/
/*                 ProtoTypes for Static Functions                 */
/*******************************************************************/
static ES_t  APP_enuMaster_Init(void);
static ES_t  APP_enuSlave_Init(void);

static ES_t SOIL_enuCheckRange(u8 Copy_u8RangeVal);
static ES_t LDR_enuCheckRange(u16 Copy_u16RangeVal);
static ES_t LM_HIH_enuCheckRange(u8 Copy_u8RangeVal, u16 Copy_u16RangeVal);

static ES_t SPI_enuCheckAction(void);
/********************************************************************/
/*                 Definition for Variables                         */
/*******************************************************************/
extern DC_MOTOR_t  DC_MOTOR_AStrConfig[MOTOR_NUM];
extern LED_t       LED_AStrConfig[LED_NUM];



void Display(void);
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

static u16 u16LDR_Read;
static u16 u16HIH_Read;
static u8  u8SOIL_Read;
static u8  u8LM35_Read;
static u8 SPI_Recive_value;

ES_t  APP_enuMain_Fun(void)
{
	ES_t  Local_enuErrorState = ES_NOK;

#if SPI_STATE == SPI_MASTER
	/*1-Make Master Initialization*/

	Local_enuErrorState = APP_enuMaster_Init();
#elif SPI_STATE == SPI_SLAVE
	/*Make Slave Initialization*/
	Local_enuErrorState = APP_enuSlave_Init();
#endif

	return Local_enuErrorState;
}


ES_t  APP_enuMainWhile_Fun(void)
{
	ES_t  Local_enuErrorState = ES_NOK;

#if SPI_STATE == SPI_MASTER

	/*1-Make Master Initialization*/



	/***************************This Should be done in while one********************/

	/*2-Activate Channels in a Periodic way to get Readings*/
	/********************************************SOIL Moisture**********************************/

	SPI_enuMasterInit(SPI_POLLING);
	SoilMoisture_enuGetPercentage(0 , &u8SOIL_Read);


	/*3-Print Readings on Character LCD*/

	CLCD_enuSendString("SOIL = ");
	CLCD_enuWriteNumber(u8SOIL_Read);


	/*4-Check on Readings if in range send some value to Slave to enable specific Actuators*/

	SOIL_enuCheckRange(u8SOIL_Read);
	/*5-For handling Display */
	_delay_ms(200);
	CLCD_enuClearDisplay();

	//	/********************************************SOIL END***************************************/
	//
	//	/*2-Activate Channels in a Periodic way to get Readings*/
	//	/******************************************** LDR **********************************/
	//
	//	LDR_enuON(1 , &u16LDR_Read);
	//
	//	/*3-Print Readings on Character LCD*/
	//
	//	CLCD_enuSendString("LDR = ");
	//	CLCD_enuWriteNumber(u16LDR_Read);
	//
	//	/*4-Check on Readings if in range send some value to Slave to enable specific Actuators*/
	//
	//	LDR_enuCheckRange(u16LDR_Read);
	//
	//	/*5-For handling Display */
	//	_delay_ms(200);
	//	CLCD_enuClearDisplay();
	//
	//	/********************************************LDR END***************************************/
	//
	//	/*2-Activate Channels in a Periodic way to get Readings*/
	//	/******************************************** TEMP+HUMIDITY **********************************/
	//
	//	LM35_enuGetTemperature(2 , &u8LM35_Read);
	//
	//	/*3-Print Readings on Character LCD*/
	//
	//		CLCD_enuSendString("LM35 = ");
	//		CLCD_enuWriteNumber(u8LM35_Read);
	//		CLCD_enuGoToXY(1 , 0);
	//		HIH5030_enuGet_Hum_Data(3 , &u16HIH_Read);
	//		CLCD_enuSendString("Humidity = ");
	//		CLCD_enuWriteNumber(u16HIH_Read);
	//	/*4-Check on Readings if in range send some value to Slave to enable specific Actuators*/
	//
	//	LDR_enuCheckRange(u16LDR_Read);
	//
	//	/*5-For handling Display */
	//	_delay_ms(200);
	//	CLCD_enuClearDisplay();

	/********************************************TEMP+HUMIDITY END***************************************/

	/*############################################### *END MASTER*######################################*/
#elif SPI_STATE == SPI_SLAVE




	/***************************This Should be done in while one********************/

	/*2-Read From Master & based on value take an action*/
	//APP_enuSlave_Init();
	SPI_enuSlaveASyncReceive(Display , &SPI_Recive_value);
	/*enable [Actuators/Alerts]*/
	SPI_enuCheckAction();

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

	_delay_ms(1000);

	GIE_enuEnable();
	/*1-Initialize ADC->Master->look@ADC_Interface.h*/
	ADC_enuInitialize();
	/*1-Initialize Soil Moisture->Master->look@ Soil_Moisture_Config.h*/
	SoilMoisture_enuInitialize();

	/*2-Initialize LDR->Master->look@ LDR_Config.h*/
	/*Fun*/
	LDR_enuInit(1);
	/*3-Initialize Temp&Humidity Sensor*/
	/*Fun*/
	LM35_enuInitialize();
	HIH5030_enuInit();
	/*4-Initialize Character LCD->Master->look@ CLCD_Config.h*/
	CLCD_enuInitialize();

	/*5-Initialize SPI as Mater->look@ SPI_Config.h*/
	SPI_enuMasterInit(SPI_POLLING);


	return Local_enuErrorState;
}



static ES_t  APP_enuSlave_Init(void)
{
	ES_t  Local_enuErrorState = ES_NOK;

	GIE_enuEnable();

	/******************************************** SPI **********************************/
	/*1-Initialize Motors->Slave->look@ DC_Motor_Config.c*/
	DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[0]);
	DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[1]);
	DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[2]);
	DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[3]);
	DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[4]);
	DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[5]);

	/*2-Initialize LEDS->Slave->look@ LED_Config.c*/
	LED_enuInitialize(&LED_AStrConfig[0]);
	LED_enuInitialize(&LED_AStrConfig[1]);
	/*3-Initialize SPI as Slave->look@ SPI_Config.h*/
	SPI_enuSlaveInit(SPI_POLLING);
	SPI_enuSlaveASyncReceive(Display , &SPI_Recive_value);
	/*4-Check The SPI Reseved Value Action*/
	SPI_enuCheckAction();
	return Local_enuErrorState;
}

static ES_t SPI_enuCheckAction(void)
{
	ES_t Local_ErrorState=ES_NOK;

//	DIO_enuSetPortDirection(DIO_PORTA , OUTPUT);
//	DIO_enuSetPortValue(DIO_PORTA , SPI_Recive_value);

	//SPI_Recive_value = 2;

	if(SPI_Recive_value == FANS_ON)
	{
		DC_MOTOR_enuTurnRight(&DC_MOTOR_AStrConfig[0]);
		DC_MOTOR_enuTurnRight(&DC_MOTOR_AStrConfig[1]);
	}
	if(SPI_Recive_value == FANS_OFF)
	{
		DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[0]);
		DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[1]);
	}
	if(SPI_Recive_value == PUMPS_ON)
	{
		DC_MOTOR_enuTurnRight(&DC_MOTOR_AStrConfig[2]);
		DC_MOTOR_enuTurnRight(&DC_MOTOR_AStrConfig[3]);
	}
	if(SPI_Recive_value == PUMPS_OFF)
	{
		DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[2]);
		DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[3]);
	}
	if(SPI_Recive_value == HEATERS_ON)
	{
		DC_MOTOR_enuTurnRight(&DC_MOTOR_AStrConfig[4]);
		DC_MOTOR_enuTurnRight(&DC_MOTOR_AStrConfig[5]);
	}
	else if(SPI_Recive_value == HEATERS_OFF)
	{
		DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[4]);
		DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[5]);
	}
	if(SPI_Recive_value == LDR_LED_ON)
	{
		LED_enuTurn_LED_ON(&LED_AStrConfig[0]);
		LED_enuTurn_LED_ON(&LED_AStrConfig[1]);
	}
	if(SPI_Recive_value == LDR_LED_OFF)
	{
		LED_enuTurn_LED_OFF(&LED_AStrConfig[0]);
		LED_enuTurn_LED_OFF(&LED_AStrConfig[1]);
	}
	//	else
		//	{
	//		DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[0]);
	//		DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[1]);
	//		DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[2]);
	//		DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[3]);
	//		DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[4]);
	//		DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[5]);
	//
	//		LED_enuTurn_LED_OFF(&LED_AStrConfig[0]);
	//		LED_enuTurn_LED_OFF(&LED_AStrConfig[1]);
	//	}

	return Local_ErrorState;
}

static ES_t SOIL_enuCheckRange(u8 Copy_u8RangeVal)
{
	ES_t Local_enuErrorState = ES_NOK;
	/********************************************SOIL Moisture**********************************/

	/*moTORS ON*/
	if((Copy_u8RangeVal >= 30) && (Copy_u8RangeVal < 60))
	{
		SPI_enuMasterTransmit(SPI_POLLING , PUMPS_ON);
		//DIO_enuSetPinValue((DIO_PORTD , DIO_PIN4 , LOW);
	}
	else if((Copy_u8RangeVal >= 60) && (Copy_u8RangeVal < 80))
	{
		SPI_enuMasterTransmit(SPI_POLLING , PUMPS_OFF);
		//DIO_enuSetPinValue((DIO_PORTD , DIO_PIN4 , LOW);
	}

	/*5-Check on Readings if out of range send some value to Slave to enable specific Alerts*/

	else
	{
		//DIO_enuSetPinDirection(DIO_PORTD , DIO_PIN4 , OUTPUT);
		//DIO_enuSetPinValue((DIO_PORTD , DIO_PIN4 , HIGH);
	}
	return Local_enuErrorState;
}
static ES_t LDR_enuCheckRange(u16 Copy_u16RangeVal)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_u16RangeVal > 512)
	{
		SPI_enuMasterTransmit(SPI_POLLING , LDR_LED_ON);
	}
	else
	{
		SPI_enuMasterTransmit(SPI_POLLING , LDR_LED_OFF);
	}

	return Local_enuErrorState;
}
static ES_t LM_HIH_enuCheckRange(u8 Copy_u8RangeVal, u16 Copy_u16RangeVal)
{
	ES_t Local_enuErrorState = ES_NOK;
	if((Copy_u8RangeVal >= 15) && (Copy_u8RangeVal <= 30))
	{
		if(Copy_u8RangeVal < 18)
		{
			SPI_enuMasterTransmit(SPI_POLLING , HEATERS_ON);
		}
		else if(Copy_u8RangeVal > 25)
		{
			SPI_enuMasterTransmit(SPI_POLLING , FANS_ON);
		}
		else
		{
			SPI_enuMasterTransmit(SPI_POLLING , HEATERS_OFF);
			_delay_ms(500);
			SPI_enuMasterTransmit(SPI_POLLING , FANS_OFF);
		}

	}
	else
	{
		DIO_enuSetPinValue(DIO_PORTD,DIO_PIN4,HIGH);
	}
	if(Copy_u16RangeVal < 80)
	{
		if(Copy_u16RangeVal > 60)
		{
			SPI_enuMasterTransmit(SPI_POLLING , FANS_ON);
		}
		else
		{
			SPI_enuMasterTransmit(SPI_POLLING , HEATERS_OFF);
			_delay_ms(500);
			SPI_enuMasterTransmit(SPI_POLLING , FANS_OFF);
		}

	}
	else
	{
		//Turn on Alert/
	}
	return Local_enuErrorState;
}

//void Display(void)
//{
////	DIO_enuSetPortDirection(DIO_PORTA , OUTPUT);
////	TOGGLE_BIT(PORTA , 0);
//}
