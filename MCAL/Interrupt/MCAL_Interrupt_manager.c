/* 
 * File:   MCAL_Interrupt_manager.c
 * Author: ADEL
 *
 * Created on June 10, 2022, 10:35 PM
 */

#include "MCAL_Interrupt_gen_config.h"
#include "MCAL_Interrupt_config.h"
#include "MCAL_Interrupt_manager.h"
#include "MCAL_external_Interrupt.h"
#include "MCAL_interanl_Interrupt.h"

static volatile uint8 RB4_previous_state = 1;
static volatile uint8 RB5_previous_state = 1;
static volatile uint8 RB6_previous_state = 1;
static volatile uint8 RB7_previous_state = 1;


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/********************************************************************************************/
/*                                       HIGH LEVEL ISRs                                    */
/********************************************************************************************/
void __interrupt() InterruptManagerHigh(void){
    /*****************************   External Interrupt ISR section   **************************/
    if((INTERRUPT_ENABLE == INTCONbits.INT0E) && (INTERRUPT_OCCURE == INTCONbits.INT0IF)){
        INT0_ISR();
        /* The external interrupt INT0 has occurred (must be cleared in software */
        EXT_INT0_ClearFlag();
    }
    else{ /* Nothing */ } 
    if((INTERRUPT_ENABLE == INTCON3bits.INT2E) && (INTERRUPT_OCCURE == INTCON3bits.INT2IF)){
        INT2_ISR();
        /* The external interrupt INT2 has occurred (must be cleared in software */
        EXT_INT2_ClearFlag();
    }
    else{ /* Nothing */ } 
    /*****************************     RBx ISR  section   **************************/
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURE == INTCONbits.RBIF)){
        if((1 == RB4_previous_state) && (HIGH == PORTBbits.RB4)){
            RB4_ISR(RB4_previous_state);
            RB4_previous_state = 0;
        }
        else if((0 == RB4_previous_state) && (LOW == PORTBbits.RB4)){
            RB4_ISR(RB4_previous_state);
            RB4_previous_state = 1;
        }
        else{ /* Nothing */ }
        
        if((1 == RB5_previous_state) && (HIGH == PORTBbits.RB5)){
            RB5_ISR(RB5_previous_state);
            RB5_previous_state = 0;
        }
        else if((0 == RB5_previous_state) && (LOW == PORTBbits.RB5)){
            RB5_ISR(RB5_previous_state);
            RB5_previous_state = 1;
        }
        else{ /* Nothing */ }
        
        if((1 == RB6_previous_state) && (HIGH == PORTBbits.RB6)){
            RB6_ISR(RB6_previous_state);
            RB6_previous_state = 0;
        }
        else if((0 == RB6_previous_state) && (LOW == PORTBbits.RB6)){
            RB6_ISR(RB6_previous_state);
            RB6_previous_state = 1;
        }
        else{ /* Nothing */ }
        
        if((1 == RB7_previous_state) && (HIGH == PORTBbits.RB7)){
            RB7_ISR(RB7_previous_state);
            RB7_previous_state = 0;
        }
        else if((0 == RB7_previous_state) && (LOW == PORTBbits.RB7)){
            RB7_ISR(RB7_previous_state);
            RB7_previous_state = 1;
        }
        else{ /* Nothing */ }
        
        /* The external interrupt RBx has occurred (must be cleared in software */
        EXT_RBx_ClearFlag();
    }
    else{ /* Nothing */ }
    /*****************************      ADC ISR section    **************************/
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCURE == PIR1bits.ADIF)){
        ADC_ISR();
        /* ADC Interrupt has occurred (must be cleared in software */
        ADC_InterruptFlagClear();
    }
    /*****************************     Timer0 ISR  section   **************************/
    if((INTERRUPT_ENABLE == INTCONbits.T0IE) && (INTERRUPT_OCCURE == INTCONbits.T0IF)){
        TIMER0_ISR();
        /* Timer0 Interrupt has occurred (must be cleared in software */
        TIMER0_InterruptFlagClear();
    }
    else{ /* Nothing */ } 
    /*****************************      Timer1 ISR section    **************************/
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCURE == PIR1bits.TMR1IF)){
        TIMER1_ISR();
        /* Timer1 Interrupt has occurred (must be cleared in software */
        TIMER1_InterruptFlagClear();
    }
    else{ /* Nothing */ } 
    /*****************************      Timer2 ISR section    **************************/
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCURE == PIR1bits.TMR2IF)){
        /* Timer2 Interrupt has occurred (must be cleared in software */
        TIMER2_InterruptFlagClear();
        /* Perform Timer2 Interrupt handler */
        TIMER2_ISR();
    }
    else{ /* Nothing */ } 
    /*****************************      Timer3 ISR section    **************************/
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCURE == PIR2bits.TMR3IF)){
        TIMER3_ISR();
        /* Timer3 Interrupt has occurred (must be cleared in software */
        TIMER3_InterruptFlagClear();
    }
    else{ /* Nothing */ } 
    /*****************************      CCP1 ISR section    **************************/
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCURE == PIR1bits.CCP1IF)){
        CCP1_ISR();
        /* CCP1 Interrupt has occurred (must be cleared in software */
        CCP1_InterruptFlagClear();
    }
    else{ /* Nothing */ } 
    
    /*****************************      CCP2 ISR section    **************************/
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCURE == PIR2bits.CCP2IF)){
        CCP2_ISR();
        /* CCP2 Interrupt has occurred (must be cleared in software */
        CCP2_InterruptFlagClear();
    }
    else{ /* Nothing */ } 
    
    /***************************      EUSART TX ISR section    ***********************/
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCURE == PIR1bits.TXIF)){
        EUSART_TX_ISR();
    }
    else{ /* Nothing */ } 
    
    /***************************      EUSART RX ISR section    ***********************/
    if((INTERRUPT_ENABLE == PIE1bits.RC1IE) && (INTERRUPT_OCCURE == PIR1bits.RCIF)){
        EUSART_RX_ISR();
    }
    else{ /* Nothing */ } 
}

