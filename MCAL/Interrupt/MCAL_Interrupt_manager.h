/* 
 * File:   MCAL_Interrupt_manager.h
 * Author: ADEL
 *
 * Created on June 10, 2022, 10:35 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

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

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 source);
void RB5_ISR(uint8 source);
void RB6_ISR(uint8 source);
void RB7_ISR(uint8 source);
void ADC_ISR();
void TIMER0_ISR();
void TIMER1_ISR();
void TIMER2_ISR();
void TIMER3_ISR();
void CCP1_ISR();
void CCP2_ISR();
void EUSART_TX_ISR();
void EUSART_RX_ISR();

#endif	/* MCAL_INTERRUPT_MANAGER_H */

