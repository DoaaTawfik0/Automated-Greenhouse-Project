/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  HAL           ***************/
/**************   SWC:    CLCD          ***************/
/**************   Version: 2.00         ***************/
/******************************************************/
/******************************************************/

#include  "../../LIB/STD_TYPES.h"
#include  "../../LIB/BIT_MATH.h"
#include  "../../LIB/ERROR_STATE.h"

#include  "../../MCAL/DIO/DIO_Interface.h"

#include  "CLCD_Interface.h"
#include  "CLCD_Config.h"
#include  "CLCD_Private.h"


#include  "util/delay.h"

/********************************************************************/
/*                 ProtoTypes fo Static Functions                  */
/*******************************************************************/
static ES_t CLCD_u8Latch(u8 Copy_u8Data);

static inline ES_t  CLCD_InenuSendCommand(u8 Copy_u8Command);
static inline ES_t  CLCD_InenuSendCharacter(u8 Copy_u8Character);

static inline ES_t  CLCD_InenuSetPinsDirection(void);

/*******************************************************************/
/*******************************************************************/



/************************************************************************************/
/************************************************************************************/
/** Function Name   : CLCD_enuInitialize.                                          **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : void.                                                        **/
/** Functionality   : Initializing Character_LCD                                   **/
/*This function Initialize Control & data pins Direction  & set initialization     **/
/*for EIGHT_BIT_MODE or FOUR_BIGHT_MODE                                            **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

ES_t  CLCD_enuInitialize(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	Local_enuErrorState  = CLCD_InenuSetPinsDirection();

	_delay_ms(40);

#if  CLCD_MODE  == EIGHT_BIT

	Local_enuErrorState |= CLCD_InenuSendCommand(FUNCTION_SET_EIGHT_BIT);

#elif  CLCD_MODE == FOUR_BIT

	Local_enuErrorState |= CLCD_InenuSendCommand(FUNCTION_SET_FOUR_BIT);

#else
#error "Invalid CLCD Mode"

#endif

	_delay_ms(1);
	Local_enuErrorState |= CLCD_InenuSendCommand(DISPLAY_ON_OFF);
	_delay_ms(1);
	Local_enuErrorState |= CLCD_InenuSendCommand(DISPLAY_CLEAR);
	_delay_ms(2);
	Local_enuErrorState |= CLCD_InenuSendCommand(ENTRY_MODE_SET);

	return Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/** Function Name   : CLCD_enuSendCommand.                                         **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : Copy_u8Command.                                              **/
/** Functionality   : Sending Command to CLCD MCU                                  **/
/*This function take any Command & send it on data bus                             **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

ES_t  CLCD_enuSendCommand(u8 Copy_u8Command)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Set Register Select Pin with 0 for command*/
	Local_enuErrorState  = DIO_enuSetPinValue(CLCD_REGISTER_SELECT_PORT , CLCD_REGISTER_SELECT_PIN , LOW);

	Local_enuErrorState |= CLCD_u8Latch(Copy_u8Command);

	return Local_enuErrorState;
}

/************************************************************************************/
/************************************************************************************/
/** Function Name   : CLCD_enuSendCharacter.                                       **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : Copy_u8Character.                                            **/
/** Functionality   : Sending Character to CLCD                                    **/
/*This function take any character & print it on LCD                               **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

ES_t  CLCD_enuSendCharacter(u8 Copy_u8Character)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Set Register Select Pin with 0 for Data*/
	Local_enuErrorState  = DIO_enuSetPinValue(CLCD_REGISTER_SELECT_PORT , CLCD_REGISTER_SELECT_PIN , HIGH);

	Local_enuErrorState |= CLCD_u8Latch(Copy_u8Character);

	return Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/** Function Name   : CLCD_enuSendString.                                          **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : Copy_pcString.                                               **/
