/* 
 * File:   MCAL_Timer2.h
 * Author: ADEL
 *
 * Created on June 18, 2022, 2:59 PM
 */

#ifndef MCAL_TIMER2_H
#define	MCAL_TIMER2_H

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


/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/


#define TIMER2_ENABLE_MODULE()                                (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE_MODULE()                               (T2CONbits.TMR2ON = 0)

#define TIMER2_SELECT_PRESCALER(prescaler)                    (T2CONbits.T2CKPS = prescaler)
#define TIMER2_SELECT_POSTSCALER(prescaler)                   (T2CONbits.TOUTPS = prescaler)


/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef enum{
    TIMER2_PRESCALER_DIV_BY_1 = 0,
    TIMER2_PRESCALER_DIV_BY_4,
    TIMER2_PRESCALER_DIV_BY_16,
}En_timer2_prescaler_select_t;
typedef enum{
    TIMER2_POSTSCALER_DIV_BY_1 = 0,
    TIMER2_POSTSCALER_DIV_BY_2,
    TIMER2_POSTSCALER_DIV_BY_3,
    TIMER2_POSTSCALER_DIV_BY_4,
    TIMER2_POSTSCALER_DIV_BY_5,
    TIMER2_POSTSCALER_DIV_BY_6,
    TIMER2_POSTSCALER_DIV_BY_7,
    TIMER2_POSTSCALER_DIV_BY_8,
    TIMER2_POSTSCALER_DIV_BY_9,
    TIMER2_POSTSCALER_DIV_BY_10,
    TIMER2_POSTSCALER_DIV_BY_11,
    TIMER2_POSTSCALER_DIV_BY_12,
    TIMER2_POSTSCALER_DIV_BY_13,
    TIMER2_POSTSCALER_DIV_BY_14,
    TIMER2_POSTSCALER_DIV_BY_15,
    TIMER2_POSTSCALER_DIV_BY_16,
}En_timer2_postscaler_select_t;

typedef struct{
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    En_interrupt_priority_t interrupt_priority;
#endif
#endif
    uint8 preloaded_value;
    En_timer2_prescaler_select_t prescaler_value;
    En_timer2_postscaler_select_t postscaler_value;
    uint8 reserved : 4;
}St_timer2_conf_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/
Std_ReturnType MTimer2_init(St_timer2_conf_t* timer2_cfg);
Std_ReturnType MTimer2_deinit(St_timer2_conf_t* timer2_cfg);
Std_ReturnType MTimer2_write_value(uint8 value);
Std_ReturnType MTimer2_read_value(uint8* value);


#endif	/* MCAL_TIMER2_H */

