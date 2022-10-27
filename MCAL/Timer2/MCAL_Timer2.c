/* 
 * File:   MCAL_Timer2.c
 * Author: ADEL
 *
 * Created on June 18, 2022, 2:59 PM
 */

#include "MCAL_Timer2.h"

PtrTo_func_t Timer2_PtrTo_App_ISR = NULL;

uint8 timer2_preload_value = 0;

void TIMER2_ISR(void);

static inline void timer2_configure_interrupt(const St_timer2_conf_t* timer2_cfg);


Std_ReturnType MTimer2_init(St_timer2_conf_t* timer2_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == timer2_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable the Timer1 */
        TIMER2_DISABLE_MODULE();
        /* Set the default pre_loaded value to timer1 register */
        MTimer2_write_value(timer2_cfg->preloaded_value);
        timer2_preload_value = timer2_cfg->preloaded_value;
        /* Set the pre_scaler */
        TIMER2_SELECT_PRESCALER(timer2_cfg->prescaler_value);
        /* Set the post_scaler */
        TIMER2_SELECT_POSTSCALER(timer2_cfg->postscaler_value);
        /* Configure the interrupt */
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_EnableInterrupt();
        timer2_configure_interrupt(timer2_cfg);
#endif
        /* Enable Timer2 module */
        TIMER2_ENABLE_MODULE();
        errorState = E_OK;
    }
    return errorState;
}

Std_ReturnType MTimer2_deinit(St_timer2_conf_t* timer2_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == timer2_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable Timer2 Module */
        TIMER2_DISABLE_MODULE();
        /* Disable Timer2 Module Interrupt feature */
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_DisableInterrupt();
#endif
    }
    return errorState;
}

Std_ReturnType MTimer2_write_value(uint8 value){
    Std_ReturnType errorState = E_OK;
    PR2 = value;    
    return errorState;
}

Std_ReturnType MTimer2_read_value(uint8* value){
    Std_ReturnType errorState = E_OK;
    if(NULL == value){
        errorState = E_NOT_OK;
    }
    else{
        *value = TMR2;
    }
    return errorState;
}

void TIMER2_ISR(void){
    PR2 = timer2_preload_value;
    if(Timer2_PtrTo_App_ISR){
        Timer2_PtrTo_App_ISR();
    }else { /* Nothing */}
}

static inline void timer2_configure_interrupt(const St_timer2_conf_t* timer2_cfg){
    TIMER2_InterruptFlagClear();
    Timer2_PtrTo_App_ISR = timer2_cfg->InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE
    INTERRUPT_EnableGlobalInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();
#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_EnableGlobalHighPriorityInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();    
    if(INTERRUPT_HIGH_PRIORITY == timer2_cfg->interrupt_priority){ TIMER2_SetToHighPriority(); }
    else if(INTERRUPT_LOW_PRIORITY == timer2_cfg->interrupt_priority){ TIMER2_SetToLowPriority(); }
    else{ /* Nothing */ }
#endif
}
