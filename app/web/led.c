////////////////////////////////////////////////////////////////////////////////
/// @file     LED.C
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
#define _LED_C_

// Includes  -------------------------------------------------------------------
#include <string.h>

#include "sys_arch.h"

#include "http_server.h"

#include "bsp.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Application_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Application_Main
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Main_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Led task for FreeRTOS.
/// @param  pvParameters: Task parameters.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void vLedTask(void * pvParameters)
{
    const TickType_t xDelay = pdMS_TO_TICKS(50);

    BSP_LED_Configure();

    s_xBtnSemaphore = xSemaphoreCreateBinary();

    while (1) {
        if (xSemaphoreTake(s_xBtnSemaphore, xDelay) == pdTRUE) {
            if (buttonClickedFlag) {
                GREEN_LED_ON();
            } else {
                GREEN_LED_OFF();
            }
        }
    }
}

/// @}

/// @}

/// @}
