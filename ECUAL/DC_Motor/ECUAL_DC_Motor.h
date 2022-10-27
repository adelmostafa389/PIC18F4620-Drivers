/* 
 * File:   ECUAL_Motor.h
 * Author: ADEL
 *
 * Created on June 2, 2022, 2:30 PM
 */


#ifndef ECUAL_MOTOR_H
#define	ECUAL_MOTOR_H


/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "ECUAL_DC_Motor_config.h"
#include "../../MCAL/GPIO/MCAL_GPIO.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/
#define DC_MOTOR_ON_STATUS    0x01U
#define DC_MOTOR_OFF_STATUS   0x00U

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef struct{
    St_pin_config_t motor_pin_1;
    St_pin_config_t motor_pin_2;
}St_dc_motor_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/
Std_ReturnType HDC_MOTOR_initialize(const St_dc_motor_t* const dcMotor);
Std_ReturnType HDC_MOTOR_move_forward(const St_dc_motor_t* const dcMotor);
Std_ReturnType HDC_MOTOR_move_backward(const St_dc_motor_t* const dcMotor);
Std_ReturnType HDC_MOTOR_stop(const St_dc_motor_t* const dcMotor);


#endif	/* ECUAL_MOTOR_H */

