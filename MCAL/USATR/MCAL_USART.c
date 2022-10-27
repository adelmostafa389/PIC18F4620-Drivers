/* 
 * File:   MCAL_USART.c
 * Author: ADEL
 *
 * Created on June 24, 2022, 6:53 PM
 */

#include "MCAL_USART.h"

PtrTo_func_t EUSART_TX_PtrTo_App_ISR = NULL;
PtrTo_func_t EUSART_RX_PtrTo_App_ISR = NULL;
PtrTo_func_t EUSART_FrameError_PtrTo_App_ISR = NULL;
PtrTo_func_t EUSART_OverRunError_PtrTo_App_ISR = NULL;

static void EUSART_ASYNC_configure_baud_rate(const St_USART_conf_t* usart_cfg);
static void EUSART_ASYNC_TX_Init(const St_USART_conf_t* usart_cfg);
static void EUSART_ASYNC_RX_Init(const St_USART_conf_t* usart_cfg);

Std_ReturnType MEUSART_ASYNC_Init(const St_USART_conf_t* usart_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == usart_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable the USART module */
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
        /* Initialize RC6/TX and RC7/RX pins as a USART */
        TRISCbits.RC6 = INPUT;
        TRISCbits.RC7 = INPUT;
        /* Configure Baud rate */
        EUSART_ASYNC_configure_baud_rate(usart_cfg);
        /* Initialize transmitter TX */
        EUSART_ASYNC_TX_Init(usart_cfg);
        /* Initialize receiver RX */
        EUSART_ASYNC_RX_Init(usart_cfg);
        /* Enable the USART module */
        RCSTAbits.SPEN = EUSART_MODULE_ENABLE;
    }
    return errorState;
}

Std_ReturnType MEUSART_ASYNC_DeInit(const St_USART_conf_t *usart_cfg){
    Std_ReturnType errorState = E_OK;
    if(NULL == usart_cfg){
        errorState = E_NOT_OK;
    }
    else{
        /* Disable the USART module */
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
    }
    return errorState;
}

Std_ReturnType MEUSART_ASYNC_ReadByteNonBlocking(uint8* data){
    Std_ReturnType errorState = E_OK;
    if(NULL == data){
        errorState = E_NOT_OK;
    }
    else{
        *data = RCREG;
    }
    return errorState;
}

Std_ReturnType MEUSART_ASYNC_RX_Restart(void){
    Std_ReturnType errorState = E_OK;
    /* Disables receiver */
    RCSTAbits.CREN = 0; 
    /* Enables receiver */
    RCSTAbits.CREN = 1; 
    return errorState;
}

Std_ReturnType MEUSART_ASYNC_WriteByteBlocking(uint8 data){
    Std_ReturnType ret = E_OK;
    while(!TXSTAbits.TRMT);
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EUSART_TX_EnableInterrupt();
#endif
    TXREG = data;
    return ret;
}

Std_ReturnType MEUSART_ASYNC_WriteStringBlocking(uint8* data, uint8 str_len){
    Std_ReturnType errorState = E_OK;
    uint8 char_counter = ZERO_INIT;
    if(NULL == data){
        errorState = E_NOT_OK;
    }
    else{
        for(char_counter = 0; char_counter < str_len; char_counter++){
            MEUSART_ASYNC_WriteByteBlocking(data[char_counter]);
        }
    }
    return errorState;
}

Std_ReturnType MEUSART_ASYNC_WriteByteNonBlocking(uint8 data){
    Std_ReturnType errorState = E_NOT_OK;
    TXREG = data;
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EUSART_TX_EnableInterrupt();
#endif
    return errorState;
}

Std_ReturnType MEUSART_ASYNC_WriteStringNonBlocking(uint8* data, uint8 str_len){
    Std_ReturnType errorState = E_NOT_OK;
    uint8 char_counter = ZERO_INIT;
    if(NULL == data){
        errorState = E_NOT_OK;
    }
    else{
        for(char_counter = 0; char_counter < str_len; char_counter++){
            MEUSART_ASYNC_WriteByteNonBlocking(data[char_counter]);
        }
    }
    return errorState;
}


