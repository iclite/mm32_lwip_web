////////////////////////////////////////////////////////////////////////////////
/// @file     console.c
/// @author   Nanjing AE Team
/// @version  1.0.0
/// @date     2021-04-22
/// @brief    THIS FILE PROVIDES ALL THE SYSTEM FUNCTIONS.
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
/// <H2><CENTER>&COPY; COPYRIGHT 2021 MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion  --------------------------------------
#define _CONSOLE_C_

// Files includes  -------------------------------------------------------------
#include <stdio.h>

#include "mm32.h"

#include "hal_gpio.h"
#include "hal_uart.h"

#include "console.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Application_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Application_Console
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Console_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  printf redirection function.
/// @param  ch: One character.
/// @param  f: File pointer.
/// @retval int32_t: One character.
////////////////////////////////////////////////////////////////////////////////
#ifdef __GNUC__
#    define PUTCHAR_PROTOTYPE int32_t __io_putchar(int32_t ch)
#else
#    define PUTCHAR_PROTOTYPE int32_t fputc(int32_t ch, FILE * f)
#endif
PUTCHAR_PROTOTYPE
{
    while ((CONSOLE_UART->CSR & UART_CSR_TXC) == 0);
    CONSOLE_UART->TDR = ch & 0x00FF;
    return ch;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Console Initialization.
/// @param  baudrate: Uart baudrate.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void InitConsole(uint32_t baudrate)
{
    UART_InitTypeDef UART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    CONSOLE_UART_CLK();
    CONSOLE_GPIO_CLK();

    UART_InitStructure.BaudRate      = baudrate;
    UART_InitStructure.WordLength    = UART_WordLength_8b;
    UART_InitStructure.StopBits      = UART_StopBits_1;
    UART_InitStructure.Parity        = UART_Parity_No;
    UART_InitStructure.Mode          = UART_GCR_RX | UART_GCR_TX;
    UART_InitStructure.HWFlowControl = UART_HWFlowControl_None;
    UART_Init(CONSOLE_UART, &UART_InitStructure);
    UART_Cmd(CONSOLE_UART, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = CONSOLE_TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(CONSOLE_TX_GPIO, &GPIO_InitStructure);
    GPIO_PinAFConfig(CONSOLE_TX_GPIO, CONSOLE_TX_SRC, CONSOLE_TX_AF);

    GPIO_InitStructure.GPIO_Pin   = CONSOLE_RX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_Init(CONSOLE_RX_GPIO, &GPIO_InitStructure);
    GPIO_PinAFConfig(CONSOLE_RX_GPIO, CONSOLE_RX_SRC, CONSOLE_RX_AF);
}

/// @}

/// @}

/// @}
