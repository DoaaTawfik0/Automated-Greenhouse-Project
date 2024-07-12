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


/*###################################################################*/
#include "APP_Config.h"
#include "../MCAL/DIO/DIO_Register.h"
void Display(void);
/*###################################################################*/



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

	SPI_enuMasterInit(SPI_POLLING);
	ADC_enuInitialize();
	SoilMoisture_enuInitialize();
	LM35_enuInitialize();
	HIH5030_enuInit();
	LDR_enuInit(1);
	CLCD_enuInitialize();

	LED_enuInitialize(&LED_AStrConfig[2]);
	LED_enuInitialize(&LED_AStrConfig[3]);
	LED_enuInitialize(&LED_AStrConfig[4]);


#elif SPI_STATE == SPI_SLAVE

	SPI_enuSlaveInit(SPI_POLLING);


	DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[0]);
	DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[1]);
	DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[2]);

	LED_enuInitialize(&LED_AStrConfig[0]);
	LED_enuInitialize(&LED_AStrConfig[1]);





#else
#endif





	while(1)
	{

#if  SPI_STATE == SPI_MASTER




		//################################################  LDR      ###########################


		LDR_enuON(1 , &Local_u16LDR);
		CLCD_enuSendString("LDR = ");
		CLCD_enuWriteNumber(Local_u16LDR);

		if(Local_u16LDR < 512)
		{
			SPI_enuMasterTransmit(SPI_POLLING , LDR_LED_ON);
			//			LED_enuTurn_LED_ON(&LED_AStrConfig[0]);
			//			LED_enuTurn_LED_ON(&LED_AStrConfig[1]);

		}
		else
		{
			SPI_enuMasterTransmit(SPI_POLLING , LDR_LED_OFF);
			//			LED_enuTurn_LED_OFF(&LED_AStrConfig[0]);
			//			LED_enuTurn_LED_OFF(&LED_AStrConfig[1]);
		}

		_delay_ms(200);
		CLCD_enuClearDisplay();

		//		/********************************************SOIL Moisture**********************************/


		SoilMoisture_enuGetPercentage(0 , &Local_u8SoilMoisture);
		CLCD_enuSendString("SOIL = ");
		CLCD_enuWriteNumber(Local_u8SoilMoisture);

		/*moTORS ON*/
		if((Local_u8SoilMoisture >= 30) && (Local_u8SoilMoisture < 60))
		{
			//DC_MOTOR_enuTurnRight(&DC_MOTOR_AStrConfig[1]);
			SPI_enuMasterTransmit(SPI_POLLING , PUMPS_ON);
			LED_enuTurn_LED_OFF(&LED_AStrConfig[3]);
			//DIO_enuSetPinValue((DIO_PORTD , DIO_PIN4 , LOW);
		}
		//		else if((Local_u8SoilMoisture >= 60) && (Local_u8SoilMoisture < 80))
		//		{
		//			//DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[1]);
		//			SPI_enuMasterTransmit(SPI_POLLING , PUMPS_OFF);
		//			//DIO_enuSetPinValue((DIO_PORTD , DIO_PIN4 , LOW);
		//		}
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
			//DIO_enuSetPinDirection(DIO_PORTD , DIO_PIN4 , OUTPUT);
			//DIO_enuSetPinValue((DIO_PORTD , DIO_PIN4 , HIGH);
		}

		_delay_ms(200);
		CLCD_enuClearDisplay();

		//		//############################################################LM35
		//
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
			//			DIO_enuSetPinValue(DIO_PORTD,DIO_PIN4,HIGH);
		}

		_delay_ms(200);
		CLCD_enuClearDisplay();
		//#########################################################Humidity
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













		//########################################################### TEMP+HUMIDITY#################################//

		//		LM35_enuGetTemperature(2 , &Val);
		//		HIH5030_enuGet_Hum_Data(3 , &Local_u16HIH);
		//		CLCD_enuSendString("LM35 = ");
		//		CLCD_enuWriteNumber(Val);
		//		CLCD_enuGoToXY(1 , 0);
		//		CLCD_enuSendString("Humidity = ");
		//		CLCD_enuWriteNumber(Local_u16HIH);
		//
		//		if((Val >= 15) && (Val <= 30))
		//		{
		//			if(Val < 18)
		//			{
		//				SPI_enuMasterTransmit(SPI_POLLING , HEATERS_ON);
		//			}
		//			else if(Val > 25)
		//			{
		//				SPI_enuMasterTransmit(SPI_POLLING , FANS_ON);
		//			}
		//			else
		//			{
		//				SPI_enuMasterTransmit(SPI_POLLING , HEATERS_OFF);
		//				_delay_ms(500);
		//				SPI_enuMasterTransmit(SPI_POLLING , FANS_OFF);
		//			}
		//
		//		}
		//		else
		//		{
		//			DIO_enuSetPinValue(DIO_PORTD,DIO_PIN4,HIGH);
		//		}
		//		if(Local_u16HIH < 80)
		//		{
		//			if(Local_u16HIH > 60)
		//			{
		//				SPI_enuMasterTransmit(SPI_POLLING , FANS_ON);
		//			}
		//		}
		//		else
		//		{
		//			//Turn on Alert/
		//		}
		//
		//
		//		_delay_ms(200);
		//		CLCD_enuClearDisplay();

		//############################################################################################//






#elif SPI_STATE == SPI_SLAVE


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
		//		else
		//		{
		//			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[0]);
		//			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[1]);
		//			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[2]);
		//			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[3]);
		//			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[4]);
		//			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[5]);
		//
		//			LED_enuTurn_LED_OFF(&LED_AStrConfig[0]);
		//			LED_enuTurn_LED_OFF(&LED_AStrConfig[1]);
		//		}


#else


#error "SPI "
#endif



	}

	return 0;
}

void Display(void)
{
	DIO_enuSetPortDirection(DIO_PORTA , OUTPUT);
	DIO_enuSetPortValue(DIO_PORTA , 5);
}












//#include "../LIB/ERROR_STATE.h"
//#include "APP_Interface.h"
//
//
//
//
//int main()
//{
//		APP_enuMain_Fun();
//
//	while(1)
//	{
//
//		 APP_enuMainWhile_Fun();
//
//	}
//	return 0;
//}


