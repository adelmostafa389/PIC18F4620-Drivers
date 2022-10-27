/* 
 * File:   ECUAL_Chr_LCD.h
 * Author: ADEL
 *
 * Created on June 6, 2022, 11:26 PM
 */

#ifndef ECUAL_CHR_LCD_H
#define	ECUAL_CHR_LCD_H

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "../../MCAL/GPIO/MCAL_GPIO.h"
#include "ECUAL_Chr_LCD_config.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/
#define LCD_CLEAR                              0x01
#define LCD_RETURN_HOME                        0x02
#define LCD_ENTRY_MODE                         0x06
#define LCD_DISPLAY_OFF_CURSURE_OFF_BLINK_OFF  0x08
#define LCD_DISPLAY_ON_CURSURE_OFF_BLINK_OFF   0x0C
#define LCD_DISPLAY_ON_CURSURE_OFF_BLINK_ON    0x0D
#define LCD_DISPLAY_ON_CURSURE_ON_BLINK_OFF    0x0E
#define LCD_DISPLAY_ON_CURSURE_ON_BLINK_ON     0x0F
#define LCD_SHIFT_DISPLAY_LEFT                 0x18
#define LCD_SHIFT_DISPLAY_RIGHT                0x1C
#define LCD_4BIT_MODE_2LINES                   0x28
#define LCD_8BIT_MODE_2LINES                   0x38
#define LCD_CGRAM_START                        0x40
#define LCD_DDRAM_START                        0x80

#define ROW1  1
#define ROW2  2
#define ROW3  3
#define ROW4  4

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/
typedef struct{
    St_pin_config_t lcd_rs;
    St_pin_config_t lcd_en;
    St_pin_config_t lcd_data[4];
}St_chr_lcd_4bit_t;

typedef struct{
    St_pin_config_t lcd_rs;
    St_pin_config_t lcd_en;
    St_pin_config_t lcd_data[8];
}St_chr_lcd_8bit_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/
Std_ReturnType HLcd_4bit_init(const St_chr_lcd_4bit_t* lcd);
Std_ReturnType HLcd_4bit_send_command(const St_chr_lcd_4bit_t* lcd, uint8 command);
Std_ReturnType HLcd_4bit_send_char_data(const St_chr_lcd_4bit_t* lcd, uint8 data);
Std_ReturnType HLcd_4bit_send_char_data_pos(const St_chr_lcd_4bit_t* lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType HLcd_4bit_send_string(const St_chr_lcd_4bit_t* lcd, uint8 str[]);
Std_ReturnType HLcd_4bit_send_string_pos(const St_chr_lcd_4bit_t* lcd, uint8 row, uint8 column, uint8 str[]);
Std_ReturnType HLcd_4bit_send_custom_char(const St_chr_lcd_4bit_t* lcd, uint8 row, uint8 column, uint8 custom_char[], uint8 mem_pos);

Std_ReturnType HLcd_8bit_init(const St_chr_lcd_8bit_t* lcd);
Std_ReturnType HLcd_8bit_send_command(const St_chr_lcd_8bit_t* lcd, uint8 command);
Std_ReturnType HLcd_8bit_send_char_data(const St_chr_lcd_8bit_t* lcd, uint8 data);
Std_ReturnType HLcd_8bit_send_char_data_pos(const St_chr_lcd_8bit_t* lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType HLcd_8bit_send_string(const St_chr_lcd_8bit_t* lcd, uint8 str[]);
Std_ReturnType HLcd_8bit_send_string_pos(const St_chr_lcd_8bit_t* lcd, uint8 row, uint8 column, uint8 str[]);
Std_ReturnType HLcd_8bit_send_custom_char(const St_chr_lcd_8bit_t* lcd, uint8 row, uint8 column, uint8 custom_char[], uint8 mem_pos);


Std_ReturnType convert_uint8_to_string(uint8 value, uint8 str[]);
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 str[]);
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 str[]);


#endif	/* ECUAL_CHR_LCD_H */

