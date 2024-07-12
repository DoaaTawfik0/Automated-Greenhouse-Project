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

	/********************************************SOIL END***************************************/

	/*2-Activate Channels in a Periodic way to get Readings*/
	/******************************************** LDR **********************************/

	LDR_enuON(1 , &u16LDR_Read);

	/*3-Print Readings on Character LCD*/

	CLCD_enuSendString("LDR = ");
	CLCD_enuWriteNumber(u16LDR_Read);

	/*4-Check on Readings if in range send some value to Slave to enable specific Actuators*/

	LDR_enuCheckRange(u16LDR_Read);

	/*5-For handling Display */
	_delay_ms(200);
	CLCD_enuClearDisplay();

	/********************************************LDR END***************************************/

	/*2-Activate Channels in a Periodic way to get Readings*/
	/******************************************** TEMP+HUMIDITY **********************************/

	LM35_enuGetTemperature(2 , &u8LM35_Read);

	/*3-Print Readings on Character LCD*/

		CLCD_enuSendString("LM35 = ");
		CLCD_enuWriteNumber(u8LM35_Read);
		CLCD_enuGoToXY(1 , 0);
		HIH5030_enuGet_Hum_Data(3 , &u16HIH_Read);
		CLCD_enuSendString("Humidity = ");
		CLCD_enuWriteNumber(u16HIH_Read);
	/*4-Check on Readings if in range send some value to Slave to enable specific Actuators*/

	LDR_enuCheckRange(u16LDR_Read);

	/*5-For handling Display */
	_delay_ms(200);
	CLCD_enuClearDisplay();

	/********************************************TEMP+HUMIDITY END***************************************/

	/*############################################### *END MASTER*######################################*/
#elif SPI_STATE == SPI_SLAVE




	/***************************This Should be done in while one********************/

	/*2-Read From Master & based on value take an action*/
	APP_enuSlave_Init();
	/*enable [Actuators/Alerts]*/
	SPI_enuCheckAction();

#else
#error "SPI is Out Of Range....."

#endif


	return Local_enuErrorState;
