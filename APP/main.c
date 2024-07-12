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


void Display(void);


/********************************************************************/
/*                 Definition for Variables                         */
/*******************************************************************/
extern DC_MOTOR_t  DC_MOTOR_AStrConfig[MOTOR_NUM];
extern LED_t       LED_AStrConfig[LED_NUM];

u16 Local_val;
u8 Val1 , Val2 , Val;
u8  Local_u8SoilMoisture , Local_u8LM35;
u16 Local_u16LDR , Local_u16HIH;

int main()
{


	_delay_ms(2000);

	GIE_enuEnable();


#if  SPI_STATE == SPI_MASTER


	/*1-Initialize SPI as Mater->look@ SPI_Config.h*/
	SPI_enuMasterInit(SPI_POLLING);
	/*2-Initialize ADC->Master->look@ADC_Interface.h*/
	ADC_enuInitialize();
	/*3-Initialize Soil Moisture->Master->look@ Soil_Moisture_Config.h*/
	SoilMoisture_enuInitialize();
	/*4-Initialize LM35 Sensor*/
	LM35_enuInitialize();
	/*5-Initialize HIH5030 Sensor*/
	HIH5030_enuInit();
	/*6-Initialize LDR->Master->look@ LDR_Config.h*/
	LDR_enuInit(1);
	/*7-Initialize Character LCD->Master->look@ CLCD_Config.h*/
	CLCD_enuInitialize();
	/*8-Initialize LEDS*/
	LED_enuInitialize(&LED_AStrConfig[2]);
	LED_enuInitialize(&LED_AStrConfig[3]);
	LED_enuInitialize(&LED_AStrConfig[4]);

	/*Turn off all actuators*/
	LED_enuTurn_LED_OFF(&LED_AStrConfig[2]);
	LED_enuTurn_LED_OFF(&LED_AStrConfig[3]);
	LED_enuTurn_LED_OFF(&LED_AStrConfig[4]);

#elif SPI_STATE == SPI_SLAVE

	/*1-Initialize SPI as Slave->look@ SPI_Config.h*/
	SPI_enuSlaveInit(SPI_POLLING);

	/*2-Initialize Motors->Slave->look@ DC_Motor_Config.c*/
	DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[0]);
	DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[1]);
	DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[2]);

	/*3-Initialize LEDS->Slave->look@ LED_Config.c*/
	LED_enuInitialize(&LED_AStrConfig[0]);
	LED_enuInitialize(&LED_AStrConfig[1]);

	/*Turn Off all actuators*/
	DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[0]);
	DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[1]);
	DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[2]);
	LED_enuTurn_LED_OFF(&LED_AStrConfig[0]);
	LED_enuTurn_LED_OFF(&LED_AStrConfig[1]);

