/* 
 * File:   MCAL_CCP2.C
 * Author: ADEL
 *
 * Created on June 21, 2022, 10:48 AM
 */

#include "MCAL_CCP2.h"

PtrTo_func_t CCP2_PtrTo_App_ISR = NULL;
void CCP2_ISR(void);

static inline void CCP2_configure_interrupt(const St_CCP2_cfg_t* ccp2_cfg);
static inline void CCP_Timer_source_select(const St_CCP2_cfg_t* ccp2_cfg);

Std_ReturnType MCCP2_init(const St_CCP2_cfg_t* ccp2_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == ccp2_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable the CPP2 module */
        CCP2_DISABLE_MODULE();
        /* Select CPP2 mode(Compare/Capture/PWM) */
        CCP2_SELECT_MODE(ccp2_cfg->mode);
        /* CCP2 I/O pin configuration */
        errorState = MGPIO_initialize_pin(&(ccp2_cfg->ccp_pin));
        /*  */
#if CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECT
        CCP_Timer_source_select(&ccp2_cfg);
#elif CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECT
        CCP_Timer_source_select(&ccp2_cfg);
#elif CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECT
        /* Set Timer2 period register (PR2) value to generate PWM frequency */
        PR2 = (uint8)(_XTAL_FREQ/
                (ccp2_cfg->PWM_frequency * 4 * ccp2_cfg->timer2_prescaler_value));
#endif
        /* Configure the interrupt */
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP2_EnableInterrupt();
        CCP2_configure_interrupt(ccp2_cfg);
#endif
        errorState = E_OK;
    }
    return errorState;
}

Std_ReturnType MCCP2_deinit(const St_CCP2_cfg_t* ccp2_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == ccp2_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable CCP2 Module */
        CCP2_DISABLE_MODULE();
        /* Disable CCP2 Module Interrupt feature */
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP2_DisableInterrupt();
#endif
    }
    return errorState;
}

#if CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECT
Std_ReturnType MCCP2_is_compare_ready(uint8* compare_isReady){
    Std_ReturnType errorState = E_OK;
    if(NULL == compare_isReady){
        errorState = E_NOT_OK;
    }
    else{
        if(CCP2_COMPARE_NOT_READY == PIR2bits.CCP2IF){
            *compare_isReady = CCP2_COMPARE_NOT_READY;
        }
        else if(CCP2_COMPARE_READY == PIR2bits.CCP2IF){
            *compare_isReady = CCP2_COMPARE_READY;
        }
    }
    return errorState;
}

Std_ReturnType MCCP2_set_value_to_compare(uint16 ccp2_compareValue){
    Std_ReturnType errorState = E_OK;
    Un_CCP2_register_t temp_ccp_reg = {.CCP2R16 = ZERO_INIT};
    temp_ccp_reg.CCP2R16 = ccp2_compareValue;
    CCPR2L = temp_ccp_reg.CCP2RL;
    CCPR2H = temp_ccp_reg.CCP2RH;
    return errorState;
}

#elif CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECT
Std_ReturnType MCCP2_is_capture_ready(uint8* capture_isReady){
    Std_ReturnType errorState = E_OK;
    if(NULL == capture_isReady){
        errorState = E_NOT_OK;
    }
    else{
        if(CCP2_CAPTURE_NOT_READY == PIR2bits.CCP2IF){
            *capture_isReady = CCP2_CAPTURE_NOT_READY;
        }
        else if(CCP2_CAPTURE_READY == PIR2bits.CCP2IF){
            *capture_isReady = CCP2_CAPTURE_READY;
        }
    }
    return errorState;
}

Std_ReturnType MCCP2_read_capture_value(uint16* ccp2_captureValue){
    Std_ReturnType errorState = E_OK;
    Un_16bits_register_t temp_ccp_reg = {.REG16 = ZERO_INIT};
    if(NULL == ccp2_captureValue){
        errorState = E_NOT_OK;
    }
    else{
        temp_ccp_reg.LSbits8 = CCPR2L;
        temp_ccp_reg.MSbits8 = CCPR2H;
        *ccp2_captureValue = temp_ccp_reg.REG16;
    }
    return errorState;
}

#elif CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECT
Std_ReturnType MCCP2_set_PWM_duty_cycle(uint8 duty_value){
    Std_ReturnType errorState = E_OK;
    uint16 l_temp_duty_value = (uint16)(4*(PR2+1)*(duty_value/100.0));
    CCP2CONbits.DC2B = (uint8)(l_temp_duty_value & 0x0003);
    CCPR2L = (uint8)(l_temp_duty_value >> 2);
    return errorState;
}
Std_ReturnType MCCP2_start_PWM(void){
    Std_ReturnType errorState = E_OK;
    CCP2_SELECT_MODE(CCP2_PWM_MODE);
    return errorState;
}
Std_ReturnType MCCP2_stop_PWM(void){
    Std_ReturnType errorState = E_OK;
    CCP2_DISABLE_MODULE();
    return errorState;
}

#endif

void CCP2_ISR(void){
    if(CCP2_PtrTo_App_ISR){
        CCP2_PtrTo_App_ISR();
    }else { /* Nothing */}
}

static inline void CCP2_configure_interrupt(const St_CCP2_cfg_t* ccp2_cfg){
    CCP2_InterruptFlagClear();
    CCP2_PtrTo_App_ISR = ccp2_cfg->InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE
    INTERRUPT_EnableGlobalInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();
#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_EnableGlobalHighPriorityInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();    
    if(INTERRUPT_HIGH_PRIORITY == ccp2_cfg->interrupt_priority){ CCP2_SetToHighPriority(); }
    else if(INTERRUPT_LOW_PRIORITY == ccp2_cfg->interrupt_priority){ CCP2_SetToLowPriority(); }
    else{ /* Nothing */ }
#endif
}


#if ((CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECT) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECT))
static inline void CCP_Timer_source_select(const St_CCP2_cfg_t* ccp2_cfg){
    if(CCP1_CCP2_TIMER1_SOURCE == ccp2_cfg->cpp_timer_select){
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3_SOURCE == ccp2_cfg->cpp_timer_select){
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_CCP2_TIMER3_SOURCE == ccp2_cfg->cpp_timer_select){
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 1;
    }
    else{/*Nothing*/}
}
#endif