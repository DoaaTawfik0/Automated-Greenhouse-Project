/*******************************************************/
/*******************************************************/
/**************   Author: Doaa Tawfik    ***************/
/**************   Layer:  HAL            ***************/
/**************   SWC:    SOIL_MOISTURE  ***************/
/**************   Version: 1.00          ***************/
/*******************************************************/
/*******************************************************/


#ifndef  SOIL_MOISTURE_INTERFACE_H_
#define  SOIL_MOISTURE_INTERFACE_H_


ES_t  SoilMoisture_enuInitialize(void);


ES_t  SoilMoisture_enuGetPercentage(u8 Copy_u8Channel_ID  , u8* Copy_pu8RetValue);


#endif
