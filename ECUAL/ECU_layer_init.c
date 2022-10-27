/* 
 * File:   ECU_layer_init.c
 * Author: ADEL
 *
 * Created on June 7, 2022, 9:23 AM
 */

#include "ECU_layer_init.h"

St_chr_lcd_4bit_t LCD_4bit = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = OUTPUT,
    .lcd_rs.initial_value = LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = OUTPUT,
    .lcd_en.initial_value = LOW,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = OUTPUT,
    .lcd_data[0].initial_value = LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = OUTPUT,
    .lcd_data[1].initial_value = LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = OUTPUT,
    .lcd_data[2].initial_value = LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = OUTPUT,
    .lcd_data[3].initial_value = LOW
};

St_chr_lcd_8bit_t LCD_8bit = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN6,
    .lcd_rs.direction = OUTPUT,
    .lcd_rs.initial_value = LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN7,
    .lcd_en.direction = OUTPUT,
    .lcd_en.initial_value = LOW,
    .lcd_data[0].port = PORTD_INDEX,
    .lcd_data[0].pin = GPIO_PIN0,
    .lcd_data[0].direction = OUTPUT,
    .lcd_data[0].initial_value = LOW,
    .lcd_data[1].port = PORTD_INDEX,
    .lcd_data[1].pin = GPIO_PIN1,
    .lcd_data[1].direction = OUTPUT,
    .lcd_data[1].initial_value = LOW,
    .lcd_data[2].port = PORTD_INDEX,
    .lcd_data[2].pin = GPIO_PIN2,
    .lcd_data[2].direction = OUTPUT,
    .lcd_data[2].initial_value = LOW,
    .lcd_data[3].port = PORTD_INDEX,
    .lcd_data[3].pin = GPIO_PIN3,
    .lcd_data[3].direction = OUTPUT,
    .lcd_data[3].initial_value = LOW,
    .lcd_data[4].port = PORTD_INDEX,
    .lcd_data[4].pin = GPIO_PIN4,
    .lcd_data[4].direction = OUTPUT,
    .lcd_data[4].initial_value = LOW,
    .lcd_data[5].port = PORTD_INDEX,
    .lcd_data[5].pin = GPIO_PIN5,
    .lcd_data[5].direction = OUTPUT,
    .lcd_data[5].initial_value = LOW,
    .lcd_data[6].port = PORTD_INDEX,
    .lcd_data[6].pin = GPIO_PIN6,
    .lcd_data[6].direction = OUTPUT,
    .lcd_data[6].initial_value = LOW,
    .lcd_data[7].port = PORTD_INDEX,
    .lcd_data[7].pin = GPIO_PIN7,
    .lcd_data[7].direction = OUTPUT,
    .lcd_data[7].initial_value = LOW
};

Std_ReturnType application_initialize(void){
    Std_ReturnType errorState = E_NOT_OK;
    //errorState = HLcd_4bit_init(&LCD_4bit);
    return errorState;
}
