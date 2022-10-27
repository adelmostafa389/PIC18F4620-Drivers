/* 
 * File:   MCAL_USART.h
 * Author: ADEL
 *
 * Created on June 24, 2022, 6:53 PM
 */

#ifndef MCAL_USART_H
#define	MCAL_USART_H



/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include <xc.h>
#include "../MCAL_STD_TYPES.h"
#include "../GPIO/MCAL_GPIO.h"
#include "../Interrupt/MCAL_interanl_Interrupt.h"
#include "MCAL_USART_config.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

/* Enable / Disable EUSART Module */
#define EUSART_MODULE_ENABLE   1
#define EUSART_MODULE_DISABLE  0

/* Selecting EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE  		1
#define EUSART_ASYNCHRONOUS_MODE 		0
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSART_ASYNCHRONOUS_LOW_SPEED  	0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN  		1
#define EUSART_08BIT_BAUDRATE_GEN  		0

/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE  0
/* EUSART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE  0
/* check if TXREG is empty(ready for the next char) */
#define TXREG_IS_EMPTY                  1
#define TXREG_IS_FULL                   0
/* EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_RX_DISABLE  0
/* EUSART 9-Bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE  0
/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED 1
#define EUSART_FRAMING_ERROR_CLEARED  0
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0
 
/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/


/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/
typedef enum{
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,   
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}St_baudrate_gen_t;

typedef struct{
    En_interrupt_priority_t usart_tx_int_priority;
	uint8 usart_tx_enable : 1;
	uint8 usart_tx_9bit_enable : 1;
    uint8 reserved : 5;
}St_USART_tx_cfg_t;

typedef struct{
    En_interrupt_priority_t usart_rx_int_priority;
	uint8 usart_rx_enable : 1;
	uint8 usart_rx_9bit_enable : 1;
    uint8 reserved : 5;
}St_USART_rx_cfg_t;

typedef union{
	struct{
		uint8 reserved : 6;
		uint8 usart_ferr : 1;
		uint8 usart_oerr : 1;
	};
	uint8 status;
}St_USART_error_status_t;

typedef struct{
    uint32 baudrate;
    St_baudrate_gen_t baudrate_gen_gonfig;
    St_USART_tx_cfg_t usart_tx_cfg;
	St_USART_rx_cfg_t usart_rx_cfg;
	St_USART_error_status_t error_status;
	PtrTo_func_t EUSART_TxDefaultInterruptHandler;
    PtrTo_func_t EUSART_RxDefaultInterruptHandler;
    PtrTo_func_t EUSART_FramingErrorHandler;
    PtrTo_func_t EUSART_OverrunErrorHandler;
}St_USART_conf_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

Std_ReturnType MEUSART_ASYNC_Init(const St_USART_conf_t* usart_cfg);
Std_ReturnType MEUSART_ASYNC_DeInit(const St_USART_conf_t* usart_cfg);

Std_ReturnType MEUSART_ASYNC_ReadByteBlocking(uint8* data);
Std_ReturnType MEUSART_ASYNC_ReadByteNonBlocking(uint8* data);
Std_ReturnType MEUSART_ASYNC_RX_Restart(void);

Std_ReturnType MEUSART_ASYNC_WriteByteBlocking(uint8 data);
Std_ReturnType MEUSART_ASYNC_WriteStringBlocking(uint8* data, uint8 str_len);
Std_ReturnType MEUSART_ASYNC_WriteByteNonBlocking(uint8 data);
Std_ReturnType MEUSART_ASYNC_WriteStringNonBlocking(uint8* data, uint8 str_len);

#endif	/* MCAL_USART_H */

