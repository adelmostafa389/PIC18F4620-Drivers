/* 
 * File:   MCAL_external_Interrupt.c
 * Author: ADEL
 *
 * Created on June 10, 2022, 10:41 PM
 */

#include "MCAL_external_Interrupt.h"

PtrTo_func_t INT0_PtrTo_App_ISR;
PtrTo_func_t INT1_PtrTo_App_ISR;
PtrTo_func_t INT2_PtrTo_App_ISR;
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const St_interrupt_INTx_t* interrupt_object);
static Std_ReturnType Interrupt_INTx_enable(const St_interrupt_INTx_t* interrupt_object);
static Std_ReturnType Interrupt_INTx_disable(const St_interrupt_INTx_t* interrupt_object);
static Std_ReturnType Interrupt_INTx_init_pin(const St_interrupt_INTx_t* interrupt_object);
static Std_ReturnType Interrupt_INTx_init_priority(const St_interrupt_INTx_t* interrupt_object);
static Std_ReturnType Interrupt_INTx_init_edge(const St_interrupt_INTx_t* interrupt_object);
static Std_ReturnType Interrupt_INTx_clear_flag(const St_interrupt_INTx_t* interrupt_object);
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

PtrTo_func_t RB4_PtrTo_App_On_Rising_ISR;
PtrTo_func_t RB4_PtrTo_App_On_Falling_ISR;
PtrTo_func_t RB5_PtrTo_App_On_Rising_ISR;
PtrTo_func_t RB5_PtrTo_App_On_Falling_ISR;
PtrTo_func_t RB6_PtrTo_App_On_Rising_ISR;
PtrTo_func_t RB6_PtrTo_App_On_Falling_ISR;
PtrTo_func_t RB7_PtrTo_App_On_Rising_ISR;
PtrTo_func_t RB7_PtrTo_App_On_Falling_ISR;
static Std_ReturnType Interrupt_RBx_SetInterruptHandler(const St_interrupt_RBx_t* interrupt_object);
static Std_ReturnType Interrupt_RBx_init_priority(const St_interrupt_RBx_t* interrupt_object);
void RB4_ISR(uint8 source);
void RB5_ISR(uint8 source);
void RB6_ISR(uint8 source);
void RB7_ISR(uint8 source);


/**
 * 
 * @param interrupt_object
 * @return 
 */
Std_ReturnType MInterrupt_Initialize_INTx(const St_interrupt_INTx_t* interrupt_object){
    Std_ReturnType error_ret = E_OK;
    if(NULL == interrupt_object){
        error_ret = E_NOT_OK;
    }
    else{
        /* Disable the external interrupt*/
        error_ret = Interrupt_INTx_disable(interrupt_object);
        /* Clear the external interrupt flag */
        error_ret = Interrupt_INTx_clear_flag(interrupt_object);
        /* Configure interrupt pin */
        error_ret = Interrupt_INTx_init_pin(interrupt_object);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* Configure interrupt adc_interrupt_priority */
        error_ret = Interrupt_INTx_init_priority(interrupt_object);
        #endif
        /* Configure interrupt edge */
        error_ret = Interrupt_INTx_init_edge(interrupt_object);
        /* Configure default interrupt callback function */
        error_ret = Interrupt_INTx_SetInterruptHandler(interrupt_object);
        /* Enable the external interrupt */
        error_ret = Interrupt_INTx_enable(interrupt_object);
    }
    return error_ret;
}

/**
 * 
 * @param interrupt_object
 * @return 
 */
Std_ReturnType MInterrupt_Deinitialize_INTx(const St_interrupt_INTx_t* interrupt_object){
    Std_ReturnType error_ret = E_OK;
    if(NULL == interrupt_object){
        error_ret = E_NOT_OK;
    }
    else{
        Interrupt_INTx_disable(interrupt_object);
    }
    return error_ret;
}

/**
 * 
 * @param interrupt_object
 * @return 
 */
