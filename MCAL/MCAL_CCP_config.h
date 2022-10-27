/* 
 * File:   MCAL_CCP_config.h
 * Author: ADEL
 *
 * Created on June 21, 2022, 11:20 PM
 */

#ifndef MCAL_CCP_CONFIG_H
#define	MCAL_CCP_CONFIG_H

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/


/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

#define CCP_CFG_COMPARE_MODE_SELECT  0
#define CCP_CFG_CAPTURE_MODE_SELECT  1
#define CCP_CFG_PWM_MODE_SELECT      2

#define CCP1_CFG_SELECTED_MODE      CCP_CFG_PWM_MODE_SELECT
#define CCP2_CFG_SELECTED_MODE      CCP_CFG_PWM_MODE_SELECT



/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/



/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef enum{
    CCP1_CCP2_TIMER1_SOURCE = 0,
    CCP1_TIMER1_CCP2_TIMER3_SOURCE,
    CCP1_CCP2_TIMER3_SOURCE
}En_CCP_Timer_source_select_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/


#endif	/* MCAL_CCP_CONFIG_H */