/********************************************************************************************/
/*                                       LOW LEVEL ISRs                                     */
/********************************************************************************************/
void __interrupt(low_priority) InterruptManagerLow(void){
    /*****************************   External Interrupt ISR section   **************************/
    if((INTERRUPT_ENABLE == INTCON3bits.INT1E) && (INTERRUPT_OCCURE == INTCON3bits.INT1F)){
        INT1_ISR();
        /* The external interrupt INT1 has occurred (must be cleared in software */
        EXT_INT1_ClearFlag();
        
    }
    else{ /* Nothing */ } 
    /*****************************     RBx ISR  section   **************************/
        
    /*****************************      ADC ISR section    **************************/
    
    /*****************************     Timer0 ISR  section   **************************/
    
    /*****************************     Timer1 ISR  section   **************************/
    
    /*****************************      CCP1 ISR section    **************************/
    
    /*****************************      CCP1 ISR section    **************************/
    
    
}

#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE

/********************************************************************************************/
/*                               ALL ISRs WITH NO PRIORITY LEVELS                           */
/********************************************************************************************/
void __interrupt() InterruptManager(void){
    /*****************************   External Interrupt ISR section   **************************/
    if((INTERRUPT_ENABLE == INTCONbits.INT0E) && (INTERRUPT_OCCURE == INTCONbits.INT0IF)){
        INT0_ISR();
        /* The external interrupt INT0 has occurred (must be cleared in software */
        EXT_INT0_ClearFlag();
    }
    else{ /* Nothing */ } 
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT1E) && (INTERRUPT_OCCURE == INTCON3bits.INT1F)){
        INT1_ISR();
        /* The external interrupt INT1 has occurred (must be cleared in software */
        EXT_INT1_ClearFlag();
    }
    else{ /* Nothing */ } 
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT2E) && (INTERRUPT_OCCURE == INTCON3bits.INT2IF)){
        INT2_ISR();
        /* The external interrupt INT2 has occurred (must be cleared in software */
        EXT_INT2_ClearFlag();
    }
    else{ /* Nothing */ } 
    /*****************************      RBx ISR section    **************************/
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURE == INTCONbits.RBIF)){
        if((1 == RB4_previous_state) && (HIGH == PORTBbits.RB4)){
            RB4_ISR(RB4_previous_state);
            RB4_previous_state = 0;
        }
        else if((0 == RB4_previous_state) && (LOW == PORTBbits.RB4)){
            RB4_ISR(RB4_previous_state);
            RB4_previous_state = 1;
        }
        else{ /* Nothing */ }
        
        if((1 == RB5_previous_state) && (HIGH == PORTBbits.RB5)){
            RB5_ISR(RB5_previous_state);
            RB5_previous_state = 0;
        }
        else if((0 == RB5_previous_state) && (LOW == PORTBbits.RB5)){
            RB5_ISR(RB5_previous_state);
            RB5_previous_state = 1;
        }
        else{ /* Nothing */ }
        
        if((1 == RB6_previous_state) && (HIGH == PORTBbits.RB6)){
            RB6_ISR(RB6_previous_state);
            RB6_previous_state = 0;
        }
        else if((0 == RB6_previous_state) && (LOW == PORTBbits.RB6)){
            RB6_ISR(RB6_previous_state);
            RB6_previous_state = 1;
        }
        else{ /* Nothing */ }
        
        if((1 == RB7_previous_state) && (HIGH == PORTBbits.RB7)){
            RB7_ISR(RB7_previous_state);
            RB7_previous_state = 0;
        }
        else if((0 == RB7_previous_state) && (LOW == PORTBbits.RB7)){
            RB7_ISR(RB7_previous_state);
            RB7_previous_state = 1;
        }
        else{ /* Nothing */ }
        
        /* The external interrupt RBx has occurred (must be cleared in software */
        EXT_RBx_ClearFlag();
    }
    else{ /* Nothing */ }
    /*****************************      ADC ISR section    **************************/
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCURE == PIR1bits.ADIF)){
        ADC_ISR();
        /* The external interrupt INT1 has occurred (must be cleared in software */
        ADC_InterruptFlagClear();
    }
    else{ /* Nothing */ } 
    /*****************************      Timer0 ISR section    **************************/
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCURE == INTCONbits.TMR0IF)){
        TIMER0_ISR();
        /* The external interrupt INT1 has occurred (must be cleared in software */
        TIMER0_InterruptFlagClear();
    }
    else{ /* Nothing */ } 
    /*****************************      Timer1 ISR section    **************************/
    if((INTERRUPT_ENABLE == INTCONbits.T1IE) && (INTERRUPT_OCCURE == INTCONbits.T1IF)){
        TIMER1_ISR();
        /* The external interrupt INT1 has occurred (must be cleared in software */
        TIMER1_InterruptFlagClear();
    }
    else{ /* Nothing */ } 
    /*****************************      Timer2 ISR section    **************************/
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCURE == PIR1bits.TMR2IF)){
        TIMER2_ISR();
        /* The external interrupt INT2 has occurred (must be cleared in software */
        TIMER2_InterruptFlagClear();
    }
    else{ /* Nothing */ } 
    /*****************************      Timer3 ISR section    **************************/
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCURE == PIR2bits.TMR3IF)){
        TIMER3_ISR();
        /* Timer3 Interrupt has occurred (must be cleared in software */
        TIMER3_InterruptFlagClear();
    }
    else{ /* Nothing */ } 
    /*****************************      CCP1 ISR section    **************************/
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCURE == PIR1bits.CCP1IF)){
        CCP1_ISR();
        /* CCP1 Interrupt has occurred (must be cleared in software */
        CCP1_InterruptFlagClear();
    }
    else{ /* Nothing */ } 
    /*****************************      CCP2 ISR section    **************************/
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCURE == PIR2bits.CCP2IF)){
        CCP2_ISR();
        /* CCP2 Interrupt has occurred (must be cleared in software */
        CCP2_InterruptFlagClear();
    }
    else{ /* Nothing */ } 
    
    /***************************      EUSART TX ISR section    ***********************/
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCURE == PIR1bits.TXIF)){
        EUSART_TX_ISR();
    }
    else{ /* Nothing */ } 
    
    /***************************      EUSART RX ISR section    ***********************/
    if((INTERRUPT_ENABLE == PIE1bits.RC1IE) && (INTERRUPT_OCCURE == PIR1bits.RCIF)){
        EUSART_RX_ISR();
    }
    else{ /* Nothing */ } 
}

#endif