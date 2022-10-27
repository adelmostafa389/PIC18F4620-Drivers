/* 
 * File:   ECUAL_Chr_LCD.c
 * Author: ADEL
 *
 * Created on June 6, 2022, 11:26 PM
 */

#include "ECUAL_Chr_LCD.h"

static Std_ReturnType LCD_send_4bit(const St_chr_lcd_4bit_t* lcd, uint8 data);
static Std_ReturnType LCD_send_4bit_enable_signal(const St_chr_lcd_4bit_t* lcd);
static Std_ReturnType LCD_4bit_set_cursor(const St_chr_lcd_4bit_t* lcd, uint8 row, uint8 column);

static Std_ReturnType LCD_send_8bit_enable_signal(const St_chr_lcd_8bit_t* lcd);
static Std_ReturnType LCD_8bit_set_cursor(const St_chr_lcd_8bit_t* lcd, uint8 row, uint8 column);

Std_ReturnType HLcd_4bit_init(const St_chr_lcd_4bit_t* lcd){
    Std_ReturnType error_ret = E_OK;
    uint8 l_counter = ZERO_INIT;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = MGPIO_initialize_pin(&(lcd->lcd_rs));
        error_ret = MGPIO_initialize_pin(&(lcd->lcd_en));
        for(l_counter = 0; l_counter < 4; l_counter++){
            error_ret = MGPIO_initialize_pin(&(lcd->lcd_data[l_counter]));
        }
        __delay_ms(20);
        error_ret = HLcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        __delay_ms(5);
        error_ret = HLcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        __delay_us(150);
        error_ret = HLcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        error_ret = HLcd_4bit_send_command(lcd, LCD_CLEAR);   
        error_ret = HLcd_4bit_send_command(lcd, LCD_RETURN_HOME);   
        error_ret = HLcd_4bit_send_command(lcd, LCD_ENTRY_MODE);
        error_ret = HLcd_4bit_send_command(lcd, LCD_DISPLAY_ON_CURSURE_OFF_BLINK_OFF);
        error_ret = HLcd_4bit_send_command(lcd, LCD_4BIT_MODE_2LINES);
        error_ret = HLcd_4bit_send_command(lcd, 0x80);
    }
    return error_ret;
}

Std_ReturnType HLcd_4bit_send_command(const St_chr_lcd_4bit_t* lcd, uint8 command){
    Std_ReturnType error_ret = E_OK;
    uint8 l_counter = ZERO_INIT;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = MGPIO_write_pin(&(lcd->lcd_rs), LOW);
        error_ret = LCD_send_4bit(lcd, (command >> 4));
        error_ret = LCD_send_4bit_enable_signal(lcd);
        error_ret = LCD_send_4bit(lcd, command);
        error_ret = LCD_send_4bit_enable_signal(lcd);
    }
    return error_ret;
}

Std_ReturnType HLcd_4bit_send_char_data(const St_chr_lcd_4bit_t* lcd, uint8 data){
    Std_ReturnType error_ret = E_OK;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = MGPIO_write_pin(&(lcd->lcd_rs), HIGH);
        error_ret = LCD_send_4bit(lcd, (data >> 4));
        error_ret = LCD_send_4bit_enable_signal(lcd);
        error_ret = LCD_send_4bit(lcd, data);
        error_ret = LCD_send_4bit_enable_signal(lcd);
    }
    return error_ret;
}

Std_ReturnType HLcd_4bit_send_char_data_pos(const St_chr_lcd_4bit_t* lcd, uint8 row, uint8 column, uint8 data){
    Std_ReturnType error_ret = E_OK;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = LCD_4bit_set_cursor(lcd, row, column);
        error_ret = HLcd_4bit_send_char_data(lcd, data);
    }
    return error_ret;
}

Std_ReturnType HLcd_4bit_send_string(const St_chr_lcd_4bit_t* lcd, uint8 str[]){
    Std_ReturnType error_ret = E_OK;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
         while(*str){
            error_ret = HLcd_4bit_send_char_data(lcd, *str);
            str++;
        }
    }
    return error_ret;
}

Std_ReturnType HLcd_4bit_send_string_pos(const St_chr_lcd_4bit_t* lcd, uint8 row, uint8 column, uint8 str[]){
    Std_ReturnType error_ret = E_OK;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = LCD_4bit_set_cursor(lcd, row, column);
        while(*str){
            error_ret = HLcd_4bit_send_char_data(lcd, *str);
            str++;
        }
    }
    return error_ret;
}

