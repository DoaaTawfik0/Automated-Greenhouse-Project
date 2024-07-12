/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  HAL           ***************/
/**************   SWC:    DC_Motor      ***************/
/**************   Version: 1.00         ***************/
/******************************************************/
/******************************************************/


#ifndef   DC_MOTOR_INTERFACE_H_
#define   DC_MOTOR_INTERFACE_H_


#include "DC_Motor_Config.h"

#define     MOTOR_NUM       3

ES_t   DC_MOTOR_enuInitialize(DC_MOTOR_t *Copy_PStrMotorConfig);

ES_t   DC_MOTOR_enuTurnRight(DC_MOTOR_t *Copy_PStrMotor_ID);
ES_t   DC_MOTOR_enuTurnLeft(DC_MOTOR_t *Copy_PStrMotor_ID);
ES_t   DC_MOTOR_enuStop(DC_MOTOR_t *Copy_PStrMotor_ID);



#endif
