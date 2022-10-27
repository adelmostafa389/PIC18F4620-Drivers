/* 
 * File:   ECUAL_Relay.c
 * Author: ADEL
 *
 * Created on June 2, 2022, 3:20 AM
 */

#include "ECUAL_Relay.h"

/**
 * @brief Initialize the relay assigned pin to output with initial logic
 * @param relay
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HRelay_initialize(const St_relay_t* relay){
    Std_ReturnType error_ret = E_OK;
    if(NULL == relay){
        error_ret = E_NOT_OK;
    }
    else{
        St_pin_config_t relayPin = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = OUTPUT,
            .initial_value = relay->relay_initial_status
        };
        error_ret = MGPIO_initialize_pin(&relayPin);
    }
    return error_ret;
}

/**
 * @brief Turn on the relay
 * @param relay
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HRelay_turn_on(const St_relay_t* relay){
     Std_ReturnType error_ret = E_OK;
    if(NULL == relay){
        error_ret = E_NOT_OK;
    }
    else{
        St_pin_config_t relayPin = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = OUTPUT,
            .initial_value = relay->relay_initial_status
        };
        error_ret = MGPIO_write_pin(&relayPin, HIGH);
    }
    return error_ret;
}

/**
 * @brief Turn off the relay
 * @param relay
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HRelay_turn_off(const St_relay_t* relay){
     Std_ReturnType error_ret = E_OK;
    if(NULL == relay){
        error_ret = E_NOT_OK;
    }
    else{
        St_pin_config_t relayPin = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = OUTPUT,
            .initial_value = relay->relay_initial_status
        };
        error_ret = MGPIO_write_pin(&relayPin, LOW);
    }
    return error_ret;
}  