/** Functionality   : Sending String to CLCD                                       **/
/*This function take any String & print it on LCD                                  **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

ES_t CLCD_enuSendString(const char* Copy_pcString)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8   Local_u8Iterator = 0;
	if(Copy_pcString != NULL)
	{
		while(Copy_pcString[Local_u8Iterator] != NULL_CHARACTER)
		{
			Local_enuErrorState |= CLCD_InenuSendCharacter(Copy_pcString[Local_u8Iterator]);
			Local_u8Iterator++;
		}
	}
	else
	{

		Local_enuErrorState = ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/** Function Name   : CLCD_enuGoToXY.                                              **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : Copy_u8XPosition , Copy_u8YPosition.                         **/
/** Functionality   : changing display Position                                    **/
/*This function take X & Y Positions for LCD & Change DDRAM Position               **/
/*according to these positions                                                     **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

ES_t CLCD_enuGoToXY(u8 Copy_u8XPosition  , u8 Copy_u8YPosition)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8   Local_u8DDRAMAddress;
	if((Copy_u8XPosition >= 0) && (Copy_u8XPosition < 2) && (Copy_u8YPosition >= 0) && (Copy_u8YPosition < 16))
	{
		if(Copy_u8XPosition == 0)
		{
			Local_u8DDRAMAddress = Copy_u8YPosition;
		}
		else
		{
			Local_u8DDRAMAddress = (Copy_u8YPosition + 0x40);
		}
		//Set DDRAM Address Command: 128 to set bit '8' with value one
		Local_u8DDRAMAddress += 128;
		Local_enuErrorState = CLCD_InenuSendCommand(Local_u8DDRAMAddress);

	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return  Local_enuErrorState;
}


/**********************************************************************************************************/
/**********************************************************************************************************/
/** Function Name   : CLCD_enuWriteSpecialCharacter.                                                     **/
/** Return Type     : Error_State enum.                                                                  **/
/** Arguments       : Copy_pu8Pattern , Copy_u8PatternNumber , Copy_u8XPosition , Copy_u8YPosition       **/
/** Functionality   : Writing Special character on LCD                                                   **/
/*This function take pointer to an array that hold the pattern of character i want to display            **/
/*, Pattern block in CGRAM , X & Y Positions to calculate address in DDRAM                               **/
/**********************************************************************************************************/
/**********************************************************************************************************/
/**********************************************************************************************************/