Std_ReturnType HLcd_4bit_send_custom_char(const St_chr_lcd_4bit_t* lcd, uint8 row, uint8 column, uint8 custom_char[], uint8 mem_pos){
    Std_ReturnType error_ret = E_OK;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
        
    }
    return error_ret;
}


Std_ReturnType HLcd_8bit_init(const St_chr_lcd_8bit_t* lcd){
    Std_ReturnType error_ret = E_OK;
    uint8 l_counter = ZERO_INIT;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = MGPIO_initialize_pin(&(lcd->lcd_rs));
        error_ret = MGPIO_initialize_pin(&(lcd->lcd_en));
        for(l_counter = 0; l_counter < 8; l_counter++){
            error_ret = MGPIO_initialize_pin(&(lcd->lcd_data[l_counter]));
        }
        __delay_ms(20);
        error_ret = HLcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        __delay_ms(5);
        error_ret = HLcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        __delay_us(150);
        error_ret = HLcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINES);        
        error_ret = HLcd_8bit_send_command(lcd, LCD_CLEAR);        
        error_ret = HLcd_8bit_send_command(lcd, LCD_ENTRY_MODE);        
        error_ret = HLcd_8bit_send_command(lcd, LCD_DISPLAY_ON_CURSURE_OFF_BLINK_OFF);        
        error_ret = HLcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINES);        
        //error_ret = HLcd_8bit_send_command(lcd, 0x80);    
    }
    return error_ret;
}

Std_ReturnType HLcd_8bit_send_command(const St_chr_lcd_8bit_t* lcd, uint8 command){
    Std_ReturnType error_ret = E_OK;
    uint8 l_counter = ZERO_INIT;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = MGPIO_write_pin(&(lcd->lcd_rs), LOW);
        for(l_counter = 0; l_counter < 8; l_counter++){
            error_ret = MGPIO_write_pin(&(lcd->lcd_data[l_counter]), ((command >> l_counter)& (uint8)0x01));
        }
        error_ret = LCD_send_8bit_enable_signal(lcd);
    }
    return error_ret;
}

Std_ReturnType HLcd_8bit_send_char_data(const St_chr_lcd_8bit_t* lcd, uint8 data){
    Std_ReturnType error_ret = E_OK;
        uint8 l_counter = ZERO_INIT;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = MGPIO_write_pin(&(lcd->lcd_rs), HIGH);
        for(l_counter = 0; l_counter < 8; l_counter++){
            error_ret = MGPIO_write_pin(&(lcd->lcd_data[l_counter]), ((data >> l_counter)& (uint8)0x01));
        }
        error_ret = LCD_send_8bit_enable_signal(lcd);
    }
    return error_ret;
}

Std_ReturnType HLcd_8bit_send_char_data_pos(const St_chr_lcd_8bit_t* lcd, uint8 row, uint8 column, uint8 data){
    Std_ReturnType error_ret = E_OK;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = LCD_8bit_set_cursor(lcd, row, column);
        error_ret = HLcd_8bit_send_char_data(lcd, data);
    }
    return error_ret;
}

Std_ReturnType HLcd_8bit_send_string(const St_chr_lcd_8bit_t* lcd, uint8 str[]){
    Std_ReturnType error_ret = E_OK;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
        while(*str){
            error_ret = HLcd_8bit_send_char_data(lcd, *str);
        }
    }
    return error_ret;
}

Std_ReturnType HLcd_8bit_send_string_pos(const St_chr_lcd_8bit_t* lcd, uint8 row, uint8 column, uint8 str[]){
    Std_ReturnType error_ret = E_OK;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = LCD_8bit_set_cursor(lcd, row, column);
        while(*str){
            error_ret = HLcd_8bit_send_char_data(lcd, *str);
            str++;
        }
    }
    return error_ret;
}

