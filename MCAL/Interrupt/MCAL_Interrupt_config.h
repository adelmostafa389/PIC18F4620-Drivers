/* 
 * File:   MCAL_Interrupt_config.h
 * Author: ADEL
 *
 * Created on June 10, 2022, 10:41 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include <xc.h>
#include "../MCAL_STD_TYPES.h"
#include "../GPIO/MCAL_GPIO.h"
#include "MCAL_Interrupt_gen_config.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/
#define INTERRUPT_ENABLE            1
#define INTERRUPT_DISABLE           0
#define INTERRUPT_OCCURE            1
#define INTERRUPT_NOT_OCCURE        0
#define INTERRUPT_PRIORITY_ENABLE   1
#define INTERRUPT_PRIORITY_DISABLE  0

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This MACRO will enable interrupt priority levels on Interrupt */
#define INTERRUPT_EnablePriorityLevels()                   (RCONbits.IPEN = 1)
/* This MACRO will disable all the global interrupts with high interrupt priority */
#define INTERRUPT_DisablePriorityLevels()                  (RCONbits.IPEN = 0)

/* This MACRO will enable all the global interrupts with high interrupt priority */
#define INTERRUPT_EnableGlobalHighPriorityInterrupt()      (INTCONbits.GIEH = 1)
/* This MACRO will disable all the global interrupts with high interrupt priority */
#define INTERRUPT_DisableGlobalHighPriorityInterrupt()     (INTCONbits.GIEH = 0)

/* This MACRO will enable all the global interrupts with high interrupt priority */
#define INTERRUPT_EnableGlobalLowPriorityInterrupt()       (INTCONbits.GIEL = 1)
/* This MACRO will disable all the global interrupts with high interrupt priority */
#define INTERRUPT_DisableGlobalLowPriorityInterrupt()      (INTCONbits.GIEL = 0)

/* This MACRO will enable all peripheral interrupts */
#define INTERRUPT_EnablePeripheralInterrupt()              (INTCONbits.PEIE = 1)
/* This MACRO will disable all peripheral interrupts */
#define INTERRUPT_DisablePeripheralInterrupt()             (INTCONbits.PEIE = 0)

#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE

/* This MACRO will enable Global interrupts */
#define INTERRUPT_EnableGlobalInterrupt()              (INTCONbits.GIE = 1)
/* This MACRO will disable Global interrupts */
#define INTERRUPT_DisableGlobalInterrupt()             (INTCONbits.GIE = 0)

/* This MACRO will enable all peripheral interrupts */
#define INTERRUPT_EnablePeripheralInterrupt()              (INTCONbits.PEIE = 1)
/* This MACRO will disable all peripheral interrupts */
#define INTERRUPT_DisablePeripheralInterrupt()             (INTCONbits.PEIE = 0)

#endif
/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/
typedef enum{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY 
}En_interrupt_priority_t;


/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

#endif	/* MCAL_INTERRUPT_CONFIG_H */

