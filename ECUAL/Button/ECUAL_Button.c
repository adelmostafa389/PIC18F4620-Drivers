/* 
 * File:   ECUAL_Button.c
 * Author: ADEL
 *
 * Created on May 31, 2022, 10:05 PM
 */

#include "ECUAL_Button.h"


/**
 * @brief initialize the related pin to be input
 * @param button
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HBUTTON_initialize(const St_button_t* button){
    Std_ReturnType error_ret = E_OK;
    if(NULL == button){
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = MGPIO_initialize_pin_direction(&(button->button_pin));
    }
    return error_ret;
}

/**
 * @brief Read the state of the button and pass it to (*buttonState)
 * @param button
 * @param buttonState
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HBUTTON_read(const St_button_t* button, En_button_state_t* buttonState){
    Std_ReturnType error_ret = E_OK;
    En_logic_t pinStatus = LOW;
    if((NULL == button) || (NULL == buttonState)){
        error_ret = E_NOT_OK;
    }
    else{
         error_ret = MGPIO_read_pin(&(button->button_pin), &pinStatus);
         if(BUTTON_ACTIVE_HIGH == button->button_connection){
             if(HIGH == pinStatus){
                 *buttonState = BUTTON_PRESSED;
             }
             else{
                 *buttonState = BUTTON_RELEASED;
             }
        }
        else if(BUTTON_ACTIVE_LOW == button->button_connection){
            if(HIGH == pinStatus){
                 *buttonState = BUTTON_RELEASED;
             }
             else{
                 *buttonState = BUTTON_PRESSED;
             }
        }
        else{
            error_ret = E_NOT_OK;
        }
    }
    return error_ret;
}