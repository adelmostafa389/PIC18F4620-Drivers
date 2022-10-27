/* 
 * File:   MCAL_Timer3.h
 * Author: ADEL
 *
 * Created on June 18, 2022, 2:59 PM
 */

#ifndef MCAL_TIMER3_H
#define	MCAL_TIMER3_H

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include <xc.h>
#include "../MCAL_STD_TYPES.h"
#include "../GPIO/MCAL_GPIO.h"
#include "../Interrupt/MCAL_interanl_Interrupt.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

#define TIMER3_SYNC_EXT_CLK_INPUT_DISABLE 1
#define TIMER3_SYNC_EXT_CLK_INPUT_ENABLE  0

#define TIMER3_COUNTER_MODE               1
#define TIMER3_TIMER_MODE                 0

#define TIMER3_OSC_ENABLE                 1
#define TIMER3_OSC_DISABLE                0

#define TIMER3_RW_16Bit_MODE              1
#define TIMER3_RW_8Bit_MODE               0

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

#define TIMER3_ENABLE_MODULE()                                (T3CONbits.TMR3ON = 1)
#define TIMER3_DISABLE_MODULE()                               (T3CONbits.TMR3ON = 0)

#define TIMER3_SELECT_PRESCALER(prescaler)                    (T3CONbits.T3CKPS = prescaler)

#define TIMER3_SELECT_MODE(timer3_mode)                       (T3CONbits.TMR3CS = timer3_mode)

/* Enable/Disable external clock synchronization with the clock source oscillator (In case of counter mode) */
#define TIMER3_SELECT_COUNTER_SYNCHRONIZATION(timer3_sync)    (T3CONbits.T3SYNC = timer3_sync) 

#define TIMER3_SELECT_RW_MODE(rw_mode)                               (T3CONbits.RD16 = rw_mode)

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef enum{
    TIMER3_PRESCALER_DIV_BY_1 = 0,
    TIMER3_PRESCALER_DIV_BY_2,
    TIMER3_PRESCALER_DIV_BY_4,
    TIMER3_PRESCALER_DIV_BY_8,
}En_timer3_prescaler_select_t;

typedef struct{
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    PtrTo_func_t InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    En_interrupt_priority_t interrupt_priority;
#endif
#endif
    uint16 preloaded_value;
    En_timer3_prescaler_select_t prescaler_value;
    uint8 register_rw_mode : 1;
    uint8 counter_sync : 1;
    uint8 mode : 1;
    uint8 reserved : 4;
}St_timer3_conf_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/
Std_ReturnType MTimer3_init(St_timer3_conf_t* timer3_cfg);
Std_ReturnType MTimer3_deinit(St_timer3_conf_t* timer3_cfg);
Std_ReturnType MTimer3_write_value(St_timer3_conf_t* timer3_cfg, uint16 value);
Std_ReturnType MTimer3_read_value(St_timer3_conf_t* timer3_cfg, uint16* value);

#endif	/* MCAL_TIMER3_H */