Std_ReturnType MInterrupt_Initialize_RBx(const St_interrupt_RBx_t* interrupt_object){
    Std_ReturnType error_ret = E_OK;
    if(NULL == interrupt_object){
        error_ret = E_NOT_OK;
    }
    else{
       /* Disable the external interrupt*/
        EXT_RBx_DisableInterrupt();
        /* Clear the external interrupt flag */
        EXT_RBx_ClearFlag();
        /* Configure interrupt pin */
        MGPIO_initialize_pin_direction(&(interrupt_object->mcu_pin));
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* Configure interrupt adc_interrupt_priority */
        Interrupt_RBx_init_priority(interrupt_object);
#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE
        INTERRUPT_EnableGlobalInterrupt();
        INTERRUPT_EnablePeripheralInterrupt();
#endif
        /* Configure default interrupt callback function */
        Interrupt_RBx_SetInterruptHandler(interrupt_object);
        /* Enable the external interrupt */
        EXT_RBx_EnableInterrupt();
    }
    return error_ret;
}

/**
 * 
 * @param interrupt_object
 * @return 
 */
Std_ReturnType MInterrupt_Deinitialize_RBx(const St_interrupt_RBx_t* interrupt_object){
    Std_ReturnType error_ret = E_OK;
    if(NULL == interrupt_object){
        error_ret = E_NOT_OK;
    }
    else{
        /* Disable the external interrupt*/
        EXT_RBx_DisableInterrupt();
        /* Clear the external interrupt flag */
        EXT_RBx_ClearFlag();
    }
    return error_ret;
}


/**
 * 
 * @param interrupt_object
 * @return 
 */
static Std_ReturnType Interrupt_INTx_enable(const St_interrupt_INTx_t* interrupt_object){
    Std_ReturnType error_ret = E_OK;
    if(NULL == interrupt_object){
        error_ret = E_NOT_OK;
    }
    else{
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_EnablePriorityLevels();
        if(INTERRUPT_LOW_PRIORITY == interrupt_object->adc_interrupt_priority)
        {INTERRUPT_EnableGlobalLowPriorityInterrupt(); }
        else if(INTERRUPT_HIGH_PRIORITY == interrupt_object->adc_interrupt_priority)
        { INTERRUPT_EnableGlobalHighPriorityInterrupt(); }
        else{ error_ret = E_NOT_OK; }
#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_INTERRUPT_FEATURE_DISABLE  
        INTERRUPT_EnableGlobalInterrupt();
        INTERRUPT_EnablePeripheralInterrupt();
#endif
        switch(interrupt_object->source){
            case EXT_INT0:
                EXT_INT0_EnableInterrupt();
                break;
            case EXT_INT1:
                EXT_INT1_EnableInterrupt();
                break;
            case EXT_INT2:
                EXT_INT2_EnableInterrupt();
                break;  
            default:error_ret = E_NOT_OK; break;
        }
    }
    return error_ret;
}

/**
 * 
 * @param interrupt_object
 * @return 
 */
static Std_ReturnType Interrupt_INTx_disable(const St_interrupt_INTx_t* interrupt_object){
    Std_ReturnType error_ret = E_OK;
    if(NULL == interrupt_object){
        error_ret = E_NOT_OK;
    }
    else{
        switch(interrupt_object->source){
            case EXT_INT0:
                EXT_INT0_DisableInterrupt();
                break;
            case EXT_INT1:
                EXT_INT1_DisableInterrupt();
                break;
            case EXT_INT2:
                EXT_INT2_DisableInterrupt();
                break;  
            default:error_ret = E_NOT_OK; break;    }
    }
    return error_ret;
}

/**
 * 
 * @param interrupt_object
 * @return 
 */
static Std_ReturnType Interrupt_INTx_init_pin(const St_interrupt_INTx_t* interrupt_object){
    Std_ReturnType error_ret = E_OK;
    if(NULL == interrupt_object){
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = MGPIO_initialize_pin_direction(&(interrupt_object->mcu_pin));
    }
    return error_ret;
}

/**
 * 
 * @param interrupt_object
 * @return 
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_init_priority(const St_interrupt_INTx_t* interrupt_object){
    Std_ReturnType error_ret = E_OK;
    if(NULL == interrupt_object){
        error_ret = E_NOT_OK;
    }
    else{
        switch(interrupt_object->source){
            case EXT_INT1:
                if(INTERRUPT_LOW_PRIORITY == interrupt_object->adc_interrupt_priority)
                { EXT_INT1_SetToLowPriority(); }
                else if(INTERRUPT_HIGH_PRIORITY == interrupt_object->adc_interrupt_priority)
                { EXT_INT1_SetToHighPriority(); }
                else{ error_ret = E_NOT_OK; }
                break;
            case EXT_INT2:
                if(INTERRUPT_LOW_PRIORITY == interrupt_object->adc_interrupt_priority)
                { EXT_INT2_SetToLowPriority(); }
                else if(INTERRUPT_HIGH_PRIORITY == interrupt_object->adc_interrupt_priority)
                { EXT_INT2_SetToHighPriority(); }
                else{ error_ret = E_NOT_OK; }
                break;  
            default:error_ret = E_NOT_OK; break;
        }
    }
    return error_ret;
}
#endif

/**
 * 
 * @param interrupt_object
 * @return 
 */