ES_t CLCD_enuWriteSpecialCharacter(u8* Copy_pu8Pattern , u8 Copy_u8PatternNumber , u8 Copy_u8XPosition  , u8 Copy_u8YPosition)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8   Local_u8Iterator  , Local_u8Address;
	if(Copy_pu8Pattern != NULL)
	{
		Local_u8Address = Copy_u8PatternNumber*8;
		//Set CGRAM Address Command: 64 to set bit '7' with value one
		Local_enuErrorState  = CLCD_InenuSendCommand(Local_u8Address+64);
		for(Local_u8Iterator = 0 ; Local_u8Iterator < 8 ; Local_u8Iterator++)
		{
			Local_enuErrorState |= CLCD_InenuSendCharacter(Copy_pu8Pattern[Local_u8Iterator]);
		}
		/*To go back to DDRAM*/
		Local_enuErrorState |= CLCD_enuGoToXY(Copy_u8XPosition , Copy_u8YPosition);
		/*let DDRAM print value stored in CGRAM By Knowing it's block Number*/
		Local_enuErrorState |= CLCD_InenuSendCharacter(Copy_u8PatternNumber);
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : CLCD_enuWriteNumber.                                  **/
/** Return Type     : Error_State.                                          **/
/** Arguments       : Copy_u32Number                                        **/
/** Functionality   : Write any number on lcd                               **/
/*****************************************************************************/
/*****************************************************************************/

ES_t CLCD_enuWriteNumber(u32 Copy_u32Number)
{
	ES_t Local_enuErrorState = ES_NOK;
	u32  Local_u32rev_num = 1;

	if (Copy_u32Number == 0) {
		Local_enuErrorState |= CLCD_InenuSendCharacter('0'); // Send '0' character to LCD
		return Local_enuErrorState;
	}
	while(Copy_u32Number != 0)
	{
		Local_u32rev_num = ((Local_u32rev_num*10) + (Copy_u32Number%10));
		Copy_u32Number /= 10;
	}

	while(Local_u32rev_num != 1)
	{
		Local_enuErrorState |= CLCD_InenuSendCharacter((Local_u32rev_num%10)+'0');
		Local_u32rev_num /= 10;
	}

	return Local_enuErrorState;
}


/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : CLCD_enuWritFloateNumber.                             **/
/** Return Type     : Error_State.                                          **/
/** Arguments       : Copy_f32FloatNumber                                   **/
/** Functionality   : Write any float number on lcd                         **/
/*****************************************************************************/
/*****************************************************************************/

ES_t CLCD_enuWritFloateNumber(f32 Copy_f32FloatNumber)
{
	ES_t Local_enuErrorState = ES_NOK;
	u32  Local_u32IntegerPart , Local_u32DecimalPart;
	u32  Local_u32rev_num = 1;

	Local_u32IntegerPart = (u32)Copy_f32FloatNumber;
	Local_u32DecimalPart = (u32)((Copy_f32FloatNumber - Local_u32IntegerPart)*100);

	if (Local_u32IntegerPart == 0) {
		Local_enuErrorState |= CLCD_InenuSendCharacter('0'); // Send '0' character to LCD
		return Local_enuErrorState;
	}
	while(Local_u32IntegerPart != 0)
	{
		Local_u32rev_num = ((Local_u32rev_num*10) + (Local_u32IntegerPart%10));
		Local_u32IntegerPart /= 10;
	}

	while(Local_u32rev_num != 1)
	{
		Local_enuErrorState |= CLCD_InenuSendCharacter((Local_u32rev_num%10)+'0');
		Local_u32rev_num /= 10;
	}

	CLCD_enuSendCharacter('.');
	Local_u32rev_num = 1;

	if (Local_u32DecimalPart == 0)
	{
		Local_enuErrorState |= CLCD_InenuSendCharacter('0'); // Send '0' character to LCD
		return Local_enuErrorState;
	}
	while(Local_u32DecimalPart != 0)
	{
		Local_u32rev_num = ((Local_u32rev_num*10) + (Local_u32DecimalPart%10));
		Local_u32DecimalPart /= 10;
	}

	while(Local_u32rev_num != 1)
	{
		Local_enuErrorState |= CLCD_InenuSendCharacter((Local_u32rev_num%10)+'0');
		Local_u32rev_num /= 10;
	}

	return Local_enuErrorState;
}

/************************************************************************************/
/************************************************************************************/
/** Function Name   : CLCD_enuClearDisplay.                                        **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : void                                                         **/
/** Functionality   : Clearing display                                             **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

ES_t CLCD_enuClearDisplay(void)
{
	ES_t  Local_enuErrorState = ES_NOK;

	Local_enuErrorState = CLCD_InenuSendCommand(DISPLAY_CLEAR);

	return  Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/** Function Name   : CLCD_enuCursor_OR_Display_Shift.                             **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : Copy_u8ShiftType                                             **/
/** Functionality   : Shifting Cursor or Display                                   **/
/*This function take number from 0 to 3 if this number is :                        **/
/*Zero  >> This means you want to shift Cursor to Left                             **/
/*One   >> This means you want to shift Cursor to Right                            **/
/*Two   >> This means you want to shift Display to Left                            **/
/*Three >> This means you want to shift Display to Right                           **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

ES_t CLCD_enuCursor_OR_Display_Shift(u8 Copy_u8ShiftType)
{
	ES_t  Local_enuErrorState = ES_NOK;

	if((Copy_u8ShiftType >= 0) && (Copy_u8ShiftType < 4))
	{
		switch(Copy_u8ShiftType)
		{
		case 0:  Local_enuErrorState = CLCD_InenuSendCommand(0x10); break;
		case 1:  Local_enuErrorState = CLCD_InenuSendCommand(0x14);   break;
		case 2:  Local_enuErrorState = CLCD_InenuSendCommand(0x18);   break;
		case 3:  Local_enuErrorState = CLCD_InenuSendCommand(0x1C);   break;
		}
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return  Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/** Function Name   : CLCD_enuControl_Cursor_Display.                              **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : Copy_u8State                                                 **/
/** Functionality   : Controling Display of Cursor                                 **/
/*This function take number 0 or 1 if this number is :                             **/
/*Zero  >> This means you don't want to display Cursor                             **/
/*One   >> This means you want to display Cursor                                   **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

ES_t CLCD_enuControl_Cursor_Display(u8 Copy_u8State)
{
	ES_t  Local_enuErrorState = ES_NOK;

	if(Copy_u8State == 0)
	{
		Local_enuErrorState = CLCD_InenuSendCommand(0x0C);
	}
	else if(Copy_u8State == 1)
	{
		Local_enuErrorState = CLCD_InenuSendCommand(0x0E);
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return  Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/** Function Name   : CLCD_enuControl_Cursor_Blink.                                **/
/** Return Type     : Error_State enum.                                            **/
/** Arguments       : Copy_u8State                                                 **/
/** Functionality   : Controling Blinking of Cursor                                **/
/*This function take number 0 or 1 if this number is :                             **/
/*Zero  >> This means you don't want the Cursor to blink                           **/
/*One   >> This means you want the Cursor to blink                                 **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

ES_t CLCD_enuControl_Cursor_Blink(u8 Copy_u8State)
{
	ES_t  Local_enuErrorState = ES_NOK;

	if(Copy_u8State == 0)
	{
		Local_enuErrorState = CLCD_InenuSendCommand(0x0C);
	}
	else if(Copy_u8State == 1)
	{
		Local_enuErrorState = CLCD_InenuSendCommand(0xD);
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return  Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/*        Static Function helps me to write data(data/command) on data Pins         */
/************************************************************************************/
/************************************************************************************/
static ES_t CLCD_u8Latch(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Set Read Write Pin with 0 for Write*/
	Local_enuErrorState  = DIO_enuSetPinValue(CLCD_READ_WRITE_PORT , CLCD_READ_WRITE_PIN , LOW);
	/*Clear CLCD Enable pin  */
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_ENABLE_PORT , CLCD_ENABLE_PIN , LOW);

	/*Send Command on Data Pins*/
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT7 , CLCD_DATA_PIN7 , ((Copy_u8Data>>7)&1));
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT6 , CLCD_DATA_PIN6 , ((Copy_u8Data>>6)&1));
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT5 , CLCD_DATA_PIN5 , ((Copy_u8Data>>5)&1));
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT4 , CLCD_DATA_PIN4 , ((Copy_u8Data>>4)&1));

