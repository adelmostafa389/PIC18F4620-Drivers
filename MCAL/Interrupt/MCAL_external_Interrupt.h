/* 
 * File:   MCAL_external_Interrupt.h
 * Author: ADEL
 *
 * Created on June 10, 2022, 10:41 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "MCAL_Interrupt_config.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/


/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This macro disables the external interrupt, INT0 */
#define EXT_INT0_DisableInterrupt()          (INTCONbits.INT0E = 0)
/* This macro enables the external interrupt, INT0 */
#define EXT_INT0_EnableInterrupt()           (INTCONbits.INT0E = 1)
/* This macro clears interrupt flag of the external interrupt, INT0 */
#define EXT_INT0_ClearFlag()                 (INTCONbits.INT0IF = 0)
/* This macro configure the external interrupt, INT0, to interrupt on rising edge */
#define EXT_INT0_InterruptOnRisingEdge()     (INTCON2bits.INTEDG0 = 1)
/* This macro configure the external interrupt, INT0, to interrupt on falling edge */
#define EXT_INT0_InterruptOnFallingEdge()    (INTCON2bits.INTEDG0 = 0)

/* This macro disables the external interrupt, INT1 */
#define EXT_INT1_DisableInterrupt()          (INTCON3bits.INT1E = 0)
/* This macro enables the external interrupt, INT1 */
#define EXT_INT1_EnableInterrupt()           (INTCON3bits.INT1E = 1)
/* This macro clears interrupt flag of the external interrupt, INT1 */
#define EXT_INT1_ClearFlag()                 (INTCON3bits.INT1F = 0)
/* This macro configure the external interrupt, INT1, to interrupt on rising edge */
#define EXT_INT1_InterruptOnRisingEdge()     (INTCON2bits.INTEDG1 = 1)
/* This macro configure the external interrupt, INT1, to interrupt on falling edge */
#define EXT_INT1_InterruptOnFallingEdge()    (INTCON2bits.INTEDG1 = 0)

/* This macro disables the external interrupt, INT2 */
#define EXT_INT2_DisableInterrupt()          (INTCON3bits.INT2E = 0)
/* This macro enables the external interrupt, INT2 */
#define EXT_INT2_EnableInterrupt()           (INTCON3bits.INT2E = 1)
/* This macro clears interrupt flag of the external interrupt, INT1 */
#define EXT_INT2_ClearFlag()                 (INTCON3bits.INT2F = 0)
/* This macro configure the external interrupt, INT2, to interrupt on rising edge */
#define EXT_INT2_InterruptOnRisingEdge()     (INTCON2bits.INTEDG2 = 1)
/* This macro configure the external interrupt, INT2, to interrupt on falling edge */
#define EXT_INT2_InterruptOnFallingEdge()    (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro configure the external interrupt, INT1, to low adc_interrupt_priority */
#define EXT_INT1_SetToHighPriority()         (INTCON3bits.INT1IP = 1)
/* This macro configure the external interrupt, INT1, to high adc_interrupt_priority */
#define EXT_INT1_SetToLowPriority()          (INTCON3bits.INT1IP = 0)

/* This macro configure the external interrupt, INT2, to low adc_interrupt_priority */
#define EXT_INT2_SetToHighPriority()         (INTCON3bits.INT2IP = 1)
/* This macro configure the external interrupt, INT2, to high adc_interrupt_priority */
#define EXT_INT2_SetToLowPriority()          (INTCON3bits.INT2IP = 0)
#endif

#elif EXTERNAL_INTERRUPT_INX_FEATURE_ENABLE == INTERRUPT_FEATURE_DISABLE

#endif


#if EXTERNAL_INTERRUPT_ON_CHANGE_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This macro disables the external interrupt, RBx */
#define EXT_RBx_DisableInterrupt()          (INTCONbits.RBIE = 0)
/* This macro disables the external interrupt, RBx */
#define EXT_RBx_EnableInterrupt()           (INTCONbits.RBIE = 1)
/* This macro clears interrupt flag of the external interrupt, RBx */
#define EXT_RBx_ClearFlag()                 (INTCONbits.RBIF = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro configure the external interrupt, RBx, to low adc_interrupt_priority */
#define EXT_RBx_SetToHighPriority()         (INTCON2bits.RBIP = 1)
/* This macro configure the external interrupt, RBx, to high adc_interrupt_priority */
#define EXT_RBx_SetToLowPriority()          (INTCON2bits.RBIP = 0)
#endif

#elif EXTERNAL_INTERRUPT_INX_FEATURE_ENABLE == INTERRUPT_FEATURE_DISABLE

#endif

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/
typedef enum{
    EXT_INT0 = 0,
    EXT_INT1,
    EXT_INT2
}En_interrupt_INTx_src_t;

typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE
}En_interrupt_INTx_edge_t;

typedef struct{
    void (* EXT_InterruptHandler)(void);
    St_pin_config_t mcu_pin;
    En_interrupt_INTx_src_t source;
    En_interrupt_INTx_edge_t edge;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    En_interrupt_priority_t adc_interrupt_priority;
#endif
}St_interrupt_INTx_t;

typedef struct{
    void (* EXT_On_Rising_InterruptHandler)(void);
    void (* EXT_On_Falling_InterruptHandler)(void);
    St_pin_config_t mcu_pin;
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    En_interrupt_priority_t adc_interrupt_priority;
    #endif
}St_interrupt_RBx_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

/**
 * 
 * @param interrupt_object
 * @return 
 */
Std_ReturnType MInterrupt_Initialize_INTx(const St_interrupt_INTx_t* interrupt_object);

/**
 * 
 * @param interrupt_object
 * @return 
 */
Std_ReturnType MInterrupt_Deinitialize_INTx(const St_interrupt_INTx_t* interrupt_object);

/**
 * 
 * @param interrupt_object
 * @return 
 */
Std_ReturnType MInterrupt_Initialize_RBx(const St_interrupt_RBx_t* interrupt_object);

/**
 * 
 * @param interrupt_object
 * @return 
 */
Std_ReturnType MInterrupt_Deinitialize_RBx(const St_interrupt_RBx_t* interrupt_object);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

