/* 
 * File:   hal_adc.c
 * Author: Ahmed Abd El-Ghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 * Created on March 26, 2021, 7:21 PM
 */

#include "MCAL_ADC.h"

PtrTo_func_t ADC_PtrTo_App_ISR = NULL;
void ADC_ISR(void);

static inline void adc_init_ANx_pin_to_input(En_adc_channel_select_t channel);
static inline void adc_configure_interrupt(const St_ADC_conf_t* adc_cfg);

/**
 * @Summary Initializes the ADC
 * @Description This routine initializes the ADC.
 *              This routine must be called before any other ADC routine is called.
 *              This routine should only be called once during system initialization.
 * @Preconditions None
 * @param  adc_cfg Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MADC_Init(const St_ADC_conf_t *adc_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == adc_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE();
        /* Configure the acquisition time */
        ADC_SET_AQUISITION_TIME(adc_cfg->acquisition_time);
        /* Configure the conversion clock */
        ADC_SELECT_CONVERSION_CLOCK(adc_cfg->conversion_clock);
        /* Configure the default channel */
        errorState = MADC_SelectChannel(adc_cfg->default_channel);
        /* Configure the interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_EnableInterrupt();
        adc_configure_interrupt(adc_cfg);        
#endif
        /* Configure the result format */
        ADC_SET_RESULT_FORMAT(adc_cfg->result_format);
        /* Configure the voltage reference */
        ADC_CHOOSE_EXTERNAL_VREF(adc_cfg->voltage_reference);
        /* Enable the ADC */
        ADC_CONVERTER_ENABLE();
        errorState = E_OK;
    }
    return errorState;
}

/**
 * @Summary De-Initializes the ADC
 * @param adc_cfg Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_DeInit(const St_ADC_conf_t *adc_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == adc_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE();
        /* Disable the interrupt */
        #if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_DisableInterrupt();
        #endif
        errorState = E_OK;
    }
    return errorState;
}

/**
 * @Summary Allows selection of a channel for conversion
 * @Description This routine is used to select desired channel for conversion.
 * @Preconditions MADC_Init() function should have been called before calling this function.
 * @param adc_cfg Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MADC_SelectChannel(En_adc_channel_select_t channel){
    Std_ReturnType errorState = E_OK;
    /* Configure the default channel */
    ADC_PINS_ANALOG_DIGITAL_CONFIG(channel);
    ADC_SELECT_CHANNEL(channel);
    adc_init_ANx_pin_to_input(channel);
    return errorState;
}

