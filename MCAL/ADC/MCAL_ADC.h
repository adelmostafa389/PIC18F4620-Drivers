/* 
 * File:   MCAL_ADC.h
 * Author: ADEL
 *
 * Created on June 14, 2022, 5:59 PM
 */

#ifndef MCAL_ADC_H
#define	MCAL_ADC_H


/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include <xc.h>
#include "../MCAL_STD_TYPES.h"
#include "../GPIO/MCAL_GPIO.h"
#include "../Interrupt/MCAL_interanl_Interrupt.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

#define ADC_AN0_ANALOG_FUNCTIONALITY  0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY  0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY  0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY  0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY  0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY  0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY  0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY  0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY  0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY  0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY 0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY 0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY 0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY  0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY 0x0F

#define ADC_RESULT_RIGHT              0x01U
#define ADC_RESULT_LEFT               0x00U

#define ADC_VOLTAGE_REFERENCE_ENABLE  0x01U
#define ADC_VOLTAGE_REFERENCE_DISABLE 0x00U

#define ADC_CONVERSION_COMPLETE          0
#define ADC_CONVERSION_IN_PROGRESS       1

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

/* A/D conversion status : conversion is in progress/ A/D idle */
#define ADC_READ_CONVERSION_STATUS()        (ADCON0bits.GO_DONE)
/* Start A/D conversion command */
#define ADC_START_CONVERSION()              (ADCON0bits.GO_DONE = 1)

/* Functions to enable or disable the ADC functionality */
#define ADC_CONVERTER_ENABLE()              (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE()             (ADCON0bits.ADON = 0)

/**
 * @Brief Set ADC result format stored in registers ADRES1 and ADRES2 to be RighT/left justified
 *   format can be ADC_RESULT_RIGHT (0x01) or ADC_RESULT_LEFT (0x00)
 */
#define ADC_SET_RESULT_FORMAT(format)       (ADCON2bits.ADFM = format)


/**
 * @Brief Set voltage reference of the ADC 
 *        when vref = ADC_VOLTAGE_REFERENCE_ENABLE  ADC reference voltage set to VREF-(AN2) and VREF+(AN3)
 *        when vref = ADC_VOLTAGE_REFERENCE_DISABLE ADC reference voltage set to VSS and VDD
 */
#define ADC_CHOOSE_EXTERNAL_VREF(vref)     do{ADCON1bits.VCFG0 = vref;\
                                              ADCON1bits.VCFG1 = vref;\
                                             }while(0)

/**
 * @Brierf Analog To Digital port configuration
 * @Example when passing ADC_AN4_ANALOG_FUNCTIONALITY:
 *          A0, A1, A2, A3 and A4 are all configured as analog input pins
 * @ref En_adc_channel_select_t
 */
#define ADC_PINS_ANALOG_DIGITAL_CONFIG(ADC_pinsConfig)    (ADCON1bits.PCFG = ADC_pinsConfig)


/**
 * @Brierf Analog To Digital port configuration
 * @ref En_adc_channel_select_t
 */
#define ADC_SELECT_CHANNEL(ADC_CHANNEL)    (ADCON0bits.CHS = ADC_CHANNEL)

/**
 * @Brierf Configure the acquisition time
 * @ref En_adc_acquisition_time_t
 */
#define ADC_SET_AQUISITION_TIME(TAD)    (ADCON2bits.ACQT = TAD)

/**
 * @Brierf Configure the conversion clock
 * @ref En_adc_channel_select_t
 */
#define ADC_SELECT_CONVERSION_CLOCK(CLOCK)    (ADCON2bits.ADCS = CLOCK)

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

/* @brief Analog Channel Select */
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,
}En_adc_channel_select_t;


typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,
}En_adc_acquisition_time_t;

typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64,
}En_adc_conversion_clock_t;

typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    En_interrupt_priority_t interrupt_priority;
#endif
#endif
    En_adc_channel_select_t default_channel;
    En_adc_acquisition_time_t acquisition_time;
    En_adc_conversion_clock_t conversion_clock;
    uint8 voltage_reference : 1;
    uint8 result_format : 1;
    uint8 reserved : 6;
}St_ADC_conf_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

/**
 * @Summary Initializes the ADC
 * @Description This routine initializes the ADC.
 *              This routine must be called before any other ADC routine is called.
 *              This routine should only be called once during system initialization.
 * @Preconditions None
 * @param adc_cfg Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MADC_Init(const St_ADC_conf_t *adc_cfg);

/**
 * @Summary De-Initializes the ADC
 * @param adc_cfg Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_DeInit(const St_ADC_conf_t *adc_cfg);

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
Std_ReturnType MADC_SelectChannel(En_adc_channel_select_t channel);

/**
 * @Summary Starts conversion
 * @Description This routine is used to start conversion of desired channel.
 * @Preconditions MADC_Init() function should have been called before calling this function.
 * @param adc_cfg Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType MADC_StartConversion(const St_ADC_conf_t *adc_cfg);

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
Std_ReturnType MADC_IsConversionDone(const St_ADC_conf_t *adc_cfg, uint8 *conversion_status);

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
Std_ReturnType MADC_GetConversionResult(const St_ADC_conf_t *adc_cfg, uint16 *conversion_result);

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
                                 uint16 *conversion_result);

/**
 * 
 * @param adc_cfg
 * @param channel
 * @return 
 */
Std_ReturnType MADC_StartConversion_Interrupt(const St_ADC_conf_t *adc_cfg, En_adc_channel_select_t channel);

#endif	/* MCAL_ADC_H */

