/* 
 * File:   MCAL_GPIO.h
 * Author: ADEL
 *
 * Created on May 27, 2022, 2:35 PM
 */

#ifndef MCAL_GPIO_H
#define	MCAL_GPIO_H


/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/

#include <xc.h>
#include "../MCAL_STD_TYPES.h"
#include "../device_config.h"
#include "MCAL_GPIO_config.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/
#define BIT_MASK (uint8)1

#define PORT_MAX_PIN_NUM 8
#define MAX_PORT_NUM     5

#define GPIO_PORT_PIN_CONFIGURATIONS   CONFIG_ENABLE
#define GPIO_PORT_CONFIGURATIONS       CONFIG_ENABLE

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/
#define HWREG8(_X)         (*((volatile uint8* )(_X)))

#define SET_BIT(REG, BIT_POSN)        (REG |= (1 << BIT_POSN))
#define CLEAR_BIT(REG, BIT_POSN)      (REG &= ~(1 << BIT_POSN))
#define TOGGLE_BIT(REG, BIT_POSN)     (REG ^= (1 << BIT_POSN))
#define READ_BIT(REG, BIT_POSN)       ((REG >> BIT_POSN) & BIT_MASK)

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/
typedef enum{
    LOW = 0,
    HIGH
}En_logic_t;

typedef enum{
    OUTPUT = 0,
    INPUT
}En_direction_t;

typedef enum{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
}En_pin_index_t;

typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}En_port_index_t;

typedef struct{
    uint8 port : 3;                 /* @ref En_port_index_t */
    uint8 pin  : 3;                 /* @ref En_pin_index_t */
    uint8 direction : 1;            /* @ref En_direction_t */
    uint8 initial_value : 1;        /* @ref En_logic_t */
}St_pin_config_t;

/********************************************************************************************/
/*                             Function Declarations "APIs"                                 */
/********************************************************************************************/
Std_ReturnType MGPIO_initialize_pin_direction(const St_pin_config_t* _pin_config);
Std_ReturnType MGPIO_get_pin_direction(const St_pin_config_t* _pin_config, En_direction_t* direction_status);
Std_ReturnType MGPIO_write_pin(const St_pin_config_t* _pin_config, En_logic_t logic);
Std_ReturnType MGPIO_read_pin(const St_pin_config_t* _pin_config, En_logic_t* logic);
Std_ReturnType MGPIO_toggle_pin(const St_pin_config_t* _pin_config);
Std_ReturnType MGPIO_initialize_pin(const St_pin_config_t* _pin_config);


Std_ReturnType MGPIO_initialize_port_direction(En_port_index_t port, uint8 direction);
Std_ReturnType MGPIO_get_port_direction(En_port_index_t port, uint8* direction_status);
Std_ReturnType MGPIO_write_port(En_port_index_t port, En_logic_t logic);
Std_ReturnType MGPIO_read_port(En_port_index_t port, En_logic_t* logic);
Std_ReturnType MGPIO_toggle_port(En_port_index_t port);

#endif	/* MCAL_GPIO_H */

