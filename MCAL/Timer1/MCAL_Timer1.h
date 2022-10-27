/* 
 * File:   MCAL_Timer0.h
 * Author: ADEL
 *
 * Created on June 17, 2022, 4:08 PM
 */

#ifndef MCAL_TIMER1_H
#define	MCAL_TIMER1_H

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

#define TIMER1_SYNC_EXT_CLK_INPUT_DISABLE 1
#define TIMER1_SYNC_EXT_CLK_INPUT_ENABLE  0

#define TIMER1_COUNTER_MODE               1
#define TIMER1_TIMER_MODE                 0

#define TIMER1_OSC_ENABLE                 1
#define TIMER1_OSC_DISABLE                0

#define TIMER1_RW_16Bit_MODE              1
#define TIMER1_RW_8Bit_MODE               0

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

#define TIMER1_ENABLE_MODULE()                                (T1CONbits.TMR1ON = 1)
#define TIMER1_DISABLE_MODULE()                               (T1CONbits.TMR1ON = 0)

#define TIMER1_SELECT_PRESCALER(prescaler)                    (T1CONbits.T1CKPS = prescaler)

#define TIMER1_SELECT_MODE(timer1_mode)                       (T1CONbits.TMR1CS = timer1_mode)

/* Enable/Disable TIMER1 oscillator connected to pins (RC0 "T1OS0" & RC1 "T1OS1") */
#define TIMER1_ENABLE_OSC()                                   (T1CONbits.T1OSCEN = TIMER1_OSC_ENABLE)
#define TIMER1_DISABLE_OSC()                                  (T1CONbits.T1OSCEN = TIMER1_OSC_DISABLE) 
/* Enable/Disable external clock synchronization with the clock source oscillator (In case of counter mode) */
#define TIMER1_SELECT_COUNTER_SYNCHRONIZATION(timer1_sync)    (T1CONbits.T1SYNC = timer1_sync)
/* Indication to check the clock source delivered to the timer(Timer1 oscillator or from another source)*/
#define TIMER1_SYSTEM_CLK_STATUS()                            (T1CONbits.T1RUN)


#define TIMER1_SELECT_RW_MODE(rw_mode)                        (T1CONbits.RD16 = rw_mode)

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef enum{
    TIMER1_PRESCALER_DIV_BY_1 = 0,
    TIMER1_PRESCALER_DIV_BY_2,
    TIMER1_PRESCALER_DIV_BY_4,
    TIMER1_PRESCALER_DIV_BY_8,
}En_timer1_prescaler_select_t;

typedef struct{
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    En_interrupt_priority_t interrupt_priority;
#endif
#endif
    uint16 preloaded_value;
    En_timer1_prescaler_select_t prescaler_value;
    uint8 register_rw_mode : 1;
    uint8 counter_sync : 1;
    uint8 mode : 1;
    uint8 timer1_osc_enable : 1;
    uint8 reserved : 4;
}St_timer1_conf_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/
Std_ReturnType MTimer1_init(St_timer1_conf_t* timer1_cfg);
Std_ReturnType MTimer1_deinit(St_timer1_conf_t* timer1_cfg);
Std_ReturnType MTimer1_write_value(St_timer1_conf_t* timer1_cfg, uint16 value);
Std_ReturnType MTimer1_read_value(St_timer1_conf_t* timer1_cfg, uint16* value);

#endif	/* MCAL_TIMER1_H */

