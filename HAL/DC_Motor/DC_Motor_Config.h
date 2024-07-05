/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  HAL           ***************/
/**************   SWC:    DC_Motor      ***************/
/**************   Version: 1.00         ***************/
/******************************************************/
/******************************************************/


#ifndef   DC_MOTOR_CONFIG_H_
#define   DC_MOTOR_CONFIG_H_


typedef  struct{

	u8 DC_MOTOR_IN1_PORT;
	u8 DC_MOTOR_IN1_PIN;
	u8 DC_MOTOR_IN2_PORT;
	u8 DC_MOTOR_IN2_PIN;
	u8 DC_MOTOR_ENABLE_PORT;
	u8 DC_MOTOR_ENABLE_PIN;
	u8 DC_MOTOR_ENABLE_STATE;

}DC_MOTOR_t;


#endif
