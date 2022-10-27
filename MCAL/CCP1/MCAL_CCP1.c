/* 
 * File:   MCAL_CCP1.c
 * Author: ADEL
 *
 * Created on June 20, 2022, 11:04 AM
 */

#include "MCAL_CCP1.h"
#include "MCAL_CCP1_config.h"

PtrTo_func_t CCP1_PtrTo_App_ISR = NULL;
void CCP1_ISR(void);

static inline void CCP1_configure_interrupt(const St_CCP1_cfg_t* ccp1_cfg);
static inline void CCP_Timer_source_select(const St_CCP1_cfg_t* ccp1_cfg);

Std_ReturnType MCCP1_init(const St_CCP1_cfg_t* ccp1_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == ccp1_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable the CPP1 module */
        CCP1_DISABLE_MODULE();
        /* Select CPP1 mode(Compare/Capture/PWM) */
        CCP1_SELECT_MODE(ccp1_cfg->mode);
        /* CCP1 I/O pin configuration */
        errorState = MGPIO_initialize_pin(&(ccp1_cfg->ccp_pin));
        /*  */
#if CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECT
        CCP_Timer_source_select(&ccp1_cfg);
#elif CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECT
        CCP_Timer_source_select(&ccp1_cfg);
#elif CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECT
        /* Set Timer1 period register (PR2) value to generate PWM frequency */
        PR2 = (uint8)(_XTAL_FREQ/
                (ccp1_cfg->PWM_frequency * 4 * ccp1_cfg->timer2_prescaler_value));
#endif
        /* Configure the interrupt */
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP1_EnableInterrupt();
        CCP1_configure_interrupt(ccp1_cfg);
#endif
        errorState = E_OK;
    }
    return errorState;
}

Std_ReturnType MCCP1_deinit(const St_CCP1_cfg_t* ccp1_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == ccp1_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable CCP1 Module */
        CCP1_DISABLE_MODULE();
        /* Disable CCP1 Module Interrupt feature */
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP1_DisableInterrupt();
#endif
    }
    return errorState;
}

#if CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECT
Std_ReturnType MCCP1_is_compare_ready(uint8* compare_isReady){
    Std_ReturnType errorState = E_OK;
    if(NULL == compare_isReady){
        errorState = E_NOT_OK;
    }
    else{
        if(CCP1_COMPARE_NOT_READY == PIR1bits.CCP1IF){
            *compare_isReady = CCP1_COMPARE_NOT_READY;
        }
        else if(CCP1_COMPARE_READY == PIR1bits.CCP1IF){
            *compare_isReady = CCP1_COMPARE_READY;
        }
    }
    return errorState;
}

Std_ReturnType MCCP1_set_value_to_compare(uint16 ccp1_compareValue){
    Std_ReturnType errorState = E_OK;
    Un_CCP1_register_t temp_ccp_reg = {.CCP1R16 = ZERO_INIT};
    temp_ccp_reg.CCP1R16 = ccp1_compareValue;
    CCPR1L = temp_ccp_reg.CCP1RL;
    CCPR1H = temp_ccp_reg.CCP1RH;
    return errorState;
}

#elif CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECT
Std_ReturnType MCCP1_is_capture_ready(uint8* capture_isReady){
    Std_ReturnType errorState = E_OK;
    if(NULL == capture_isReady){
        errorState = E_NOT_OK;
    }
    else{
        if(CCP1_CAPTURE_NOT_READY == PIR1bits.CCP1IF){
            *capture_isReady = CCP1_CAPTURE_NOT_READY;
        }
        else if(CCP1_CAPTURE_READY == PIR1bits.CCP1IF){
            *capture_isReady = CCP1_CAPTURE_READY;
        }
    }
    return errorState;
}

Std_ReturnType MCCP1_read_capture_value(uint16* ccp1_captureValue){
    Std_ReturnType errorState = E_OK;
    Un_16bits_register_t temp_ccp_reg = {.REG16 = ZERO_INIT};
    if(NULL == ccp1_captureValue){
        errorState = E_NOT_OK;
    }
    else{
        temp_ccp_reg.LSbits8 = CCPR1L;
        temp_ccp_reg.MSbits8 = CCPR1H;
        *ccp1_captureValue = temp_ccp_reg.REG16;
    }
    return errorState;
}

#elif CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECT
Std_ReturnType MCCP1_set_PWM_duty_cycle(uint8 duty_value){
    Std_ReturnType errorState = E_OK;
    uint16 l_temp_duty_value = (uint16)(4*(PR2+1)*(duty_value/100.0));
    CCP1CONbits.DC1B = (uint8)(l_temp_duty_value & 0x0003);
    CCPR1L = (uint8)(l_temp_duty_value >> 2);
    return errorState;
}
Std_ReturnType MCCP1_start_PWM(void){
    Std_ReturnType errorState = E_OK;
    CCP1_SELECT_MODE(CCP1_PWM_MODE);
    return errorState;
}
Std_ReturnType MCCP1_stop_PWM(void){
    Std_ReturnType errorState = E_OK;
    CCP1_DISABLE_MODULE();
    return errorState;
}

#endif

void CCP1_ISR(void){
    if(CCP1_PtrTo_App_ISR){
        CCP1_PtrTo_App_ISR();
    }else { /* Nothing */}
}

static inline void CCP1_configure_interrupt(const St_CCP1_cfg_t* ccp1_cfg){
    CCP1_InterruptFlagClear();
    CCP1_PtrTo_App_ISR = ccp1_cfg->InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE
    INTERRUPT_EnableGlobalInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();
#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_EnableGlobalHighPriorityInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();    
    if(INTERRUPT_HIGH_PRIORITY == ccp1_cfg->interrupt_priority){ CCP1_SetToHighPriority(); }
    else if(INTERRUPT_LOW_PRIORITY == ccp1_cfg->interrupt_priority){ CCP1_SetToLowPriority(); }
    else{ /* Nothing */ }
#endif
}

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECT) || (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECT))
static inline void CCP_Timer_source_select(const St_CCP1_cfg_t* ccp1_cfg){
    if(CCP1_CCP2_TIMER1_SOURCE == ccp1_cfg->cpp_timer_select){
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3_SOURCE == ccp1_cfg->cpp_timer_select){
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_CCP2_TIMER3_SOURCE == ccp1_cfg->cpp_timer_select){
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 1;
    }
    else{/*Nothing*/}
}
#endif