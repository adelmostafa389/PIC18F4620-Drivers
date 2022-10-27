/* 
 * File:   MCAL_CCP2.h
 * Author: ADEL
 *
 * Created on June 21, 2022, 10:48 AM
 */

#ifndef MCAL_CCP2_H
#define	MCAL_CCP2_H


/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include <xc.h>
#include "../MCAL_STD_TYPES.h"
#include "../GPIO/MCAL_GPIO.h"
#include "../Interrupt/MCAL_interanl_Interrupt.h"
#include "../MCAL_CCP_config.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

/* Disable CPP2 module */
#define CCP2_MODULE_DISABLE_MODE                  ((uint8)0x00)
/* CPP2 COMPARE modes */
#if CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECT
#define CCP2_COMPARE_MODE                         ((uint8)0x02)
#define CCP2_COMPARE_MODE_INIT_PIN_LOW            ((uint8)0x08)
#define CCP2_COMPARE_MODE_INIT_PIN_HIGH           ((uint8)0x09)
#define CCP2_COMPARE_MODE_GEN_SW_INTERRUPT        ((uint8)0x0A)
#define CCP2_COMPARE_MODE_GEN_EVENT               ((uint8)0x0B)
/* CPP2 CAPTURE modes */
#elif CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECT
#define CCP2_CAPTURE_MODE_1_FALLING_EDGE          ((uint8)0x04)
#define CCP2_CAPTURE_MODE_1_RISING_EDGE           ((uint8)0x05)
#define CCP2_CAPTURE_MODE_4_RISING_EDGE           ((uint8)0x06) 
#define CCP2_CAPTURE_MODE_16_RISING_EDGE          ((uint8)0x07)
/* CPP2 PWM modes */
#elif CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECT
#define CCP2_PWM_MODE                             ((uint8)0x0C)
#endif
    

/* CCP2 module capture mode state*/
#define CCP2_CAPTURE_NOT_READY                    0x00
#define CCP2_CAPTURE_READY                        0x01

/* CCP2 module compare mode state*/
#define CCP2_COMPARE_NOT_READY                    0x00
#define CCP2_COMPARE_READY                        0x01

#define CCP2_TIMER2_PRESCALER_DIV_BY_1            0x01
#define CCP2_TIMER2_PRESCALER_DIV_BY_4            0x01
#define CCP2_TIMER2_PRESCALER_DIV_BY_16           0x01



/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

#define CCP2_DISABLE_MODULE()                (CCP2CONbits.CCP2M = CCP2_MODULE_DISABLE_MODE)

#define CCP2_SELECT_MODE(mode)                (CCP2CONbits.CCP2M = mode)

#define CCP2_SET_PWM_DUTY_CYCLE(duty_cycle)   (CCP2CONbits.DC2B = duty_cycle)

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/
typedef struct{
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    En_interrupt_priority_t interrupt_priority;
#endif
#endif
    St_pin_config_t ccp_pin;
    uint8 timer2_prescaler_value;
    uint8 mode;
#if CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECT

#elif CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECT
    En_CCP_Timer_source_select_t cpp_timer_select;

#elif CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECT
    uint32 PWM_frequency;
#endif
}St_CCP2_cfg_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

Std_ReturnType MCCP2_init(const St_CCP2_cfg_t* ccp2_cfg);
Std_ReturnType MCCP2_deinit(const St_CCP2_cfg_t* ccp2_cfg);

#if CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECT
Std_ReturnType MCCP2_is_compare_ready(uint8* compare_isReady);
Std_ReturnType MCCP2_set_value_to_compare(uint16 ccp2_compareValue);

#elif CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECT
Std_ReturnType MCCP2_is_capture_ready(uint8* capture_isReady);
Std_ReturnType MCCP2_read_capture_value(uint16* ccp2_captureValue);

#elif CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECT
Std_ReturnType MCCP2_set_PWM_duty_cycle(uint8 duty_value);
Std_ReturnType MCCP2_start_PWM(void);
Std_ReturnType MCCP2_stop_PWM(void);
#endif


#endif	/* MCAL_CCP2_H */