#if CLCD_MODE == EIGHT_BIT
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT3 , CLCD_DATA_PIN3 , ((Copy_u8Data>>3)&1));
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT2 , CLCD_DATA_PIN2 , ((Copy_u8Data>>2)&1));
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT1 , CLCD_DATA_PIN1 , ((Copy_u8Data>>1)&1));
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT0 , CLCD_DATA_PIN0 , ((Copy_u8Data>>0)&1));
#elif CLCD_MODE == FOUR_BIT

	/*SET CLCD Enable pin  */
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_ENABLE_PORT , CLCD_ENABLE_PIN , HIGH);
	_delay_ms(20);
	/*Clear CLCD Enable pin  */
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_ENABLE_PORT , CLCD_ENABLE_PIN , LOW);


	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT7 , CLCD_DATA_PIN7 , ((Copy_u8Data>>3)&1));
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT6 , CLCD_DATA_PIN6 , ((Copy_u8Data>>2)&1));
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT5 , CLCD_DATA_PIN5 , ((Copy_u8Data>>1)&1));
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT4 , CLCD_DATA_PIN4 , ((Copy_u8Data>>0)&1));

#else
#error "Invalid CLCD Mode"
#endif

	/*SET CLCD Enable pin  */
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_ENABLE_PORT , CLCD_ENABLE_PIN , HIGH);
	_delay_ms(20);
	/*Clear CLCD Enable pin  */
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_ENABLE_PORT , CLCD_ENABLE_PIN , LOW);

	return  Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/*    Static inline Function helps me to Set LCD Pins Direction                     */
/************************************************************************************/
/************************************************************************************/

