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


int main()
{


	_delay_ms(2000);

	GIE_enuEnable();

	SoilMoisture_enuInitialize();
	LM35_enuInitialize();
	HIH5030_enuInit();
	LDR_enuInit(1);

	CLCD_enuInitialize();



	u16 Local_val;
	u8 Val;

	while(1)
	{

#if  SPI_STATE == SPI_MASTER

		SPI_enuMasterInit(SPI_POLLING);
		SoilMoisture_enuGetPercentage(0 , &Val);
		CLCD_enuWriteNumber(Val);

		if(Val > 50)
		{
			SPI_enuMasterTransmit(SPI_POLLING , 2);
		}
		else
		{
			SPI_enuMasterTransmit(SPI_POLLING , 3);
		}
		_delay_ms(200);
		CLCD_enuClearDisplay();

		//###########################################################33

		LM35_enuGetTemperature(2 , &Val);
		CLCD_enuWriteNumber(Val);

		if(Val >= 25)
		{
			SPI_enuMasterTransmit(SPI_POLLING , 4);
		}
		else if(Val < 25)
		{
			SPI_enuMasterTransmit(SPI_POLLING , 5);
		}
		else
		{
			SPI_enuMasterTransmit(SPI_POLLING , 6);
		}
		_delay_ms(200);
		CLCD_enuClearDisplay();







#elif SPI_STATE == SPI_SLAVE

		SPI_enuSlaveInit(SPI_POLLING);

		DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[0]);
		DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[1]);
		DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[2]);
		DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[3]);
		DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[4]);
		DC_MOTOR_enuInitialize(&DC_MOTOR_AStrConfig[5]);

		LED_enuInitialize(&LED_AStrConfig[0]);
		LED_enuInitialize(&LED_AStrConfig[1]);

		SPI_enuSlaveASyncReceive(Display , &Val);
		//SPI_enuSlaveReceive(SPI_POLLING , &Val);

		if(Val == 2)
		{
			DC_MOTOR_enuTurnRight(&DC_MOTOR_AStrConfig[2]);
			DC_MOTOR_enuTurnRight(&DC_MOTOR_AStrConfig[3]);
		}
		else if(Val == 4)
		{
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[0]);
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[1]);
		}
		else if(Val == 5)
		{
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[4]);
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[5]);
		}
		else
		{
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[0]);
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[1]);
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[2]);
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[3]);
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[4]);
			DC_MOTOR_enuStop(&DC_MOTOR_AStrConfig[5]);
		}


#else


#error "SPI "
#endif



	}

	return 0;
}

void Display(void)
{
	TOGGLE_BIT(PORTA , 0);
}
