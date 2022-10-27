/* 
 * File:   MCAL_Timer0.h
 * Author: ADEL
 *
 * Created on June 16, 2022, 6:14 PM
 */

#ifndef MCAL_TIMER0_H
#define	MCAL_TIMER0_H


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

#define TIMER0_PRESCALER_DISABLE_CFG      1
#define TIMER0_PRESCALER_ENABLE_CFG       0

#define TIMER0_FALLING_EDGE_ENABLE_CFG    1
#define TIMER0_RISING_EDGE_ENABLE_CFG     0

#define TIMER0_COUNTER_MODE               1
#define TIMER0_TIMER_MODE                 0

#define TIMER0_8BIT_REGISTER_MODE         1
#define TIMER0_16BIT_REGISTER_MODE        0

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

#define TIMER0_SELECT_PRESCALER(prescaler)          (T0CONbits.T0PS = prescaler)

#define TIMER0_ENABLE_PRESCALER()                   (T0CONbits.PSA = 0)
#define TIMER0_DISABLE_PRESCALER()                  (T0CONbits.PSA = 1)

#define TIMER0_SELECT_COUNTER_EDGE(counter_edge)    (T0CONbits.T0SE = counter_edge)

#define TIMER0_SELECT_MODE(timer0_mode)             (T0CONbits.T0CS = timer0_mode)

#define TIMER0_SELECT_REGISTER_SIZE(register_size)  (T0CONbits.T08BIT = register_size)

#define TIMER0_ENABLE_MODULE()                      (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE_MODULE()                     (T0CONbits.TMR0ON = 0)

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef enum{
    TIMER0_PRESCALER_DIV_BY_2 = 0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256,
}En_timer0_prescaler_select_t;

typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    En_interrupt_priority_t interrupt_priority;
#endif
#endif
    uint16 preloaded_value;
    En_timer0_prescaler_select_t prescaler_value;
    uint8 prescaler_enable : 1;
    uint8 register_size : 1;
    uint8 mode : 1;
    uint8 counter_edge : 1;
}St_timer0_conf_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/
Std_ReturnType MTimer0_init(St_timer0_conf_t* timer0_cfg);
Std_ReturnType MTimer0_deinit(St_timer0_conf_t* timer0_cfg);
Std_ReturnType MTimer0_write_value(St_timer0_conf_t* timer0_cfg, uint16 value);
Std_ReturnType MTimer0_read_value(St_timer0_conf_t* timer0_cfg, uint16* value);

#endif	/* MCAL_TIMER0_H */

