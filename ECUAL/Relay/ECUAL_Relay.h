/* 
 * File:   ECUAL_Relay.h
 * Author: ADEL
 *
 * Created on June 2, 2022, 3:20 AM
 */

#ifndef ECUAL_RELAY_H
#define	ECUAL_RELAY_H

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "ECUAL_Relay_config.h"
#include "../../MCAL/GPIO/MCAL_GPIO.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/
#define RELAY_ON_STATUS    0x01U
#define RELAY_OFF_STATUS   0x00U

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/
typedef struct{
    uint8 relay_port : 4;
    uint8 relay_pin : 3;
    uint8 relay_initial_status : 1;
}St_relay_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/
Std_ReturnType HRelay_initialize(const St_relay_t* relay);
Std_ReturnType HRelay_turn_on(const St_relay_t* relay);
Std_ReturnType HRelay_turn_off(const St_relay_t* relay);

#endif	/* ECUAL_RELAY_H */

