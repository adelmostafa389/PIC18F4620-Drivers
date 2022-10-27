/* 
 * File:   ECU_layer_init.h
 * Author: ADEL
 *
 * Created on June 7, 2022, 9:23 AM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H



/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "LED/ECU_LED.h"
#include "Button/ECUAL_Button.h"
#include "DC_Motor/ECUAL_DC_Motor.h"
#include "7_Segment/ECUAL_7_segment.h"
#include "Keypad/ECUAL_Keypad.h"
#include "Relay/ECUAL_Relay.h"
#include "Chr_LCD/ECUAL_Chr_LCD.h"

/********************************************************************************************/
/*                                    ECUAL Devices Definitions                             */
/********************************************************************************************/

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/
Std_ReturnType application_initialize(void);

#endif	/* ECU_LAYER_INIT_H */

