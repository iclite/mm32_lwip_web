////////////////////////////////////////////////////////////////////////////////
/// @file     BSP_LAN8720.C
/// @author   LiuYQ
/// @version  v1.0.0
/// @date     2021-06-10
/// @brief    THIS FILE PROVIDES ALL THE LAN8720 BSP LAYER FUNCTIONS.
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
#define _BSP_LAN8720_C_

// Files includes  -------------------------------------------------------------
#include "hal_gpio.h"
#include "hal_rcc.h"
#include "hal_eth.h"
#include "hal_nvic.h"

#include "bsp_eth.h"
#include "bsp_lan8720.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Board_Support_Package
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup LAN8720_BSP
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup LAN8720_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
void CloseLAN8720(uint16_t phyAddr)
{
    ETH_WritePHYRegister(phyAddr, PHY_BCR, PHY_Powerdown);
}

////////////////////////////////////////////////////////////////////////////////
void CloseAutoMDIX(uint16_t phyAddress, bool exchange)
{
    u16 regValue = ETH_ReadPHYRegister(phyAddress, PHY_CSIR);

    if (exchange == true) {
        regValue |= PHY_MDIX_ChannelSelect;
    } else {
        regValue &= ~PHY_MDIX_ChannelSelect;
    }

    regValue |= PHY_AutoMDIX_Control;                                           // Disable AutoMDIX

    ETH_WritePHYRegister(phyAddress, PHY_CSIR, regValue);
}

////////////////////////////////////////////////////////////////////////////////
void InitLAN8720(uint16_t phyAddress)
{
    uint32_t status = 0;

    ETH_WritePHYRegister(phyAddress, PHY_BCR, PHY_Reset);

    if (ETH_InitStructure.ETH_AutoNegotiation != ETH_AutoNegotiation_Disable) {
        while (!(ETH_ReadPHYRegister(phyAddress, PHY_BSR) & PHY_Linked_Status));

        if (!(ETH_ReadPHYRegister(phyAddress, PHY_BSR) & PHY_AutoNego_Complete)) {
            ETH_WritePHYRegister(phyAddress, PHY_BCR, PHY_AutoNegotiation);
        }

        status = ETH_ReadPHYRegister(phyAddress, PHY_SCSR);

        if (status & PHY_DUPLEX_STATUS) {
            ETH_InitStructure.ETH_Mode = ETH_Mode_FullDuplex;
        } else {
            ETH_InitStructure.ETH_Mode = ETH_Mode_HalfDuplex;
        }

        if (status & PHY_SPEED_STATUS) {
            ETH_InitStructure.ETH_Speed = ETH_Speed_10M;
        } else {
            ETH_InitStructure.ETH_Speed = ETH_Speed_100M;
        }
    } else {
        uint16_t value = (uint16_t)((ETH_InitStructure.ETH_Mode >> 3) +
            (ETH_InitStructure.ETH_Speed >> 1));
        ETH_WritePHYRegister(phyAddress, PHY_BCR, value);
    }

    if (ETH_InitStructure.ETH_Speed == ETH_Speed_10M) {
        SYSCFG->CFGR2 &= ~SYSCFG_CFGR2_RMIISPD;
    } else {
        SYSCFG->CFGR2 |= SYSCFG_CFGR2_RMIISPD;
    }

    while (!(ETH_ReadPHYRegister(phyAddress, PHY_BSR) & PHY_Linked_Status));

    EthStatus |= ETH_LINK_FLAG;
}

////////////////////////////////////////////////////////////////////////////////
void ChangePHY(uint8_t mode)
{
    switch(mode){
    case 0:
        InitLAN8720(PHY_ADDRESS_LAN8720_A);
        CloseLAN8720(PHY_ADDRESS_LAN8720_B);
        break;
    case 1:
        InitLAN8720(PHY_ADDRESS_LAN8720_B);
        CloseLAN8720(PHY_ADDRESS_LAN8720_A);
        break;
    default:
        CloseLAN8720(PHY_ADDRESS_LAN8720_A);
        CloseLAN8720(PHY_ADDRESS_LAN8720_B);
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////
void BSP_PHY8720_Configure()
{
    InitLAN8720(PHY_ADDRESS_LAN8720_A);
}


/// @}

/// @}

/// @}

