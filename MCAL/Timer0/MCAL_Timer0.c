/* 
 * File:   MCAL_Timer0.c
 * Author: ADEL
 *
 * Created on June 16, 2022, 6:14 PM
 */

#include "MCAL_Timer0.h"

PtrTo_func_t Timer0_PtrTo_App_ISR = NULL;

uint16 timer0_preload_value = 0;

void TIMER0_ISR(void);

static inline void timer0_configure_interrupt(const St_timer0_conf_t* timer0_cfg);
static inline void timer0_configure_prescaler(const St_timer0_conf_t* timer0_cfg);

/**
 * 
 * @param timer0_cfg
 * @return 
 */
Std_ReturnType MTimer0_init(St_timer0_conf_t* timer0_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == timer0_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable the Timer0 */
        TIMER0_DISABLE_MODULE();
        /* Set the default preloaded value to timer0 register */
        timer0_preload_value = timer0_cfg->preloaded_value;
        errorState = MTimer0_write_value(timer0_cfg, (timer0_cfg->preloaded_value));
        /* Configure the prescaler */
        timer0_configure_prescaler(timer0_cfg);
        /* Configure timer0 register size */
        TIMER0_SELECT_REGISTER_SIZE(timer0_cfg->register_size);
        /* Configure Timer0 Mode */
        TIMER0_SELECT_MODE(timer0_cfg->mode);
        /* Configure Timer0 external clock source pin (T0CKI at RA4) to input */
        TRISAbits.RA4 = INPUT;
        /* Select edge type to increase the counter rising-edge/falling-edge */
        TIMER0_SELECT_COUNTER_EDGE(timer0_cfg->counter_edge);
        /* Configure the interrupt */
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_EnableInterrupt();
        timer0_configure_interrupt(timer0_cfg);
#endif
        /* Enable Timer0 module */
        TIMER0_ENABLE_MODULE();
        errorState = E_OK;
    }
    return errorState;
}

Std_ReturnType MTimer0_deinit(St_timer0_conf_t* timer0_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == timer0_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable Timer0 Module */
        TIMER0_DISABLE_MODULE();
        /* Disable Timer0 Module Interrupt feature */
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_DisableInterrupt();
#endif
    }
    return errorState;
}

Std_ReturnType MTimer0_write_value(St_timer0_conf_t* timer0_cfg, uint16 value){
    Std_ReturnType errorState = E_OK;
    if(NULL == timer0_cfg){
        errorState = E_NOT_OK;
    }
    else{
        TMR0H = (uint8)(value >> 8);
        TMR0L = (uint8)(value);
    }
    return errorState;
}

Std_ReturnType MTimer0_read_value(St_timer0_conf_t* timer0_cfg, uint16* value){
    Std_ReturnType errorState = E_OK;
    uint8 l_tmr0l = ZERO_INIT, l_tmr0h = ZERO_INIT;
    if(NULL == timer0_cfg){
        errorState = E_NOT_OK;
    }
    else{
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0H;
        *value = (uint16)((l_tmr0h<<8) + l_tmr0l);
    }
    return errorState;
}

void TIMER0_ISR(void){
    TMR0H = (uint8)(timer0_preload_value >> 8);
    TMR0L = (uint8)(timer0_preload_value);
    if(Timer0_PtrTo_App_ISR){
        Timer0_PtrTo_App_ISR();
    }else { /* Nothing */}
}

static inline void timer0_configure_prescaler(const St_timer0_conf_t* timer0_cfg){
    if(TIMER0_PRESCALER_ENABLE_CFG == timer0_cfg->prescaler_enable){
        TIMER0_ENABLE_PRESCALER();
        TIMER0_SELECT_PRESCALER(timer0_cfg->prescaler_value);
    }
    else if(TIMER0_PRESCALER_DISABLE_CFG == timer0_cfg->prescaler_enable){
        TIMER0_DISABLE_PRESCALER();
    }
    else{/* Nothing */}
}

static inline void timer0_configure_interrupt(const St_timer0_conf_t* timer0_cfg){
    TIMER0_InterruptFlagClear();
    Timer0_PtrTo_App_ISR = timer0_cfg->InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE
    INTERRUPT_EnableGlobalInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();
#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_EnableGlobalHighPriorityInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();    
    if(INTERRUPT_HIGH_PRIORITY == timer0_cfg->interrupt_priority){ TIMER0_SetToHighPriority(); }
    else if(INTERRUPT_LOW_PRIORITY == timer0_cfg->interrupt_priority){ TIMER0_SetToLowPriority(); }
    else{ /* Nothing */ }
#endif
}