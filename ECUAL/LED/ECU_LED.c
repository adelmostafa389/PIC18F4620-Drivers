/* 
 * File:   ECU_LED.c
 * Author: ADEL
 *
 * Created on May 27, 2022, 4:30 PM
 */

#include "ECU_LED.h"

/**
 * @brief Initialize the assigned pin to be output and turn the LED off
 * @param led
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HLED_initialize(const St_led_t *led){
    Std_ReturnType error_ret = E_OK;
    if(NULL == led || (led->pin > (PORT_MAX_PIN_NUM - 1))){
        error_ret = E_NOT_OK;
    }
    else{
       St_pin_config_t pinConfig = {
            .port = led->port,
            .pin = led->pin,
            .direction = OUTPUT,
            .initial_value = LOW
        };
        error_ret = MGPIO_initialize_pin(&pinConfig);
    }
    return error_ret;
}  

/**
 * @brief Turn the LED on
 * @param led
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HLED_turn_on(const St_led_t *led){
    Std_ReturnType error_ret = E_OK;
    if(NULL == led || (led->pin > (PORT_MAX_PIN_NUM - 1))){
        error_ret = E_NOT_OK;
    }
    else{
       St_pin_config_t pinConfig = {
            .port = led->port,
            .pin = led->pin,
            .direction = OUTPUT,
            .initial_value = led->led_initial_status
        };
        error_ret = MGPIO_write_pin(&pinConfig, HIGH);
    }
    return error_ret;
}

/**
 * @brief Turn the LED off
 * @param led
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HLED_turn_off(const St_led_t *led){
    Std_ReturnType error_ret = E_OK;
    if(NULL == led || (led->pin > (PORT_MAX_PIN_NUM - 1))){
        error_ret = E_NOT_OK;
    }
    else{
       St_pin_config_t pinConfig = {
            .port = led->port,
            .pin = led->pin,
            .direction = OUTPUT,
            .initial_value = led->led_initial_status
        };
        error_ret = MGPIO_write_pin(&pinConfig, LOW);
    }
    return error_ret;
}

/**
 * @brief Toggle the LED state
 * @param led
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HLED_toggle(const St_led_t *led){
    Std_ReturnType error_ret = E_OK;
    if(NULL == led || (led->pin > (PORT_MAX_PIN_NUM - 1))){
        error_ret = E_NOT_OK;
    }
    else{
       St_pin_config_t pinConfig = {
            .port = led->port,
            .pin = led->pin,
            .direction = OUTPUT,
            .initial_value = led->led_initial_status
        };
        error_ret = MGPIO_toggle_pin(&pinConfig);
    }
    return error_ret;
}
