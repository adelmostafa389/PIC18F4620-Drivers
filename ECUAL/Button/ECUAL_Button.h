/* 
 * File:   ECUAL_Button.h
 * Author: ADEL
 *
 * Created on May 31, 2022, 10:05 PM
 */

#ifndef ECUAL_BUTTON_H
#define	ECUAL_BUTTON_H


/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "../../MCAL/GPIO/MCAL_GPIO.h"
#include "ECUAL_Button_config.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/
typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED
}En_button_state_t;

typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}En_button_connection_t;

typedef struct{
    St_pin_config_t button_pin;
    En_button_connection_t button_connection;
    En_button_state_t button_state;
}St_button_t;


/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/
Std_ReturnType HBUTTON_initialize(const St_button_t* button);
Std_ReturnType HBUTTON_read(const St_button_t* button, En_button_state_t* buttonState);

#endif	/* ECUAL_BUTTON_H */

