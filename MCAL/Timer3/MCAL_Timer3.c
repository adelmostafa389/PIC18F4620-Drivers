/* 
 * File:   MCAL_Timer3.c
 * Author: ADEL
 *
 * Created on June 18, 2022, 2:59 PM
 */

#include "MCAL_Timer3.h"

PtrTo_func_t Timer3_PtrTo_App_ISR = NULL;
/* Local variable to store T13CKI pin default direction before configure it to be input in case of counter mode */
En_direction_t l_T13CKI_pin_default_direction = INPUT;
uint16 timer3_preload_value = 0;

void TIMER3_ISR(void);

static inline void timer3_configure_interrupt(const St_timer3_conf_t* timer3_cfg);
static inline void timer3_configure_prescaler(const St_timer3_conf_t* timer3_cfg);

Std_ReturnType MTimer3_init(St_timer3_conf_t* timer3_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == timer3_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable Timer3 Module */
        TIMER3_DISABLE_MODULE();
        /* Set the default pre_loaded value to timer3 register */
        MTimer3_write_value(timer3_cfg, timer3_cfg->preloaded_value);
        timer3_preload_value = timer3_cfg->preloaded_value;
        /* Set the pre_scaler */
        TIMER3_SELECT_PRESCALER(timer3_cfg->prescaler_value);
        /* Configure read/write timer3 Register in 8bit mode or in 16bit mode */
        TIMER3_SELECT_RW_MODE(timer3_cfg->register_rw_mode);
        /* Configure Timer3 Mode */
        TIMER3_SELECT_MODE(timer3_cfg->mode);
        /* Configure Timer3 external clock source pin (T13CKI at RC0) to input when counter mode is selected */
        if(TIMER3_COUNTER_MODE == timer3_cfg->mode){
            l_T13CKI_pin_default_direction = TRISCbits.RC0;
            TRISCbits.RC0 = INPUT;
        }
        else{/* Nothing */}
        /* Enable/Disable external clock source synchronization with Timer3 oscillator */
        TIMER3_SELECT_COUNTER_SYNCHRONIZATION(timer3_cfg->counter_sync);
        /* Configure the interrupt */
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_EnableInterrupt();
        timer3_configure_interrupt(timer3_cfg);
#endif
        /* Enable Timer3 module */
        TIMER3_ENABLE_MODULE();
        errorState = E_OK;
    }
    return errorState;
}

Std_ReturnType MTimer3_deinit(St_timer3_conf_t* timer3_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == timer3_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable Timer3 Module */
        TIMER3_DISABLE_MODULE();
        /* Disable Timer3 Module Interrupt feature */
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_DisableInterrupt();
#endif
        /* Set pin T13CKI direction to the default value */
        TRISCbits.RC0 = l_T13CKI_pin_default_direction;
    }
    return errorState;
}

Std_ReturnType MTimer3_write_value(St_timer3_conf_t* timer3_cfg, uint16 value){
    Std_ReturnType errorState = E_OK;
    if(NULL == timer3_cfg){
        errorState = E_NOT_OK;
    }
    else{
        TMR3H = (uint8)(value >> 8);
        TMR3L = (uint8)(value);
    }
    return errorState;
}

Std_ReturnType MTimer3_read_value(St_timer3_conf_t* timer3_cfg, uint16* value){
    Std_ReturnType errorState = E_OK;
    uint8 l_tmr3l = ZERO_INIT, l_tmr3h = ZERO_INIT;
    if((NULL == timer3_cfg) || (NULL == value)){
        errorState = E_NOT_OK;
    }
    else{
        l_tmr3l = TMR3L;
        l_tmr3h = TMR3H;
        *value = (uint16)((l_tmr3h<<8) + l_tmr3l);
    }
    return errorState;
}


void TIMER3_ISR(void){
    TMR3H = (uint8)(timer3_preload_value >> 8);
    TMR3L = (uint8)(timer3_preload_value);
    if(Timer3_PtrTo_App_ISR){
        Timer3_PtrTo_App_ISR();
    }else { /* Nothing */}
}


static inline void timer3_configure_interrupt(const St_timer3_conf_t* timer3_cfg){
    TIMER3_InterruptFlagClear();
    Timer3_PtrTo_App_ISR = timer3_cfg->InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE
    INTERRUPT_EnableGlobalInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();
#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_EnableGlobalHighPriorityInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();    
    if(INTERRUPT_HIGH_PRIORITY == timer3_cfg->interrupt_priority){ TIMER3_SetToHighPriority(); }
    else if(INTERRUPT_LOW_PRIORITY == timer3_cfg->interrupt_priority){ TIMER3_SetToLowPriority(); }
    else{ /* Nothing */ }
#endif
}