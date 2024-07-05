/*****************************************************/
/*****************************************************/
/**************   Author: Doaa Tawfik  ***************/
/**************   Layer: MCAL          ***************/
/**************   SWC: Port            ***************/
/**************   Version: 1.00        ***************/
/*****************************************************/
/*****************************************************/

#include "../../LIB/ERROR_STATE.h"
#include "../../LIB/STD_TYPES.h"

#include "Port_Config.h"
#include "Port_Interface.h"
#include "Port_Private.h"
#include "Port_Register.h"




/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : PORT_voidInit.                                          **/
/** Return Type     : Void.                                    **/
/** Arguments       : void.                                                 **/
/** Functionality   : Setting initial Direction & value for MicroController Pins. **/
/*****************************************************************************/
/*****************************************************************************/
void PORT_voidInit(void)
{
	/*
	 * Setting Direction for PORT A,B,C,D
	 */
    DDRA = PORTA_DIR;
    DDRB = PORTB_DIR;
    DDRC = PORTC_DIR;
    DDRD = PORTD_DIR;

    /*
     * Setting Initial Values For PORT A,B,C,D
     */

    PORTA = PORTA_INITIAL_VALUE;
    PORTB = PORTB_INITIAL_VALUE;
    PORTC = PORTC_INITIAL_VALUE;
    PORTD = PORTD_INITIAL_VALUE;


}
