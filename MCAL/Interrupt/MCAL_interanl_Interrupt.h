/* 
 * File:   MCAL_interanl_Interrupt.h
 * Author: ADEL
 *
 * Created on June 10, 2022, 10:42 PM
 */

#ifndef MCAL_INTERANL_INTERRUPT_H
#define	MCAL_INTERANL_INTERRUPT_H

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "MCAL_Interrupt_config.h"


/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro disables the ADC Module */
#define ADC_DisableInterrupt()          (PIE1bits.ADIE = 0)
/* This macro disables the ADC Module */
#define ADC_EnableInterrupt()           (PIE1bits.ADIE = 1)
/* This macro clears interrupt flag of the ADC Module */
#define ADC_InterruptFlagClear()        (PIR1bits.ADIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro configure the ADC Module to low adc interrupt priority */
#define ADC_SetToHighPriority()         (IPR1bits.ADIP = 1)
/* This macro configure the ADC Module to high adc interrupt priority */
#define ADC_SetToLowPriority()          (IPR1bits.ADIP = 0)
#endif
#endif


#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro disables the Timer0 Module */
#define TIMER0_DisableInterrupt()          (INTCONbits.TMR0IE = 0)
/* This macro disables the Timer0 Module */
#define TIMER0_EnableInterrupt()           (INTCONbits.TMR0IE = 1)
/* This macro clears interrupt flag of the Timer0 Module */
#define TIMER0_InterruptFlagClear()        (INTCONbits.TMR0IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro configure the Timer0 Module to low interrupt priority */
#define TIMER0_SetToHighPriority()         (INTCON2bits.TMR0IP = 1)
/* This macro configure the Timer0 Module to high interrupt priority */
#define TIMER0_SetToLowPriority()          (INTCON2bits.TMR0IP = 0)
#endif
#endif

#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro disables the Timer1 Module */
#define TIMER1_DisableInterrupt()          (PIE1bits.TMR1IE = 0)
/* This macro disables the Timer1 Module */
#define TIMER1_EnableInterrupt()           (PIE1bits.TMR1IE = 1)
/* This macro clears interrupt flag of the Timer1 Module */
#define TIMER1_InterruptFlagClear()        (PIR1bits.TMR1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro configure the Timer1 Module to low interrupt priority */
#define TIMER1_SetToHighPriority()         (IPR1bits.TMR1IP = 1)
/* This macro configure the Timer1 Module to high interrupt priority */
#define TIMER1_SetToLowPriority()          (IPR1bits.TMR1IP = 0)
#endif
#endif

#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro disables the Timer2 Module */
#define TIMER2_DisableInterrupt()          (PIE1bits.TMR2IE = 0)
/* This macro disables the Timer2 Module */
#define TIMER2_EnableInterrupt()           (PIE1bits.TMR2IE = 1)
/* This macro clears interrupt flag of the Timer1 Module */
#define TIMER2_InterruptFlagClear()        (PIR1bits.TMR2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro configure the Timer2 Module to low interrupt priority */
#define TIMER2_SetToHighPriority()         (IPR1bits.TMR2IP = 1)
/* This macro configure the Timer2 Module to high interrupt priority */
#define TIMER2_SetToLowPriority()          (IPR1bits.TMR2IP = 0)
#endif
#endif

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro disables the Timer3 Module */
#define TIMER3_DisableInterrupt()          (PIE2bits.TMR3IE = 0)
/* This macro disables the Timer3 Module */
#define TIMER3_EnableInterrupt()           (PIE2bits.TMR3IE = 1)
/* This macro clears interrupt flag of the Timer3 Module */
#define TIMER3_InterruptFlagClear()        (PIR2bits.TMR3IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro configure the Timer3 Module to low interrupt priority */
#define TIMER3_SetToHighPriority()         (IPR2bits.TMR3IP = 1)
/* This macro configure the Timer3 Module to high interrupt priority */
#define TIMER3_SetToLowPriority()          (IPR2bits.TMR3IP = 0)
#endif
#endif

#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro disables the CCP1 Module */
#define CCP1_DisableInterrupt()          (PIE1bits.CCP1IE = 0)
/* This macro disables the CCP1 Module */
#define CCP1_EnableInterrupt()           (PIE1bits.CCP1IE = 1)
/* This macro clears interrupt flag of the CCP1 Module */
#define CCP1_InterruptFlagClear()        (PIR1bits.CCP1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro configure the CCP1 Module to low interrupt priority */
#define CCP1_SetToHighPriority()         (IPR1bits.CCP1IP = 1)
/* This macro configure the CCP1 Module to high interrupt priority */
#define CCP1_SetToLowPriority()          (IPR1bits.CCP1IP = 0)
#endif
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro disables the CCP2 Module */
#define CCP2_DisableInterrupt()          (PIE2bits.CCP2IE = 0)
/* This macro disables the CCP2 Module */
#define CCP2_EnableInterrupt()           (PIE2bits.CCP2IE = 1)
/* This macro clears interrupt flag of the CCP2 Module */
#define CCP2_InterruptFlagClear()        (PIR2bits.CCP2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro configure the CCP2 Module to low interrupt priority */
#define CCP2_SetToHighPriority()         (IPR2bits.CCP2IP = 1)
/* This macro configure the CCP2 Module to high interrupt priority */
#define CCP2_SetToLowPriority()          (IPR2bits.CCP2IP = 0)
#endif
#endif

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro disables the EUSART Module TX */
#define EUSART_TX_DisableInterrupt()          (PIE1bits.TXIE = 0)
/* This macro disables the EUSART Module TX */
#define EUSART_TX_EnableInterrupt()           (PIE1bits.TXIE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro configure the EUSART Module TX to low interrupt priority */
#define EUSART_TX_SetToHighPriority()         (IPR1bits.TXIP = 1)
/* This macro configure the EUSART Module TX to high interrupt priority */
#define EUSART_TX_SetToLowPriority()          (IPR1bits.TXIP = 0)
#endif
#endif


#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro disables the EUSART Module RX */
#define EUSART_RX_DisableInterrupt()          (PIE1bits.RCIE = 0)
/* This macro disables the EUSART Module RX */
#define EUSART_RX_EnableInterrupt()           (PIE1bits.RCIE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This macro configure the EUSART Module RX to low interrupt priority */
#define EUSART_RX_SetToHighPriority()         (IPR1bits.TXIP = 1)
/* This macro configure the EUSART Module RX to high interrupt priority */
#define EUSART_RX_SetToLowPriority()          (IPR1bits.TXIP = 0)
#endif
#endif

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/


#endif	/* MCAL_INTERANL_INTERRUPT_H */

