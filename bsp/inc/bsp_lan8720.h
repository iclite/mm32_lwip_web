////////////////////////////////////////////////////////////////////////////////
/// @file     BSP_BEEP.H
/// @author   LiuYQ
/// @version  v1.0.0
/// @date     2021-06-10
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE LED
///           BSP LAYER.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT 2018-2019 MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion  --------------------------------------
#ifndef __BSP_PHY8720_H
#define __BSP_PHY8720_H

#include "hal_eth.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Board_Support_Package
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup LED_BSP
/// @brief LED BSP modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup LED_Exported_Types
/// @{

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup LED_Exported_Constants
/// @{

#define PHY_ADDRESS_LAN8720_A           ((uint16_t)0x0000)
#define PHY_ADDRESS_LAN8720_B           ((uint16_t)0x0001)


////////////////////////////////////////////////////////////////////////////////
#define PHY_READ_TIMEOUT                ((uint32_t)0x0004FFFF)
#define PHY_WRITE_TIMEOUT               ((uint32_t)0x0004FFFF)

#define PHY_BCR                         ((uint16_t)0)                           ///< Basic Control Register
#define PHY_BSR                         ((uint16_t)1)                           ///< Basic Status Register
#define PHY_ID1                         ((uint16_t)2)                           ///< PHY Identifier 1
#define PHY_ID2                         ((uint16_t)3)                           ///< PHY Identifier 2
#define PHY_ANAR                        ((uint16_t)4)                           ///< Auto-Negotiation Advertisement Register
#define PHY_ANLPAR                      ((uint16_t)5)                           ///< Auto-Negotiation Link Partner Ability Register
#define PHY_ANER                        ((uint16_t)6)                           ///< Auto-Negotiation Expansion Register
#define PHY_MCSR                        ((uint16_t)17)                          ///< Mode Control/Status Register
#define PHY_SM                          ((uint16_t)18)                          ///< Special Modes
#define PHY_SECR                        ((uint16_t)26)                          ///< Symbol Error Counter Register
#define PHY_CSIR                        ((uint16_t)27)                          ///< Control / Status Indication Register
#define PHY_ISR                         ((uint16_t)29)                          ///< Interrupt Source Register
#define PHY_IMR                         ((uint16_t)30)                          ///< Interrupt Mask Register
#define PHY_SCSR                        ((uint16_t)31)                          ///< PHY Special Control/Status Register

#define PHY_Reset                       ((uint16_t)0x8000)                      ///< PHY Reset
#define PHY_Loopback                    ((uint16_t)0x4000)                      ///< Select loop-back mode
#define PHY_FULLDUPLEX_100M             ((uint16_t)0x2100)                      ///< Set the full-duplex mode at 100 Mb/s
#define PHY_HALFDUPLEX_100M             ((uint16_t)0x2000)                      ///< Set the half-duplex mode at 100 Mb/s
#define PHY_FULLDUPLEX_10M              ((uint16_t)0x0100)                      ///< Set the full-duplex mode at 10 Mb/s
#define PHY_HALFDUPLEX_10M              ((uint16_t)0x0000)                      ///< Set the half-duplex mode at 10 Mb/s
#define PHY_AutoNegotiation             ((uint16_t)0x1000)                      ///< Enable auto-negotiation function
#define PHY_Restart_AutoNegotiation     ((uint16_t)0x0200)                      ///< Restart auto-negotiation function
#define PHY_Powerdown                   ((uint16_t)0x0800)                      ///< Select the power down mode
#define PHY_Isolate                     ((uint16_t)0x0400)                      ///< Isolate PHY from MII

#define PHY_AutoNego_Complete           ((uint16_t)0x0020)                      ///< Auto-Negotiation process completed
#define PHY_Linked_Status               ((uint16_t)0x0004)                      ///< Valid link established
#define PHY_Jabber_detection            ((uint16_t)0x0002)                      ///< Jabber condition detected

#define PHY_EnergyDetect_PowerDown      ((uint16_t)0x2000)                      ///< Energy Detect Power-Down mode

#define PHY_MDIX_ChannelSelect          ((uint16_t)0x2000)                      ///< Manual channel select
#define PHY_AutoMDIX_Control            ((uint16_t)0x8000)                      ///< HP Auto-MDIX control

#define PHY_SCSR_AutoDone               ((uint16_t)0x1 << 12)
#define PHY_SCSR_10xHalfDup             ((uint16_t)0x001 << 2)
#define PHY_SCSR_10xFullDup             ((uint16_t)0x101 << 2)
#define PHY_SCSR_100xHalfDup            ((uint16_t)0x010 << 2)
#define PHY_SCSR_100xFullDup            ((uint16_t)0x110 << 2)

#define PHY_DUPLEX_STATUS               ((uint16_t)0x1 << 4)
#define PHY_SPEED_STATUS                ((uint16_t)0x1 << 2)


/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup LED_Exported_Variables
/// @{
#ifdef _BSP_PHY8720_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif



#undef GLOBAL

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup LED_Exported_Functions
/// @{

void ChangePHY(uint8_t mode);
void ChangeAutoMDIX(uint16_t phyAddr, bool mode);

void BSP_PHY8720_Configure();


/// @}



/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif /*__BSP_BEEP_H */
////////////////////////////////////////////////////////////////////////////////
