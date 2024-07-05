/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  HAL           ***************/
/**************   SWC:    DC_Motor      ***************/
/**************   Version: 1.00         ***************/
/******************************************************/
/******************************************************/

#include  "../../LIB/STD_TYPES.h"
#include  "../../LIB/ERROR_STATE.h"
#include  "../../LIB/BIT_MATH.h"

#include  "../../MCAL/DIO/DIO_Interface.h"

#include  "DC_Motor_Config.h"
#include  "DC_Motor_Private.h"
#include  "DC_Motor_Interface.h"


DC_MOTOR_t  DC_MOTOR_AStrConfig[MOTOR_NUM] =
{
		{.DC_MOTOR_IN1_PORT =  DIO_PORTA , .DC_MOTOR_IN1_PIN =  DIO_PIN0 , .DC_MOTOR_IN2_PORT = DIO_PORTA ,
				.DC_MOTOR_IN2_PIN = DIO_PIN1 , .DC_MOTOR_ENABLE_PORT = DIO_PORTA , .DC_MOTOR_ENABLE_PIN = DIO_PIN2 ,
				.DC_MOTOR_ENABLE_STATE = ACTIVATED
		} ,
		{.DC_MOTOR_IN1_PORT =  DIO_PORTB , .DC_MOTOR_IN1_PIN =  DIO_PIN0 , .DC_MOTOR_IN2_PORT = DIO_PORTB ,
				.DC_MOTOR_IN2_PIN = DIO_PIN1 , .DC_MOTOR_ENABLE_PORT = DIO_PORTB , .DC_MOTOR_ENABLE_PIN = DIO_PIN2 ,
				.DC_MOTOR_ENABLE_STATE = ACTIVATED
		}
};