/**
 * @Summary Starts conversion
 * @Description This routine is used to start conversion of desired channel.
 * @Preconditions MADC_Init() function should have been called before calling this function.
 * @param adc_cfg Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MADC_StartConversion(const St_ADC_conf_t *adc_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == adc_cfg){
        errorState = E_NOT_OK;
    }
    else{
        ADC_START_CONVERSION();
        errorState = E_OK;
    }
    return errorState;
}

/**
 * @Summary Returns true when the conversion is completed otherwise false.
 * @Description This routine is used to determine if conversion is completed.
 *              When conversion is complete routine returns true. It returns false otherwise.
 * @Preconditions MADC_Init() function should have been called before calling this function.
 *                MADC_StartConversion() should have been called before calling this function.
 * @param adc_cfg Pointer to the ADC configurations
 * @param conversion_status The conversion status
 *          true  - If conversion is complete
 *          false - If conversion is not completed
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MADC_IsConversionDone(const St_ADC_conf_t *adc_cfg, uint8 *conversion_status){
    Std_ReturnType errorState = E_OK;
    if((NULL == adc_cfg) || (NULL == conversion_status)){
        errorState = E_NOT_OK;
    }
    else{
        *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
        errorState = E_OK;
    }
    return errorState;
}

/**
 * @Summary Returns the ADC conversion value.
 * @Description This routine is used to get the analog to digital converted value.
 *              This routine gets converted values from the channel specified.
 * @Preconditions   This routine returns the conversion value only after the conversion is complete.
 *                  Completion status can be checked using MADC_IsConversionDone() routine.
 * @param adc_cfg Pointer to the ADC configurations
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MADC_GetConversionResult(const St_ADC_conf_t *adc_cfg, uint16 *conversion_result){
    Std_ReturnType errorState = E_OK;
    if((NULL == adc_cfg) || (NULL == conversion_result)){
        errorState = E_NOT_OK;
    }
    else{
        if(ADC_RESULT_RIGHT == adc_cfg->result_format){
            *conversion_result = (uint16)((ADRESH << 8) + ADRESL);
        }
        else if(ADC_RESULT_LEFT == adc_cfg->result_format){
            *conversion_result = (uint16)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else{
            *conversion_result = (uint16)((ADRESH << 8) + ADRESL);
        }
        errorState = E_OK;
    }
    return errorState;
}

/**
 * @Summary Returns the ADC conversion value, also allows selection of a channel for conversion.
 * @Description This routine is used to select desired channel for conversion.
 *              This routine is get the analog to digital converted value.
 * @Preconditions MADC_Init() function should have been called before calling this function.
 * @param adc_cfg Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MADC_GetConversion_Blocking(const St_ADC_conf_t *adc_cfg, En_adc_channel_select_t channel, 
                                 uint16 *conversion_result){
    Std_ReturnType errorState = E_OK;
    if((NULL == adc_cfg) || (NULL == conversion_result)){
        errorState = E_NOT_OK;
    }
    else{
        /* select the A/D channel */
        errorState = MADC_SelectChannel(channel);
        /* Start the conversion */
        errorState = MADC_StartConversion(adc_cfg);
        /* Check if conversion is completed */
        while(ADCON0bits.GO_nDONE);
        errorState = MADC_GetConversionResult(adc_cfg, conversion_result);
    }
    return errorState;
}

/**
 * 
 * @param adc_cfg
 * @param channel
 * @return 
 */
Std_ReturnType MADC_StartConversion_Interrupt(const St_ADC_conf_t *adc_cfg, En_adc_channel_select_t channel){
    Std_ReturnType errorState = E_OK;
    if(NULL == adc_cfg){
        errorState = E_NOT_OK;
    }
    else{
        ADC_InterruptFlagClear();
        /* select the A/D channel */
        errorState = MADC_SelectChannel(channel);
        /* Start the conversion */
        errorState = MADC_StartConversion(adc_cfg);
        errorState = E_OK;
    }
    return errorState;
}

static inline void adc_init_ANx_pin_to_input(En_adc_channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0 : SET_BIT(TRISA, 0); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN1 : SET_BIT(TRISA, 1); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN2 : SET_BIT(TRISA, 2); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN3 : SET_BIT(TRISA, 3); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN4 : SET_BIT(TRISA, 5); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN5 : SET_BIT(TRISE, 0); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN6 : SET_BIT(TRISE, 1); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN7 : SET_BIT(TRISE, 2); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN8 : SET_BIT(TRISB, 2); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN9 : SET_BIT(TRISB, 3); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB, 1); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB, 4); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB, 0); break; /* Disable the digital output driver */
        default : /* Nothing */;
    }
}

void ADC_ISR(void){
    if(ADC_PtrTo_App_ISR){
        ADC_PtrTo_App_ISR();
    }else { /* Nothing */}
}


static inline void adc_configure_interrupt(const St_ADC_conf_t* adc_cfg){
    ADC_InterruptFlagClear();
    ADC_PtrTo_App_ISR = adc_cfg->InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE
    INTERRUPT_EnableGlobalInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();
#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_EnableGlobalHighPriorityInterrupt();
    INTERRUPT_EnablePeripheralInterrupt();    
    if(INTERRUPT_HIGH_PRIORITY == adc_cfg->interrupt_priority){ ADC_SetToHighPriority(); }
    else if(INTERRUPT_LOW_PRIORITY == adc_cfg->interrupt_priority){ ADC_SetToLowPriority(); }
    else{ /* Nothing */ }
#endif
}