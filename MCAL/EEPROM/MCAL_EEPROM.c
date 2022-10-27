/* 
 * File:   MCAL_EEPROM.c
 * Author: ADEL
 *
 * Created on June 13, 2022, 3:07 PM
 */

#include "MCAL_EEPROM.h"



Std_ReturnType MEEPROM_WriteByte(uint16 bAdd, uint8 bData){
    Std_ReturnType errorState = E_NOT_OK;
    
    /* Read Global Interrupt bit status(Enabled or Diabled) */
    uint8 interrupt_enable_status = INTCONbits.GIE;
    /* Disable all Interrupt (General Interrupt) */
    INTCONbits.GIE = 0;
    /* Update the Address registers */
    EEADR  = (uint8)(bAdd & 0xFF); 
    EEADRH = (uint8)((bAdd >> 8) & (0x03));
    /* Update the data register */
    EEDATA = bData;
    /* Select access data to EEPROM memory */
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    /* Write initiate sequence to EECON2 */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Allow write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = 1;
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = 1;
    /* Wait for write operation to complete */
    while(EECON1bits.WR);
    /* Inhibits write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = 0;
    /* Restore the initial state of the Global Interrupt bit */
    INTCONbits.GIE = interrupt_enable_status;
    
    return errorState;
}

Std_ReturnType MEEPROM_ReadByte(uint16 bAdd, uint8* bData){
    Std_ReturnType errorState = E_NOT_OK;
    
    /* Read Global Interrupt bit status(Enabled or Diabled) */
    uint8 interrupt_enable_status = INTCONbits.GIE;
    /* Disable all Interrupt (General Interrupt) */
    INTCONbits.GIE = 0;
    
    /* Update the Address registers */
    EEADR  = (uint8)(bAdd & 0xFF); 
    EEADRH = (uint8)((bAdd >> 8) & (0x03));
    /* Select access data to EEPROM memory */
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.RD = 1;
    NOP();
    NOP();
    /* Update the data register */
    *bData = EEDATA;
    
    /* Restore the initial state of the Global Interrupt bit */
    INTCONbits.GIE = interrupt_enable_status;
    
    return errorState;
}