static void EUSART_ASYNC_configure_baud_rate(const St_USART_conf_t* usart_cfg){
    float temp_baud_rate = ZERO_INIT;
    switch(usart_cfg->baudrate_gen_gonfig){
        case BAUDRATE_ASYN_8BIT_lOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            temp_baud_rate = ((_XTAL_FREQ/(64 * (float)(usart_cfg->baudrate)))-1);
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            temp_baud_rate = ((_XTAL_FREQ/(16 * (float)(usart_cfg->baudrate)))-1);
            break;
        case BAUDRATE_ASYN_16BIT_lOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            temp_baud_rate = ((_XTAL_FREQ/(16 * (float)(usart_cfg->baudrate)))-1);
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            temp_baud_rate = ((_XTAL_FREQ/(4 * (float)(usart_cfg->baudrate)))-1);
            break;
        case BAUDRATE_SYN_8BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            temp_baud_rate = ((_XTAL_FREQ/(4 * (float)(usart_cfg->baudrate)))-1);
            break;
        case BAUDRATE_SYN_16BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            temp_baud_rate = ((_XTAL_FREQ/(4 * (float)(usart_cfg->baudrate)))-1);
            break;
        default: break;
    }
    SPBRG = (uint8)((uint32)temp_baud_rate);
    SPBRGH = (uint8)(((uint32)temp_baud_rate) >> 8);
}

static void EUSART_ASYNC_TX_Init(const St_USART_conf_t* usart_cfg) {
    if(EUSART_ASYNCHRONOUS_TX_ENABLE == usart_cfg->usart_tx_cfg.usart_tx_enable){
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
        /* EUSART Transmit Interrupt Configuration */
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        EUSART_TX_EnableInterrupt();
        EUSART_TX_PtrTo_App_ISR = usart_cfg->EUSART_TxDefaultInterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE
        INTERRUPT_EnableGlobalInterrupt();
        INTERRUPT_EnablePeripheralInterrupt();
#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_EnableGlobalHighPriorityInterrupt();
        INTERRUPT_EnablePeripheralInterrupt();    
        if(INTERRUPT_HIGH_PRIORITY == usart_cfg->usart_tx_cfg.usart_tx_int_priority){ EUSART_TX_SetToHighPriority(); }
        else if(INTERRUPT_LOW_PRIORITY == usart_cfg->usart_tx_cfg.usart_tx_int_priority){ EUSART_TX_SetToLowPriority(); }
        else{ /* Nothing */ }
#endif
#endif
        /* EUSART 9-Bit Transmit Configuration */
        if(EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE == usart_cfg->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE == usart_cfg->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
        }
        else{ /* Nothing */}
    }
    else { /* Nothing */}
}

static void EUSART_ASYNC_RX_Init(const St_USART_conf_t* usart_cfg){
    if(EUSART_ASYNCHRONOUS_RX_ENABLE == usart_cfg->usart_rx_cfg.usart_rx_enable){
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
        /* EUSART Receive Interrupt Configuration */
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        EUSART_RX_EnableInterrupt();
        EUSART_RX_PtrTo_App_ISR = usart_cfg->EUSART_RxDefaultInterruptHandler;
        EUSART_FrameError_PtrTo_App_ISR = usart_cfg->EUSART_FramingErrorHandler;
        EUSART_OverRunError_PtrTo_App_ISR = usart_cfg->EUSART_OverrunErrorHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE
        INTERRUPT_EnableGlobalInterrupt();
        INTERRUPT_EnablePeripheralInterrupt();
#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_EnableGlobalHighPriorityInterrupt();
        INTERRUPT_EnablePeripheralInterrupt();    
        if(INTERRUPT_HIGH_PRIORITY == usart_cfg->usart_rx_cfg.usart_rx_int_priority){ EUSART_RX_SetToHighPriority(); }
        else if(INTERRUPT_LOW_PRIORITY == usart_cfg->usart_rx_cfg.usart_rx_int_priority){ EUSART_RX_SetToLowPriority(); }
        else{ /* Nothing */ }
#endif
#endif
        /* EUSART 9-Bit Receive Configuration */
        if(EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE == usart_cfg->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE == usart_cfg->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;
        }
        else{ /* Nothing */}
    }
    else { /* Nothing */}
}

void EUSART_TX_ISR(void){
    EUSART_TX_DisableInterrupt();
    if(EUSART_TX_PtrTo_App_ISR){
        EUSART_TX_PtrTo_App_ISR();
    }else { /* Nothing */ }
}

void EUSART_RX_ISR(void){
    if(EUSART_RX_PtrTo_App_ISR){
        EUSART_RX_PtrTo_App_ISR();
    }else { /* Nothing */}
    if(EUSART_FrameError_PtrTo_App_ISR){
        EUSART_FrameError_PtrTo_App_ISR();
    }else { /* Nothing */}
    if(EUSART_OverRunError_PtrTo_App_ISR){
        EUSART_OverRunError_PtrTo_App_ISR();
    }else { /* Nothing */}
}
