////////////////////////////////////////////////////////////////////////////////
/// @file     ETH.C
/// @author   LiuYQ
/// @version  v1.0.0
/// @date     2021-06-10
/// @brief    THIS FILE PROVIDES ALL THE ETH EXAMPLE.
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
/// <H2><CENTER>&COPY; COPYRIGHT 2018-2021 MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion  --------------------------------------
#define _ETH_C_

// Includes  -------------------------------------------------------------------
#include <string.h>

#include "lwip/arch.h"
#include "lwip/dhcp.h"
#include "lwip/opt.h"

#include "sys_arch.h"
#include "tcpip.h"

#include "ethernetif.h"

#include "hal_eth.h"

#include "eth.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Application_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Application_Ethernet
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Ethernet_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Ethernet receive callback function.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ETH_RxCpltCallback(void)
{
    portBASE_TYPE taskWoken = pdFALSE;
    xSemaphoreGiveFromISR(s_xEthernetInputSemaphore, &taskWoken);
    portEND_SWITCHING_ISR(taskWoken);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Ethernet interrupt request handler function.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ETH_IRQHandler(void)
{
    if (ETH_GetDMAITStatus(ETH_DMA_IT_R)) {
        ETH_RxCpltCallback();
        ETH_DMAClearITPendingBit(ETH_DMA_IT_R);
    } else if (ETH_GetDMAITStatus(ETH_DMA_IT_T)) {
        ETH_DMAClearITPendingBit(ETH_DMA_IT_T);
    } else if (ETH_GetDMAITStatus(ETH_DMA_IT_TBU)) {
        ETH_DMAClearITPendingBit(ETH_DMA_IT_TBU);
    }

    ETH_DMAClearITPendingBit(ETH_DMA_IT_NIS);

    if (ETH_GetDMAITStatus(ETH_DMA_FLAG_AIS)) {
        ETH_DMAClearITPendingBit(ETH_DMA_FLAG_AIS);
    }
}

void ethernet_init(void)
{
    ip4_addr_t ipaddr;
    ip4_addr_t netmask;
    ip4_addr_t gw;

    tcpip_init(NULL, NULL);

    // IP addresses initialization
#if LWIP_DHCP
    ip_addr_set_zero_ip4(&ipaddr);
    ip_addr_set_zero_ip4(&netmask);
    ip_addr_set_zero_ip4(&gw);
#else
    IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
    IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
    IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
#endif  // USE_DHCP

    // Initilialize the LwIP stack without RTOS
    // add the network interface (IPv4/IPv6) without RTOS
    netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init,
              &tcpip_input);

    netif_set_default(&gnetif);  // Registers the default network interface

    if (netif_is_link_up(&gnetif)) {
        netif_set_up(&gnetif);  // When the netif is fully configured this
                                // function must be called
    } else {
        netif_set_down(&gnetif);  // When the netif link is down this function
                                  // must be called
    }

#if LWIP_DHCP
    int err;
#    if defined(USER_DEBUG)
    printf("This example will use DHCP to dynamically assign IP addresses, if "
           "not needed, define LWIP_DHCP as 0 in lwipopts.h \n\n");
#    endif
    err = dhcp_start(&gnetif);
#    if defined(USER_DEBUG)
    if (err == ERR_OK)
        printf("lwip dhcp init success...\n\n");
    else
        printf("lwip dhcp init fail...\n\n");
#    endif

    while (ip_addr_cmp(&(gnetif.ip_addr), &ipaddr)) {
        vTaskDelay(1);
    }
#endif

#if defined(USER_DEBUG)
    printf("The local IP address is:%d.%d.%d.%d\n\n",
           (gnetif.ip_addr.addr & 0x000000ff),
           ((gnetif.ip_addr.addr & 0x0000ff00) >> 8),
           ((gnetif.ip_addr.addr & 0x00ff0000) >> 16),
           ((gnetif.ip_addr.addr) & 0xff000000) >> 24);
#endif
}

uint32_t getIpAddress(void)
{
    return gnetif.ip_addr.addr;
}

void getMacAddress(uint8_t * mac)
{
    memcpy(mac, gnetif.hwaddr, sizeof(uint8_t) * 6);
}



/// @}

/// @}

/// @}
