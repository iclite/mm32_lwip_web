////////////////////////////////////////////////////////////////////////////////
/// @file   ethernetif.h
/// @author AE TEAM
/// @brief  THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE
///         ethernetif.h EXAMPLES.
/// ////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT 2018-2021 MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

#ifndef __ETHERNETIF_H
#define __ETHERNETIF_H

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Application_Layer
/// @brief MM32 Application Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Application_Ethernet_Interface
/// @brief Application Ethernet Interface Module
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Ethernet_Interface_Exported_Constants
/// @{

///  Network Interface MTU
#define NETIF_MTU                       1500

/// Static IP ADDRESS
#define IP_ADDR0                        192
#define IP_ADDR1                        168
#define IP_ADDR2                        0
#define IP_ADDR3                        32

/// NETMASK
#define NETMASK_ADDR0                   255
#define NETMASK_ADDR1                   255
#define NETMASK_ADDR2                   255
#define NETMASK_ADDR3                   0

/// Gateway Address
#define GW_ADDR0                        192
#define GW_ADDR1                        168
#define GW_ADDR2                        0
#define GW_ADDR3                        1

/// MAC Address
#define MAC_ADDR0                       2
#define MAC_ADDR1                       0
#define MAC_ADDR2                       0
#define MAC_ADDR3                       0
#define MAC_ADDR4                       0
#define MAC_ADDR5                       2

/// Network Interface Name
#define IFNAME0                         'm'
#define IFNAME1                         'm'

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Ethernet_Interface_Exported_Enumeration
/// @{

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Ethernet_Interface_Exported_Variables
/// @{

#ifdef _ETHERNETIF_C_
#define GLOBAL

GLOBAL sys_sem_t s_xEthernetInputSemaphore = NULL;

#else
#define GLOBAL extern

GLOBAL sys_sem_t s_xEthernetInputSemaphore;

#endif

#undef GLOBAL

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Ethernet_Interface_Exported_Functions
/// @{

err_t ethernetif_init(struct netif* netif);

void ethernetif_input(void* pParams);
void ethernetif_output( void* argument );
void ethernetif_update_config(struct netif* netif);
void ethernetif_notify_conn_changed(struct netif* netif);

int String2HexInt(char *stringValue);
char *cutWords(char *str,int start,int end);

/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