Std_ReturnType HLcd_8bit_send_custom_char(const St_chr_lcd_8bit_t* lcd, uint8 row, uint8 column,
                                            uint8 custom_char[], uint8 mem_pos){
    Std_ReturnType error_ret = E_OK;
    uint8 l_counter = ZERO_INIT;
    if(NULL == lcd){ 
        error_ret = E_NOT_OK;
    }
    else{
        error_ret = HLcd_8bit_send_command(lcd, (LCD_CGRAM_START + (8*mem_pos)));
        for(l_counter = 0; l_counter < 8; l_counter++){
            error_ret = HLcd_8bit_send_char_data(lcd, custom_char[l_counter]);
        }
        error_ret = HLcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return error_ret;
}



Std_ReturnType convert_uint8_to_string(uint8 value, uint8 str[]){
    Std_ReturnType errorState = E_OK;
    uint8 counterOne_str[4];
    int i = 0;
    if(NULL == str){
        errorState = E_NOT_OK;
    }
    else{
        memset((char *)str, '\0', 4);
        sprintf(str, "%i", value);
    }    
    return errorState;
}

Std_ReturnType convert_uint16_to_string(uint16 value, uint8 str[]){
    Std_ReturnType errorState = E_OK;
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;
    if(NULL == str){
        errorState = E_NOT_OK;
    }
    else{    
        memset(str, ' ', 5);
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter]; 
            DataCounter++;
        }
    }
    return errorState;
}

Std_ReturnType convert_uint32_to_string(uint32 value, uint8 str[]){
    Std_ReturnType errorState = E_OK;
    if(NULL == str){
        errorState = E_NOT_OK;
    }
    else{    
        memset((char *)str, '\0', 11);
        sprintf(str, "%i", value);
    }
    return errorState;
}

static Std_ReturnType LCD_send_4bit(const St_chr_lcd_4bit_t* lcd, uint8 data){
    Std_ReturnType error_ret = E_OK;
    error_ret = MGPIO_write_pin(&(lcd->lcd_data[0]), (data>>0) & 0x01);
    error_ret = MGPIO_write_pin(&(lcd->lcd_data[1]), (data>>1) & 0x01);
    error_ret = MGPIO_write_pin(&(lcd->lcd_data[2]), (data>>2) & 0x01);
    error_ret = MGPIO_write_pin(&(lcd->lcd_data[3]), (data>>3) & 0x01);
    return error_ret;
}

static Std_ReturnType LCD_send_4bit_enable_signal(const St_chr_lcd_4bit_t* lcd){
    Std_ReturnType error_ret = E_OK;
    error_ret = MGPIO_write_pin(&(lcd->lcd_en), HIGH);
    __delay_us(5);
    error_ret = MGPIO_write_pin(&(lcd->lcd_en), LOW);
    return error_ret;
}

static Std_ReturnType LCD_send_8bit_enable_signal(const St_chr_lcd_8bit_t* lcd){
    Std_ReturnType error_ret = E_OK;
    error_ret = MGPIO_write_pin(&(lcd->lcd_en), HIGH);
    __delay_us(5);
    error_ret = MGPIO_write_pin(&(lcd->lcd_en), LOW);
    return error_ret;
}

static Std_ReturnType LCD_8bit_set_cursor(const St_chr_lcd_8bit_t* lcd, uint8 row, uint8 column){
    Std_ReturnType error_ret = E_OK;
    column--;
    switch(row){
    case ROW1:
        error_ret = HLcd_8bit_send_command(lcd, (0x80 + column));
        break; 
    case ROW2:
        error_ret = HLcd_8bit_send_command(lcd, (0xc0 + column));
        break;
    case ROW3:
        error_ret = HLcd_8bit_send_command(lcd, (0x94 + column));
        break;
    case ROW4:
        error_ret = HLcd_8bit_send_command(lcd, (0xD4 + column));
        break;
    default:
        break;
    }
    return error_ret;
}

static Std_ReturnType LCD_4bit_set_cursor(const St_chr_lcd_4bit_t* lcd, uint8 row, uint8 column){
    Std_ReturnType error_ret = E_OK;
    column--;
    switch(row){
    case ROW1:
        error_ret = HLcd_4bit_send_command(lcd, (0x80 + column));
        break; 
    case ROW2:
        error_ret = HLcd_4bit_send_command(lcd, (0xc0 + column));
        break;
    case ROW3:
        error_ret = HLcd_4bit_send_command(lcd, (0x94 + column));
        break;
    case ROW4:
        error_ret = HLcd_4bit_send_command(lcd, (0xD4 + column));
        break;
    default:
        break;
    }
    return error_ret;
}