static Std_ReturnType Interrupt_INTx_init_edge(const St_interrupt_INTx_t* interrupt_object){
    Std_ReturnType error_ret = E_OK;
    if(NULL == interrupt_object){
        error_ret = E_NOT_OK;
    }
    else{
        switch(interrupt_object->source){
            case EXT_INT0:
                if(INTERRUPT_FALLING_EDGE == interrupt_object->edge)
                { EXT_INT0_InterruptOnFallingEdge(); }
                else if(INTERRUPT_RISING_EDGE == interrupt_object->edge)
                { EXT_INT0_InterruptOnRisingEdge(); }
                else{ error_ret = E_NOT_OK; }
                break;
            case EXT_INT1:
                if(INTERRUPT_FALLING_EDGE == interrupt_object->edge)
                { EXT_INT1_InterruptOnFallingEdge(); }
                else if(INTERRUPT_RISING_EDGE == interrupt_object->edge)
                { EXT_INT1_InterruptOnRisingEdge(); }
                else{ error_ret = E_NOT_OK; }
                break;
            case EXT_INT2:
                if(INTERRUPT_FALLING_EDGE == interrupt_object->edge)
                { EXT_INT2_InterruptOnFallingEdge(); }
                else if(INTERRUPT_RISING_EDGE == interrupt_object->edge)
                { EXT_INT2_InterruptOnRisingEdge(); }
                else{ error_ret = E_NOT_OK; }
                break;  
            default:error_ret = E_NOT_OK; break;
        }
    }
    return error_ret;
}

/**
 * 
 * @param interrupt_object
 * @return 
 */
static Std_ReturnType Interrupt_INTx_clear_flag(const St_interrupt_INTx_t* interrupt_object){
    Std_ReturnType error_ret = E_OK;
    if(NULL == interrupt_object){
        error_ret = E_NOT_OK;
    }
    else{
        switch(interrupt_object->source){
            case EXT_INT0:
                EXT_INT0_ClearFlag();
                break;
            case EXT_INT1:
                EXT_INT1_ClearFlag();
                break;
            case EXT_INT2:
                EXT_INT2_ClearFlag();
                break;  
            default:error_ret = E_NOT_OK; break;
        }
    }
    return error_ret;
}

/**
 * 
 * @param interrupt_object
 * @return 
 */
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const St_interrupt_INTx_t* interrupt_object){
    Std_ReturnType error_ret = E_OK;
    if(NULL == interrupt_object){
        error_ret = E_NOT_OK;
    }
    else{
        switch(interrupt_object->source){
            case EXT_INT0:
                INT0_PtrTo_App_ISR = (interrupt_object->EXT_InterruptHandler);
                break;
            case EXT_INT1:
                INT1_PtrTo_App_ISR = (interrupt_object->EXT_InterruptHandler);
                break;
            case EXT_INT2:
                INT2_PtrTo_App_ISR = (interrupt_object->EXT_InterruptHandler);
                break;  
            default:error_ret = E_NOT_OK; break;
        }
    }
    return error_ret;
}

