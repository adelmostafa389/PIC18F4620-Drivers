/* 
 * File:   ECUAL_Keypad.h
 * Author: ADEL
 *
 * Created on June 3, 2022, 5:43 PM
 */

#ifndef ECUAL_KEYPAD_H
#define	ECUAL_KEYPAD_H


/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "../../MCAL/GPIO/MCAL_GPIO.h"
#include "ECUAL_Keypad_config.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

#define KEYPAD_ROWS     4
#define KEYPAD_COLUMNS  4

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/
typedef struct{
    St_pin_config_t keypad_row_pins[KEYPAD_ROWS];
    St_pin_config_t keypad_columns_pins[KEYPAD_COLUMNS];
}St_keypad_type_t;


/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/
Std_ReturnType HKeypad_initialize(const St_keypad_type_t* const keypad);
Std_ReturnType HKeypad_get_value(const St_keypad_type_t* const keypad, uint8* value);


#endif	/* ECUAL_KEYPAD_H */

