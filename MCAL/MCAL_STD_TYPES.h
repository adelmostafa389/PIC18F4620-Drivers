/* 
 * File:   MCAL_STD_TYPES_H.h
 * Author: ADEL
 *
 * Created on May 27, 2022, 3:23 PM
 */

#ifndef MCAL_STD_TYPES_H_H
#define	MCAL_STD_TYPES_H_H



/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "std_libraries.h"
#include "compiler.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/
#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_0N          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define ZERO_INIT       0x00

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;

typedef void(*PtrTo_func_t)(void);

typedef uint8 Std_ReturnType;

typedef union{
    struct{
        uint8 LSbits8;
        uint8 MSbits8;
    };
    struct{
        uint16 REG16;
    };
}Un_16bits_register_t;

#define E_OK          (Std_ReturnType)0x01
#define E_NOT_OK      (Std_ReturnType)0x00

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

#endif	/* MCAL_STD_TYPES_H_H */

