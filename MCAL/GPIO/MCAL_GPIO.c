/* 
 * File:   MCAL_GPIO.c
 * Author: Adel Mostafa Kamel Helal
 *
 * Created on May 27, 2022, 3:23 PM
 */

#include "MCAL_GPIO.h"

volatile  uint8 *Arr_tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile  uint8 *Arr_lat_registers[]  = {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile  uint8 *Arr_port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/* Check if the GPIO port pin configuration functions is enabled or not*/
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
/* GPIO port pin configuration functions definitions Section */
/**
 * 
 * @param _pin_config
 * @return status of the function
 *             (E_OK) : The function is done successfully
 *             (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MGPIO_initialize_pin_direction(const St_pin_config_t* _pin_config){
    Std_ReturnType error_ret = E_OK;
    if(NULL == _pin_config || (_pin_config->pin > (PORT_MAX_PIN_NUM - 1))){
        error_ret = E_NOT_OK;
    }
    else{
       switch(_pin_config->direction){
            case OUTPUT:
                CLEAR_BIT(*Arr_tris_registers[_pin_config->port], _pin_config->pin);
                break;
            case INPUT:
                SET_BIT(*Arr_tris_registers[_pin_config->port], _pin_config->pin);
                break;
            default:
                error_ret = E_NOT_OK;
                break;
        } 
    }
    return error_ret;
}

/**
 * 
 * @param _pin_config
 * @param direction_status
 * @return status of the function
 *             (E_OK) : The function is done successfully
 *             (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MGPIO_get_pin_direction(const St_pin_config_t* _pin_config, En_direction_t* direction_status){
    Std_ReturnType error_ret = E_OK;
    if((NULL == _pin_config)||(NULL == direction_status) || (_pin_config->pin > (PORT_MAX_PIN_NUM - 1))){
        error_ret = E_NOT_OK;
    }
    else{
        *direction_status = READ_BIT(*Arr_tris_registers[_pin_config->port], _pin_config->pin);
    }
    return error_ret;
}

/**
 * 
 * @param _pin_config
 * @param logic
 * @return status of the function
 *             (E_OK) : The function is done successfully
 *             (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MGPIO_write_pin(const St_pin_config_t* _pin_config, En_logic_t logic){
    Std_ReturnType error_ret = E_OK;
    if(NULL == _pin_config || (_pin_config->pin > (PORT_MAX_PIN_NUM - 1))){
        error_ret = E_NOT_OK;
    }
    else{
            switch(logic){
            case LOW:
                CLEAR_BIT(*Arr_lat_registers[_pin_config->port], _pin_config->pin);
                //_pin_config->logic = HIGH;
                break;
            case HIGH:
                SET_BIT(*Arr_lat_registers[_pin_config->port], _pin_config->pin);
                //_pin_config->logic = LOW;
                break;
            default:
                error_ret = E_NOT_OK;
                break;
        } 
    } 
    return error_ret;
}

/**
 * 
 * @param _pin_config
 * @param logic
 * @return status of the function
 *             (E_OK) : The function is done successfully
 *             (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MGPIO_read_pin(const St_pin_config_t* _pin_config, En_logic_t* logic){
    Std_ReturnType error_ret = E_OK;
    if((NULL == _pin_config) || (NULL == logic) || (_pin_config->pin > (PORT_MAX_PIN_NUM - 1))){
        error_ret = E_NOT_OK;
    }
    else{
        *logic = READ_BIT(*Arr_port_registers[_pin_config->port], _pin_config->pin);
    }
    return error_ret;
}

/**
 * 
 * @param _pin_config
 * @return status of the function
 *             (E_OK) : The function is done successfully
 *             (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MGPIO_toggle_pin(const St_pin_config_t* _pin_config){
    Std_ReturnType error_ret = E_OK;
    if(NULL == _pin_config || (_pin_config->pin > (PORT_MAX_PIN_NUM - 1))){
        error_ret = E_NOT_OK;
    }
    else{
        TOGGLE_BIT(*Arr_lat_registers[_pin_config->port], _pin_config->pin); 
    }
    return error_ret;
}

/**
 * 
 * @param _pin_config
 * @return status of the function
 *             (E_OK) : The function is done successfully
 *             (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MGPIO_initialize_pin(const St_pin_config_t* _pin_config){
    Std_ReturnType error_ret = E_OK;
    if(NULL == _pin_config || (_pin_config->pin > (PORT_MAX_PIN_NUM - 1))){
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = MGPIO_initialize_pin_direction(_pin_config);
        error_ret = MGPIO_write_pin(_pin_config, _pin_config->initial_value);
    }
    return error_ret;
}

#endif  /* GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE */

/* Check if the GPIO port configuration functions is enabled or not*/
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
/* GPIO port configuration functions definitions Section */
/**
 * 
 * @param port
 * @param direction
 * @return status of the function
 *             (E_OK) : The function is done successfully
 *             (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MGPIO_initialize_port_direction(En_port_index_t port, uint8 direction){
    Std_ReturnType error_ret = E_OK;
    if(port > (MAX_PORT_NUM - 1)){
        error_ret = E_NOT_OK;
    }
    else{
        *Arr_tris_registers[port] = direction;
    }
    return error_ret;
}

/**
 * 
 * @param port
 * @param direction_status
 * @return status of the function
 *             (E_OK) : The function is done successfully
 *             (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MGPIO_get_port_direction(En_port_index_t port, uint8* direction_status){
    Std_ReturnType error_ret = E_OK;
    if(NULL == direction_status || (port > (MAX_PORT_NUM - 1))){
        error_ret = E_NOT_OK;
    }
    else{
        *direction_status = *Arr_tris_registers[port];
    }
    return error_ret;
}

/**
 * 
 * @param port
 * @param logic
 * @return status of the function
 *             (E_OK) : The function is done successfully
 *             (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MGPIO_write_port(En_port_index_t port, En_logic_t logic){
    Std_ReturnType error_ret = E_OK;
    if(port > (MAX_PORT_NUM - 1)){
        error_ret = E_NOT_OK;
    }
    else{
        *Arr_lat_registers[port] = logic;
    }
    return error_ret;
}

/**
 * 
 * @param port
 * @param logic
 * @return status of the function
 *             (E_OK) : The function is done successfully
 *             (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MGPIO_read_port(En_port_index_t port, En_logic_t* logic){
    Std_ReturnType error_ret = E_OK;
    if(NULL == logic || port > (MAX_PORT_NUM - 1)){
        error_ret = E_NOT_OK;
    }
    else{
        *logic = *Arr_lat_registers[port];
    }
    return error_ret;
}

/**
 * @brief Toggle all pins in the port
 * @param port
 * @return status of the function
 *             (E_OK) : The function is done successfully
 *             (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MGPIO_toggle_port(En_port_index_t port){
    Std_ReturnType error_ret = E_OK;
    if(port > (MAX_PORT_NUM - 1)){
        error_ret = E_NOT_OK;
    }
    else{
        *Arr_lat_registers[port] ^= 0xFF;  /* 0xFF Is a mask to toggle all pins in the port */
    }
    return error_ret;
}



#endif  /* GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE */
