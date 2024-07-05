/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  HAL           ***************/
/**************   SWC:    CLCD          ***************/
/**************   Version: 2.00         ***************/
/******************************************************/
/******************************************************/

#ifndef   CLCD_INTERFACE_H_
#define   CLCD_INTERFACE_H_


ES_t  CLCD_enuInitialize(void);

ES_t  CLCD_enuSendCommand(u8 Copy_u8Command);

ES_t  CLCD_enuSendCharacter(u8 Copy_u8Character);

ES_t CLCD_enuSendString(const char* Copy_pcString);

ES_t CLCD_enuGoToXY(u8 Copy_u8XPosition  , u8 Copy_u8YPosition);

ES_t CLCD_enuWriteSpecialCharacter(u8* Copy_pu8Pattern , u8 Copy_u8PatternNumber , u8 Copy_u8XPosition  , u8 Copy_u8YPosition);

ES_t CLCD_enuWriteNumber(u32 Copy_u32Number);

ES_t CLCD_enuClearDisplay(void);
ES_t CLCD_enuCursor_OR_Display_Shift(u8 Copy_u8ShiftType);
ES_t CLCD_enuControl_Cursor_Display(u8 Copy_u8State);
ES_t CLCD_enuControl_Cursor_Blink(u8 Copy_u8State);

/*****************************************/







#endif
