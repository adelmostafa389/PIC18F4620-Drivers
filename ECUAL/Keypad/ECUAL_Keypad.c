/* 
 * File:   ECUAL_Keypad.h
 * Author: ADEL
 *
 * Created on June 3, 2022, 5:43 PM
 */

#include "ECUAL_Keypad.h"

static const uint8 keypad_buttons[KEYPAD_ROWS][KEYPAD_COLUMNS] =
{
    {'7', '8', '9', '/'},  
    {'4', '5', '6', '*'},  
    {'1', '2', '3', '-'},  
    {'#', '0', '=', '+'}  
};

/**
 * #brief Initialize 
 * @param keypad
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HKeypad_initialize(const St_keypad_type_t* const keypad){
    Std_ReturnType error_ret = E_OK;
    uint8 rows_counter = 0;
    uint8 columns_counter = 0;
    if(NULL == keypad){ 
        error_ret = E_NOT_OK;
    }
    else{
        for(rows_counter = 0; rows_counter < KEYPAD_ROWS; rows_counter++)
        {
            error_ret = MGPIO_initialize_pin(&(keypad->keypad_row_pins[rows_counter]));
        }
        for(columns_counter = 0; columns_counter < KEYPAD_COLUMNS; columns_counter++)
        {
            error_ret = MGPIO_initialize_pin_direction(&(keypad->keypad_columns_pins[columns_counter]));
        }
    }
    return error_ret;
}

/**
 * #brief 
 * @param keypad
 * @param value
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HKeypad_get_value(const St_keypad_type_t* const keypad, uint8* value){
    Std_ReturnType error_ret = E_OK;
    uint8 rows_counter = 0;
    uint8 rows_init_zero_counter = 0;
    uint8 columns_counter = 0;
    En_logic_t column_logic = 0;
    if(NULL == keypad){
        error_ret = E_NOT_OK;
    }
    else{
        for(rows_counter = 0; rows_counter < KEYPAD_ROWS; rows_counter++){
            for(rows_init_zero_counter = 0; rows_init_zero_counter < KEYPAD_ROWS; rows_init_zero_counter++){
                error_ret = MGPIO_write_pin(&(keypad->keypad_row_pins[rows_init_zero_counter]), LOW);
            }
            MGPIO_write_pin(&(keypad->keypad_row_pins[rows_counter]), HIGH);
            for(columns_counter = 0; columns_counter < KEYPAD_ROWS; columns_counter++){
                error_ret = MGPIO_read_pin(&(keypad->keypad_columns_pins[columns_counter]), &column_logic);
                if(HIGH == column_logic){
                    *value = keypad_buttons[rows_counter][columns_counter];
                }
                else{
                    /* Do nothing */
                }
            }
        }
    }
    return error_ret;
}