static Std_ReturnType Interrupt_RBx_SetInterruptHandler(const St_interrupt_RBx_t* interrupt_object){
    Std_ReturnType error_ret = E_OK;
    if(NULL == interrupt_object){
        error_ret = E_NOT_OK;
    }
    else{
        switch(interrupt_object->mcu_pin.pin){
            case GPIO_PIN4:
                RB4_PtrTo_App_On_Falling_ISR = interrupt_object->EXT_On_Falling_InterruptHandler;
                RB4_PtrTo_App_On_Rising_ISR = interrupt_object->EXT_On_Rising_InterruptHandler;
                break;
            case GPIO_PIN5:
                RB5_PtrTo_App_On_Falling_ISR = interrupt_object->EXT_On_Falling_InterruptHandler;
                RB5_PtrTo_App_On_Rising_ISR = interrupt_object->EXT_On_Rising_InterruptHandler;
                break;
            case GPIO_PIN6:
                RB6_PtrTo_App_On_Falling_ISR = interrupt_object->EXT_On_Falling_InterruptHandler;
                RB6_PtrTo_App_On_Rising_ISR = interrupt_object->EXT_On_Rising_InterruptHandler;
                break;
            case GPIO_PIN7:
                RB7_PtrTo_App_On_Falling_ISR = interrupt_object->EXT_On_Falling_InterruptHandler;
                RB7_PtrTo_App_On_Rising_ISR = interrupt_object->EXT_On_Rising_InterruptHandler;
                break;
            default:error_ret = E_NOT_OK; break;
        }
    }
    return error_ret;
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_RBx_init_priority(const St_interrupt_RBx_t* interrupt_object){
    Std_ReturnType error_ret = E_OK;
    if(NULL == interrupt_object){
        error_ret = E_NOT_OK;
    }
    else{
        INTERRUPT_EnablePriorityLevels();
        switch(interrupt_object->adc_interrupt_priority){
            case INTERRUPT_HIGH_PRIORITY:
                INTERRUPT_EnableGlobalHighPriorityInterrupt();
                EXT_RBx_SetToHighPriority();
                break;
            case INTERRUPT_LOW_PRIORITY:
                INTERRUPT_EnableGlobalLowPriorityInterrupt();
                EXT_RBx_SetToLowPriority();
                break;
            default:error_ret = E_NOT_OK; break;
        }
    }
    return error_ret;
}
#endif

void INT0_ISR(void){
    /* Application callback function gets called every time this ISR execute */
    if(NULL != INT0_PtrTo_App_ISR){
        INT0_PtrTo_App_ISR();
    }
    else{ /* Nothing */ }
}

void INT1_ISR(void){
    /* Application callback function gets called every time this ISR execute */
    if(NULL != INT1_PtrTo_App_ISR){
        INT1_PtrTo_App_ISR();
    }
    else{ /* Nothing */ }
}

void INT2_ISR(void){
    /* Application callback function gets called every time this ISR execute */
    if(NULL != INT2_PtrTo_App_ISR){
        INT2_PtrTo_App_ISR();
    }
    else{ /* Nothing */ }
}


void RB4_ISR(uint8 source){
    /* Application callback function gets called every time this ISR execute */
    if(1 == source){
        if(NULL != RB4_PtrTo_App_On_Falling_ISR){
            RB4_PtrTo_App_On_Falling_ISR();
        }
        else{ /* Nothing */ }
    }
    else if(0 == source){
        if(NULL != RB4_PtrTo_App_On_Rising_ISR){
            RB4_PtrTo_App_On_Rising_ISR();
        }
        else{ /* Nothing */ }
    }
}

void RB5_ISR(uint8 source){
    /* Application callback function gets called every time this ISR execute */
    if(1 == source){
        if(NULL != RB5_PtrTo_App_On_Falling_ISR){
            RB5_PtrTo_App_On_Falling_ISR();
        }
        else{ /* Nothing */ }
    }
    else if(0 == source){
        if(NULL != RB5_PtrTo_App_On_Rising_ISR){
            RB5_PtrTo_App_On_Rising_ISR();
        }
        else{ /* Nothing */ }
    }
}

void RB6_ISR(uint8 source){
    /* Application callback function gets called every time this ISR execute */
    if(1 == source){
        if(NULL != RB6_PtrTo_App_On_Falling_ISR){
            RB6_PtrTo_App_On_Falling_ISR();
        }
        else{ /* Nothing */ }
    }
    else if(0 == source){
        if(NULL != RB6_PtrTo_App_On_Rising_ISR){
            RB6_PtrTo_App_On_Rising_ISR();
        }
        else{ /* Nothing */ }
    }
}

void RB7_ISR(uint8 source){
    /* Application callback function gets called every time this ISR execute */
    if(1 == source){
        if(NULL != RB7_PtrTo_App_On_Falling_ISR){
            RB7_PtrTo_App_On_Falling_ISR();
        }
        else{ /* Nothing */ }
    }
    else if(0 == source){
        if(NULL != RB7_PtrTo_App_On_Rising_ISR){
            RB7_PtrTo_App_On_Rising_ISR();
        }
        else{ /* Nothing */ }
    }
}