/* 
 * File:   ECUAL_Motor.c
 * Author: ADEL
 *
 * Created on June 2, 2022, 2:30 PM
 */


#include "ECUAL_DC_Motor.h"
 
/**
 * #brief Initialize the two pins assigned to the motor direction to OUTPUT 
 *        with the initial value defined in the dcMotor definition.
 * @param dcMotor
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HDC_MOTOR_initialize(const St_dc_motor_t* const dcMotor){
    Std_ReturnType error_ret = E_OK;
    if(NULL == dcMotor){
        error_ret = E_NOT_OK;
    }
    else{
        
        MGPIO_initialize_pin(&(dcMotor->motor_pin_1));
        MGPIO_initialize_pin(&(dcMotor->motor_pin_2));
    }
    return error_ret;
}

/**
 * #brief Drive the motor to rotate right
 * @param dcMotor
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HDC_MOTOR_move_forward(const St_dc_motor_t* const dcMotor){
    Std_ReturnType error_ret = E_OK;
    if(NULL == dcMotor){
        error_ret = E_NOT_OK;
    }
    else{
        MGPIO_write_pin(&(dcMotor->motor_pin_1), HIGH);
        MGPIO_write_pin(&(dcMotor->motor_pin_2), LOW);
    }
    return error_ret;
}

/**
 * #brief Drive the motor to rotate left
 * @param dcMotor
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HDC_MOTOR_move_backward(const St_dc_motor_t* const dcMotor){
    Std_ReturnType error_ret = E_OK;
    if(NULL == dcMotor){
        error_ret = E_NOT_OK;
    }
    else{
        MGPIO_write_pin(&(dcMotor->motor_pin_1), LOW);
        MGPIO_write_pin(&(dcMotor->motor_pin_2), HIGH);
    }
    return error_ret;
}

/**
 * #brief Stop the DC motor by applying logic 0 on its two pins
 * @param dcMotor
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue while execution
 */
Std_ReturnType HDC_MOTOR_stop(const St_dc_motor_t* const dcMotor){
    Std_ReturnType error_ret = E_OK;
    if(NULL == dcMotor){
        error_ret = E_NOT_OK;
    }
    else{
        MGPIO_write_pin(&(dcMotor->motor_pin_1), LOW);
        MGPIO_write_pin(&(dcMotor->motor_pin_2), LOW);
    }
    return error_ret;
}

