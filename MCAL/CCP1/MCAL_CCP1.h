/* 
 * File:   MCAL_CCP1.h
 * Author: ADEL
 *
 * Created on June 20, 2022, 11:04 AM
 */

#ifndef MCAL_CCP1_H
#define	MCAL_CCP1_H

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

/* Disable CPP1 module */
#define CCP1_MODULE_DISABLE_MODE                  ((uint8)0x00)
/* CPP1 COMPARE modes */
#if CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECT
#define CCP1_COMPARE_MODE                         ((uint8)0x02)
#define CCP1_COMPARE_MODE_INIT_PIN_LOW            ((uint8)0x08)
#define CCP1_COMPARE_MODE_INIT_PIN_HIGH           ((uint8)0x09)
#define CCP1_COMPARE_MODE_GEN_SW_INTERRUPT        ((uint8)0x0A)
#define CCP1_COMPARE_MODE_GEN_EVENT               ((uint8)0x0B)
/* CPP1 CAPTURE modes */
#elif CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECT
#define CCP1_CAPTURE_MODE_1_FALLING_EDGE          ((uint8)0x04)
#define CCP1_CAPTURE_MODE_1_RISING_EDGE           ((uint8)0x05)
#define CCP1_CAPTURE_MODE_4_RISING_EDGE           ((uint8)0x06) 
#define CCP1_CAPTURE_MODE_16_RISING_EDGE          ((uint8)0x07)
/* CPP1 PWM modes */
#elif CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECT
#define CCP1_PWM_MODE                             ((uint8)0x0C)
#endif
    

/* CCP1 module capture mode state*/
#define CCP1_CAPTURE_NOT_READY                    0x00
#define CCP1_CAPTURE_READY                        0x01

/* CCP1 module compare mode state*/
#define CCP1_COMPARE_NOT_READY                    0x00
#define CCP1_COMPARE_READY                        0x01

#define CCP1_TIMER2_PRESCALER_DIV_BY_1            0x01
#define CCP1_TIMER2_PRESCALER_DIV_BY_4            0x01
#define CCP1_TIMER2_PRESCALER_DIV_BY_16           0x01

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

#define CCP1_DISABLE_MODULE()                (CCP1CONbits.CCP1M = CCP1_MODULE_DISABLE_MODE)

#define CCP1_SELECT_MODE(mode)                (CCP1CONbits.CCP1M = mode)

#define CCP1_SET_PWM_DUTY_CYCLE(duty_cycle)   (CCP1CONbits.DC1B = duty_cycle)

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef struct{
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    En_interrupt_priority_t interrupt_priority;
#endif
#endif
    St_pin_config_t ccp_pin;
    uint8 timer2_prescaler_value;
    uint8 mode;
#if CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECT

#elif CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECT
    En_CCP_Timer_source_select_t cpp_timer_select;
#elif CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECT
    uint32 PWM_frequency;
#endif
}St_CCP1_cfg_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

Std_ReturnType MCCP1_init(const St_CCP1_cfg_t* ccp1_cfg);
Std_ReturnType MCCP1_deinit(const St_CCP1_cfg_t* ccp1_cfg);

#if CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECT
Std_ReturnType MCCP1_is_compare_ready(uint8* compare_isReady);
Std_ReturnType MCCP1_set_value_to_compare(uint16 ccp1_compareValue);

#elif CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECT
Std_ReturnType MCCP1_is_capture_ready(uint8* capture_isReady);
Std_ReturnType MCCP1_read_capture_value(uint16* ccp1_captureValue);

#elif CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECT
Std_ReturnType MCCP1_set_PWM_duty_cycle(uint8 duty_value);
Std_ReturnType MCCP1_start_PWM(void);
Std_ReturnType MCCP1_stop_PWM(void);
#endif

    

#endif	/* MCAL_CCP1_H */