static inline ES_t  CLCD_InenuSetPinsDirection(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Set Control Pins as OUTPUT PINS*/
	Local_enuErrorState  = DIO_enuSetPinDirection(CLCD_REGISTER_SELECT_PORT , CLCD_REGISTER_SELECT_PIN , OUTPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(CLCD_READ_WRITE_PORT , CLCD_READ_WRITE_PIN , OUTPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(CLCD_ENABLE_PORT , CLCD_ENABLE_PIN , OUTPUT);

	/*Set DATA Pins from D7 to D4 as OUTPUT PINS*/
	Local_enuErrorState |= DIO_enuSetPinDirection(CLCD_DATA_PORT4 , CLCD_DATA_PIN4 , OUTPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(CLCD_DATA_PORT5 , CLCD_DATA_PIN5 , OUTPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(CLCD_DATA_PORT6 , CLCD_DATA_PIN6 , OUTPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(CLCD_DATA_PORT7 , CLCD_DATA_PIN7 , OUTPUT);

#if  CLCD_MODE  == EIGHT_BIT

	/*Set DATA Pins from D3 to D0 as OUTPUT PINS*/
	Local_enuErrorState |= DIO_enuSetPinDirection(CLCD_DATA_PORT0 , CLCD_DATA_PIN0 , OUTPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(CLCD_DATA_PORT1 , CLCD_DATA_PIN1 , OUTPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(CLCD_DATA_PORT2 , CLCD_DATA_PIN2 , OUTPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(CLCD_DATA_PORT3 , CLCD_DATA_PIN3 , OUTPUT);
#elif CLCD_MODE  == FOUR_BIT

#else
#error "Invalid CLCD Mode"
#endif

	return Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/*    Static inline Function helps me to Send command                               */
/************************************************************************************/
/************************************************************************************/

static inline ES_t  CLCD_InenuSendCommand(u8 Copy_u8Command)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Set Register Select Pin with 0 for command*/
	Local_enuErrorState  = DIO_enuSetPinValue(CLCD_REGISTER_SELECT_PORT , CLCD_REGISTER_SELECT_PIN , LOW);

	/*Clear CLCD Enable pin  */
	Local_enuErrorState |= DIO_enuSetPinValue(CLCD_ENABLE_PORT , CLCD_ENABLE_PIN , LOW);

	if(Copy_u8Command == FUNCTION_SET_FOUR_BIT)
	{
		/*Send Command on Data Pins*/
		Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT7 , CLCD_DATA_PIN7 , ((Copy_u8Command>>7)&1));
		Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT6 , CLCD_DATA_PIN6 , ((Copy_u8Command>>6)&1));
		Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT5 , CLCD_DATA_PIN5 , ((Copy_u8Command>>5)&1));
		Local_enuErrorState |= DIO_enuSetPinValue(CLCD_DATA_PORT4 , CLCD_DATA_PIN4 , ((Copy_u8Command>>4)&1));
		/*SET CLCD Enable pin  */
		Local_enuErrorState |= DIO_enuSetPinValue(CLCD_ENABLE_PORT , CLCD_ENABLE_PIN , HIGH);
		_delay_ms(20);
		/*Clear CLCD Enable pin  */
		Local_enuErrorState |= DIO_enuSetPinValue(CLCD_ENABLE_PORT , CLCD_ENABLE_PIN , LOW);

	}

	Local_enuErrorState |= CLCD_u8Latch(Copy_u8Command);

	return Local_enuErrorState;
}


/************************************************************************************/
/************************************************************************************/
/*    Static inline Function helps me to Sennd Character                            */
/************************************************************************************/
/************************************************************************************/

static inline ES_t  CLCD_InenuSendCharacter(u8 Copy_u8Character)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*Set Register Select Pin with 0 for Data*/
	Local_enuErrorState  = DIO_enuSetPinValue(CLCD_REGISTER_SELECT_PORT , CLCD_REGISTER_SELECT_PIN , HIGH);

	Local_enuErrorState |= CLCD_u8Latch(Copy_u8Character);

	return Local_enuErrorState;
}
