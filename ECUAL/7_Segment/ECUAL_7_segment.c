/* 
 * File:   ECUAL_7_segment.c
 * Author: ADEL
 *
 * Created on June 3, 2022, 1:35 AM
 */


#include "ECUAL_7_segment.h"

/**
 * 
 * @param seg
 * @return 
 */
Std_ReturnType H7seg_initialize(const St_7seg_t* const seg){
    Std_ReturnType error_ret = E_OK;
    if(NULL == seg){
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = MGPIO_initialize_pin(&(seg->segment_pin0));
        error_ret = MGPIO_initialize_pin(&(seg->segment_pin1));
        error_ret = MGPIO_initialize_pin(&(seg->segment_pin2));
        error_ret = MGPIO_initialize_pin(&(seg->segment_pin3));
    }
    return error_ret;}

/**
 * 
 * @param seg
 * @param number
 * @return 
 */
Std_ReturnType H7seg_write(const St_7seg_t* const seg, uint8 number){
    Std_ReturnType error_ret = E_OK;
    
    if((NULL == seg) || (number > 9)){
        error_ret = E_NOT_OK;
    }
    else{
        /*
        uint8 segment_pin0_value = (number>>0 & 1);
        uint8 segment_pin1_value = (number>>1 & 1);
        uint8 segment_pin2_value = (number>>2 & 1);
        uint8 segment_pin3_value = (number>>3 & 1);         
         */
        error_ret = MGPIO_write_pin(&(seg->segment_pin0), (number>>0 & 1));
        error_ret = MGPIO_write_pin(&(seg->segment_pin1), (number>>1 & 1));
        error_ret = MGPIO_write_pin(&(seg->segment_pin2), (number>>2 & 1));
        error_ret = MGPIO_write_pin(&(seg->segment_pin3), (number>>3 & 1));
    }
    return error_ret;}