#else
#endif



	while(1)
	{

#if  SPI_STATE == SPI_MASTER


        /*Check on LDR Sensor*/
		LDR_enuON(1 , &Local_u16LDR);
		CLCD_enuSendString("LDR = ");
		CLCD_enuWriteNumber(Local_u16LDR);

		if(Local_u16LDR < 512)
		{
			SPI_enuMasterTransmit(SPI_POLLING , LDR_LED_ON);
		}
		else
		{
			SPI_enuMasterTransmit(SPI_POLLING , LDR_LED_OFF);
		}

		_delay_ms(200);
		CLCD_enuClearDisplay();


		/*Check on Soil Moisture Sensor*/
		SoilMoisture_enuGetPercentage(0 , &Local_u8SoilMoisture);
		CLCD_enuSendString("SOIL = ");
		CLCD_enuWriteNumber(Local_u8SoilMoisture);

		if((Local_u8SoilMoisture >= 30) && (Local_u8SoilMoisture < 60))
		{
			SPI_enuMasterTransmit(SPI_POLLING , PUMPS_ON);
			LED_enuTurn_LED_OFF(&LED_AStrConfig[3]);
		}
		else
		{
			SPI_enuMasterTransmit(SPI_POLLING , PUMPS_OFF);
			if(Local_u8SoilMoisture > 80)
			{
				LED_enuTurn_LED_ON(&LED_AStrConfig[3]);
			}
			else
			{
				LED_enuTurn_LED_OFF(&LED_AStrConfig[3]);
			}
		}

		_delay_ms(200);
		CLCD_enuClearDisplay();


		/*Check on LM35 Sensor*/
		LM35_enuGetTemperature(2 , &Local_u8LM35);
		CLCD_enuSendString("LM35 = ");
		CLCD_enuWriteNumber(Local_u8LM35);

		if((Local_u8LM35 >= 15) && (Local_u8LM35 <= 30))
		{
			if(Local_u8LM35 < 18)
			{
				SPI_enuMasterTransmit(SPI_POLLING , HEATERS_ON);
			}
			else if((Local_u8LM35 > 25) && (Local_u16HIH < 80))
			{
				SPI_enuMasterTransmit(SPI_POLLING , FANS_ON);
			}
			else
			{
				SPI_enuMasterTransmit(SPI_POLLING , HEATER_FAN_OFF);
			}

			LED_enuTurn_LED_OFF(&LED_AStrConfig[4]);
		}
		else
		{
			SPI_enuMasterTransmit(SPI_POLLING , HEATER_FAN_OFF);
			LED_enuTurn_LED_ON(&LED_AStrConfig[4]);
		}

		_delay_ms(200);
		CLCD_enuClearDisplay();



		/*Check on Humidity Sensor*/
		//		HIH5030_enuGet_Hum_Data(3 , &Local_u16HIH);
		//		CLCD_enuSendString("Humidity = ");
		//		CLCD_enuWriteNumber(Local_u16HIH);
		//
		//		if((Local_u16HIH < 80) && (Local_u8LM35 > 25))
		//		{
		//			//SPI_enuMasterTransmit(SPI_POLLING , FANS_ON);
		//			DC_MOTOR_enuTurnRight(&DC_MOTOR_AStrConfig[2]);
		//		}
		//		else
		//		{
		//			//SPI_enuMasterTransmit(SPI_POLLING , FANS_OFF);
		//			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[2]);
		//			//Turn on Alert/
		//		}
		//
		//
		//		_delay_ms(200);
		//		CLCD_enuClearDisplay();




#elif SPI_STATE == SPI_SLAVE

		/*Read Value from SPI*/
		SPI_enuSlaveASyncReceive(Display , &Val);

		if(Val == HEATER_FAN_OFF)
		{
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[0]);
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[2]);
		}
		if(Val == PUMPS_ON)
		{
			DC_MOTOR_enuTurnRight(&DC_MOTOR_AStrConfig[1]);
		}
		if(Val == PUMPS_OFF)
		{
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[1]);
		}
		if(Val == FANS_ON)
		{
			DC_MOTOR_enuTurnRight(&DC_MOTOR_AStrConfig[0]);
		}
		if(Val == FANS_OFF)
		{
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[0]);
		}
		if(Val == HEATERS_ON)
		{
			DC_MOTOR_enuTurnRight(&DC_MOTOR_AStrConfig[2]);
		}
		if(Val == HEATERS_OFF)
		{
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[2]);
		}
		if(Val == LDR_LED_ON)
		{
			LED_enuTurn_LED_ON(&LED_AStrConfig[0]);
			LED_enuTurn_LED_ON(&LED_AStrConfig[1]);
		}
		if(Val == LDR_LED_OFF)
		{
			LED_enuTurn_LED_OFF(&LED_AStrConfig[0]);
			LED_enuTurn_LED_OFF(&LED_AStrConfig[1]);
		}

#else


#error "SPI is out of range"
#endif



	}

	return 0;
}

void Display(void)
{
	DIO_enuSetPortDirection(DIO_PORTA , OUTPUT);
	DIO_enuTogglePortValue(DIO_PORTA);
}





