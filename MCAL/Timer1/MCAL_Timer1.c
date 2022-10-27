/* 
 * File:   MCAL_Timer1.c
 * Author: ADEL
 *
 * Created on June 17, 2022, 4:08 PM
 */

#include "MCAL_Timer1.h"

PtrTo_func_t Timer1_PtrTo_App_ISR = NULL;
/* Local variable to store T13CKI pin default direction before configure it to be input in case of counter mode */
En_direction_t l_T13CKI_pin_default_direction = INPUT;
uint16 timer1_preload_value = 0;

void TIMER1_ISR(void);

static inline void timer1_configure_interrupt(const St_timer1_conf_t* timer1_cfg);
static inline void timer1_configure_prescaler(const St_timer1_conf_t* timer1_cfg);

Std_ReturnType MTimer1_init(St_timer1_conf_t* timer1_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == timer1_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable Timer1 Module */
        TIMER1_DISABLE_MODULE();
        /* Set the default pre_loaded value to timer1 register */
        MTimer1_write_value(timer1_cfg, timer1_cfg->preloaded_value);
        timer1_preload_value = timer1_cfg->preloaded_value;
        /* Set the pre_scaler */
        TIMER1_SELECT_PRESCALER(timer1_cfg->prescaler_value);
        /* Configure read/write timer1 Register in 8bit mode or in 16bit mode */
        TIMER1_SELECT_RW_MODE(timer1_cfg->register_rw_mode);
        /* Configure Timer1 Mode */
        TIMER1_SELECT_MODE(timer1_cfg->mode);
        /* Configure Timer1 external clock source pin (T13CKI at RC0) to input when counter mode is selected */
        if(TIMER1_COUNTER_MODE == timer1_cfg->mode){
            l_T13CKI_pin_default_direction = TRISCbits.RC0;
            TRISCbits.RC0 = INPUT;
        }
        else{/* Nothing */}
        /* Enable/Disable external clock source synchronization with Timer1 oscillator */
        TIMER1_SELECT_COUNTER_SYNCHRONIZATION(timer1_cfg->counter_sync);
        /* Enable/Disable Timer1 oscillator connected to pins (RC0 "T1OS0" & RC1 "T1OS1") */
        if(TIMER1_OSC_ENABLE == (timer1_cfg->timer1_osc_enable)){
            TIMER1_ENABLE_OSC();
        }
        else if(TIMER1_OSC_DISABLE == (timer1_cfg->timer1_osc_enable)){
            TIMER1_DISABLE_OSC();
        }
        else{/* Nothing */}
        /* Configure the interrupt */
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_EnableInterrupt();
        timer1_configure_interrupt(timer1_cfg);
#endif
        /* Enable Timer1 module */
        TIMER1_ENABLE_MODULE();
        errorState = E_OK;
    }
    return errorState;
}

Std_ReturnType MTimer1_deinit(St_timer1_conf_t* timer1_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == timer1_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable Timer1 Module */
        TIMER1_DISABLE_MODULE();
        /* Disable Timer1 Module Interrupt feature */
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_DisableInterrupt();
#endif
        /* Set pin T13CKI direction to the default value */
        TRISCbits.RC0 = l_T13CKI_pin_default_direction;
    }
    return errorState;
}

Std_ReturnType MTimer1_write_value(St_timer1_conf_t* timer1_cfg, uint16 value){
    Std_ReturnType errorState = E_OK;
    if(NULL == timer1_cfg){
        errorState = E_NOT_OK;
    }
    else{
        TMR1H = (uint8)(value >> 8);
        TMR1L = (uint8)(value);
    }
    return errorState;
}

Std_ReturnType MTimer1_read_value(St_timer1_conf_t* timer1_cfg, uint16* value){
    Std_ReturnType errorState = E_OK;
    uint8 l_tmr1l = ZERO_INIT, l_tmr1h = ZERO_INIT;
    if((NULL == timer1_cfg) || (NULL == value)){
        errorState = E_NOT_OK;
    }
    else{
        l_tmr1l = TMR1L;
        l_tmr1h = TMR1H;
        *value = (uint16)((l_tmr1h<<8) + l_tmr1l);
    }
    return errorState;
}


void TIMER1_ISR(void){
    TMR1H = (uint8)(timer1_preload_value >> 8);
    TMR1L = (uint8)(timer1_preload_value);
    if(Timer1_PtrTo_App_ISR){
        Timer1_PtrTo_App_ISR();
    }else { /* Nothing */}
}


static inline void timer1_configure_interrupt(const St_timer1_conf_t* timer1_cfg){
    TIMER1_InterruptFlagClear();
    Timer1_PtrTo_App_ISR = timer1_cfg->InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE
    INTERRUPT_EnableGlobalInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();
#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_EnableGlobalHighPriorityInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();    
    if(INTERRUPT_HIGH_PRIORITY == timer1_cfg->interrupt_priority){ TIMER1_SetToHighPriority(); }
    else if(INTERRUPT_LOW_PRIORITY == timer1_cfg->interrupt_priority){ TIMER1_SetToLowPriority(); }
    else{ /* Nothing */ }
#endif
}