/*******************************************************************************
* File Name: DEBUG_VID_COMPARED_5.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DEBUG_VID_COMPARED_5_H) /* Pins DEBUG_VID_COMPARED_5_H */
#define CY_PINS_DEBUG_VID_COMPARED_5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DEBUG_VID_COMPARED_5_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DEBUG_VID_COMPARED_5__PORT == 15 && ((DEBUG_VID_COMPARED_5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DEBUG_VID_COMPARED_5_Write(uint8 value);
void    DEBUG_VID_COMPARED_5_SetDriveMode(uint8 mode);
uint8   DEBUG_VID_COMPARED_5_ReadDataReg(void);
uint8   DEBUG_VID_COMPARED_5_Read(void);
void    DEBUG_VID_COMPARED_5_SetInterruptMode(uint16 position, uint16 mode);
uint8   DEBUG_VID_COMPARED_5_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DEBUG_VID_COMPARED_5_SetDriveMode() function.
     *  @{
     */
        #define DEBUG_VID_COMPARED_5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DEBUG_VID_COMPARED_5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DEBUG_VID_COMPARED_5_DM_RES_UP          PIN_DM_RES_UP
        #define DEBUG_VID_COMPARED_5_DM_RES_DWN         PIN_DM_RES_DWN
        #define DEBUG_VID_COMPARED_5_DM_OD_LO           PIN_DM_OD_LO
        #define DEBUG_VID_COMPARED_5_DM_OD_HI           PIN_DM_OD_HI
        #define DEBUG_VID_COMPARED_5_DM_STRONG          PIN_DM_STRONG
        #define DEBUG_VID_COMPARED_5_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DEBUG_VID_COMPARED_5_MASK               DEBUG_VID_COMPARED_5__MASK
#define DEBUG_VID_COMPARED_5_SHIFT              DEBUG_VID_COMPARED_5__SHIFT
#define DEBUG_VID_COMPARED_5_WIDTH              1u

/* Interrupt constants */
#if defined(DEBUG_VID_COMPARED_5__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DEBUG_VID_COMPARED_5_SetInterruptMode() function.
     *  @{
     */
        #define DEBUG_VID_COMPARED_5_INTR_NONE      (uint16)(0x0000u)
        #define DEBUG_VID_COMPARED_5_INTR_RISING    (uint16)(0x0001u)
        #define DEBUG_VID_COMPARED_5_INTR_FALLING   (uint16)(0x0002u)
        #define DEBUG_VID_COMPARED_5_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DEBUG_VID_COMPARED_5_INTR_MASK      (0x01u) 
#endif /* (DEBUG_VID_COMPARED_5__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DEBUG_VID_COMPARED_5_PS                     (* (reg8 *) DEBUG_VID_COMPARED_5__PS)
/* Data Register */
#define DEBUG_VID_COMPARED_5_DR                     (* (reg8 *) DEBUG_VID_COMPARED_5__DR)
/* Port Number */
#define DEBUG_VID_COMPARED_5_PRT_NUM                (* (reg8 *) DEBUG_VID_COMPARED_5__PRT) 
/* Connect to Analog Globals */                                                  
#define DEBUG_VID_COMPARED_5_AG                     (* (reg8 *) DEBUG_VID_COMPARED_5__AG)                       
/* Analog MUX bux enable */
#define DEBUG_VID_COMPARED_5_AMUX                   (* (reg8 *) DEBUG_VID_COMPARED_5__AMUX) 
/* Bidirectional Enable */                                                        
#define DEBUG_VID_COMPARED_5_BIE                    (* (reg8 *) DEBUG_VID_COMPARED_5__BIE)
/* Bit-mask for Aliased Register Access */
#define DEBUG_VID_COMPARED_5_BIT_MASK               (* (reg8 *) DEBUG_VID_COMPARED_5__BIT_MASK)
/* Bypass Enable */
#define DEBUG_VID_COMPARED_5_BYP                    (* (reg8 *) DEBUG_VID_COMPARED_5__BYP)
/* Port wide control signals */                                                   
#define DEBUG_VID_COMPARED_5_CTL                    (* (reg8 *) DEBUG_VID_COMPARED_5__CTL)
/* Drive Modes */
#define DEBUG_VID_COMPARED_5_DM0                    (* (reg8 *) DEBUG_VID_COMPARED_5__DM0) 
#define DEBUG_VID_COMPARED_5_DM1                    (* (reg8 *) DEBUG_VID_COMPARED_5__DM1)
#define DEBUG_VID_COMPARED_5_DM2                    (* (reg8 *) DEBUG_VID_COMPARED_5__DM2) 
/* Input Buffer Disable Override */
#define DEBUG_VID_COMPARED_5_INP_DIS                (* (reg8 *) DEBUG_VID_COMPARED_5__INP_DIS)
/* LCD Common or Segment Drive */
#define DEBUG_VID_COMPARED_5_LCD_COM_SEG            (* (reg8 *) DEBUG_VID_COMPARED_5__LCD_COM_SEG)
/* Enable Segment LCD */
#define DEBUG_VID_COMPARED_5_LCD_EN                 (* (reg8 *) DEBUG_VID_COMPARED_5__LCD_EN)
/* Slew Rate Control */
#define DEBUG_VID_COMPARED_5_SLW                    (* (reg8 *) DEBUG_VID_COMPARED_5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DEBUG_VID_COMPARED_5_PRTDSI__CAPS_SEL       (* (reg8 *) DEBUG_VID_COMPARED_5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DEBUG_VID_COMPARED_5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DEBUG_VID_COMPARED_5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DEBUG_VID_COMPARED_5_PRTDSI__OE_SEL0        (* (reg8 *) DEBUG_VID_COMPARED_5__PRTDSI__OE_SEL0) 
#define DEBUG_VID_COMPARED_5_PRTDSI__OE_SEL1        (* (reg8 *) DEBUG_VID_COMPARED_5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DEBUG_VID_COMPARED_5_PRTDSI__OUT_SEL0       (* (reg8 *) DEBUG_VID_COMPARED_5__PRTDSI__OUT_SEL0) 
#define DEBUG_VID_COMPARED_5_PRTDSI__OUT_SEL1       (* (reg8 *) DEBUG_VID_COMPARED_5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DEBUG_VID_COMPARED_5_PRTDSI__SYNC_OUT       (* (reg8 *) DEBUG_VID_COMPARED_5__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DEBUG_VID_COMPARED_5__SIO_CFG)
    #define DEBUG_VID_COMPARED_5_SIO_HYST_EN        (* (reg8 *) DEBUG_VID_COMPARED_5__SIO_HYST_EN)
    #define DEBUG_VID_COMPARED_5_SIO_REG_HIFREQ     (* (reg8 *) DEBUG_VID_COMPARED_5__SIO_REG_HIFREQ)
    #define DEBUG_VID_COMPARED_5_SIO_CFG            (* (reg8 *) DEBUG_VID_COMPARED_5__SIO_CFG)
    #define DEBUG_VID_COMPARED_5_SIO_DIFF           (* (reg8 *) DEBUG_VID_COMPARED_5__SIO_DIFF)
#endif /* (DEBUG_VID_COMPARED_5__SIO_CFG) */

/* Interrupt Registers */
#if defined(DEBUG_VID_COMPARED_5__INTSTAT)
    #define DEBUG_VID_COMPARED_5_INTSTAT            (* (reg8 *) DEBUG_VID_COMPARED_5__INTSTAT)
    #define DEBUG_VID_COMPARED_5_SNAP               (* (reg8 *) DEBUG_VID_COMPARED_5__SNAP)
    
	#define DEBUG_VID_COMPARED_5_0_INTTYPE_REG 		(* (reg8 *) DEBUG_VID_COMPARED_5__0__INTTYPE)
#endif /* (DEBUG_VID_COMPARED_5__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DEBUG_VID_COMPARED_5_H */


/* [] END OF FILE */