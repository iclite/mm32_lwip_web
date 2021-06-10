////////////////////////////////////////////////////////////////////////////////
/// @file     MAIN.C
/// @author   LiuYQ
/// @version  v1.0.0
/// @date     2021-05-25
/// @brief    THIS FILE PROVIDES ALL THE MAIN EXAMPLE.
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
#define _MAIN_C_

// Includes  -------------------------------------------------------------------
#include <string.h>

#include "mm32_system.h"

#include "console.h"

#include "lwip/err.h"

#include "sys_arch.h"

#include "eth.h"
#include "ethernetif.h"

#include "http_server.h"

#include "led.h"
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Application_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Application_Main
/// @{

extern void xPortSysTickHandler(void);

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Main_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  This function handles App SysTick Handler.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void AppTick_Handler(void)
{
#if (INCLUDE_xTaskGetSchedulerState == 1)
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
#endif
        xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1)
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Ethernet task for FreeRTOS.
/// @param  pvParameters: Task parameters.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void vEthernetTask(void * pvParameters)
{
    ethernet_init();

    http_server_init();

    vTaskDelete(NULL);

    while (1) {}
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  FreeRTOS application stack overflow hook funtion.
/// @param  xTask: Stack overflow task handle.
/// @param  pcTaskName: Stack overflow task name string.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void vApplicationStackOverflowHook(TaskHandle_t xTask, char * pcTaskName)
{
    while (1) {
        printf("task %s is stack overflow. \r\n", pcTaskName);
        vTaskDelay(500);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  main function.
/// @param  None.
/// @retval int: useless.
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    BaseType_t xReturn[] = {pdFAIL, pdFAIL};
    MCUID = SystemInit(SYSCLK_HSE_15x, emSYSTICK_On, AppTick_Handler);

    // Printf redirection to UART1.
    InitConsole(115200);

    xReturn[0] = xTaskCreate(vLedTask, "LED_INIT_TASK", 128, NULL, 1, NULL);
    xReturn[1] = xTaskCreate(vEthernetTask, "ETH_INIT_TASK", 512, NULL, 1, NULL);

    printf("Uart to Ethernet is running...\r\n");

    if (xReturn[0] == pdPASS && xReturn[1] == pdPASS) {
        vTaskStartScheduler();
    } else {
        return -1;
    }

    while (1) {}
}

/// @}

/// @}

/// @}
