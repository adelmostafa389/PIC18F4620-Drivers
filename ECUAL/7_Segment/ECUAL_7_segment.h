/* 
 * File:   ECUAL_7_segment.h
 * Author: ADEL
 *
 * Created on June 3, 2022, 1:35 AM
 */

#ifndef ECUAL_7_SEGMENT_H
#define	ECUAL_7_SEGMENT_H

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "../../MCAL/GPIO/MCAL_GPIO.h"
#include "ECUAL_7_segment_config.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/
typedef enum{
    COMMON_ANODE,
    COMMON_CATHODE
}En_7seg_type_t;

typedef struct{
    St_pin_config_t segment_pin0;
    St_pin_config_t segment_pin1;
    St_pin_config_t segment_pin2;
    St_pin_config_t segment_pin3;
    En_7seg_type_t segment_type;
}St_7seg_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/
Std_ReturnType H7seg_initialize(const St_7seg_t* const seg);
Std_ReturnType H7seg_write(const St_7seg_t* const seg, uint8 number);



#endif	/* ECUAL_7_SEGMENT_H */

