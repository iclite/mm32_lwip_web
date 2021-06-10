////////////////////////////////////////////////////////////////////////////////
/// @file    uart.h
/// @author  AE TEAM
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FIRMWARE FUNCTIONS.
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
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion ---------------------------------------
#ifndef __CONSOLE_H
#define __CONSOLE_H

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Application_Layer
/// @brief MM32 Application Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Application_Console
/// @brief Application console modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Console_Exported_Constants
/// @{

#define CONSOLE_TARGET                  1

#if !defined(CONSOLE_TARGET) || (defined(CONSOLE_TARGET) && (CONSOLE_TARGET == 1))
    #define CONSOLE_UART                UART1
    #define CONSOLE_UART_CLK()          RCC->APB2ENR |= RCC_APB2ENR_UART1;
    #define CONSOLE_GPIO_CLK()          RCC->AHB1ENR |= RCC_AHB1ENR_GPIOA;

    #define CONSOLE_TX_GPIO             GPIOA
    #define CONSOLE_TX_PIN              GPIO_Pin_9
    #define CONSOLE_TX_SRC              GPIO_PinSource9
    #define CONSOLE_TX_AF               GPIO_AF_7

    #define CONSOLE_RX_GPIO             GPIOA
    #define CONSOLE_RX_PIN              GPIO_Pin_10
    #define CONSOLE_RX_SRC              GPIO_PinSource10
    #define CONSOLE_RX_AF               GPIO_AF_7

#elif defined(CONSOLE_TARGET) && (CONSOLE_TARGET == 2)
    #define CONSOLE_UART                UART2
    #define CONSOLE_UART_CLK()          RCC->APB1ENR |= RCC_APB1ENR_UART2;
    #define CONSOLE_GPIO_CLK()          RCC->AHB1ENR |= RCC_AHB1ENR_GPIOA;

    #define CONSOLE_TX_GPIO             GPIOA
    #define CONSOLE_TX_PIN              GPIO_Pin_2
    #define CONSOLE_TX_SRC              GPIO_PinSource2
    #define CONSOLE_TX_AF               GPIO_AF_7

    #define CONSOLE_RX_GPIO             GPIOA
    #define CONSOLE_RX_PIN              GPIO_Pin_3
    #define CONSOLE_RX_SRC              GPIO_PinSource3
    #define CONSOLE_RX_AF               GPIO_AF_7

#elif defined(CONSOLE_TARGET) && (CONSOLE_TARGET == 3)
    #define CONSOLE_UART                UART3
    #define CONSOLE_UART_CLK()          RCC->APB1ENR |= RCC_APB1ENR_UART3;
    #define CONSOLE_GPIO_CLK()          RCC->AHB1ENR |= RCC_AHB1ENR_GPIOB;

    #define CONSOLE_TX_GPIO             GPIOB
    #define CONSOLE_TX_PIN              GPIO_Pin_10
    #define CONSOLE_TX_SRC              GPIO_PinSource10
    #define CONSOLE_TX_AF               GPIO_AF_7

    #define CONSOLE_RX_GPIO             GPIOB
    #define CONSOLE_RX_PIN              GPIO_Pin_11
    #define CONSOLE_RX_SRC              GPIO_PinSource11
    #define CONSOLE_RX_AF               GPIO_AF_7

#elif defined(CONSOLE_TARGET) && (CONSOLE_TARGET == 4)
    #define CONSOLE_UART                UART4
    #define CONSOLE_UART_CLK()          RCC->APB1ENR |= RCC_APB1ENR_UART4;
    #define CONSOLE_GPIO_CLK()          RCC->AHB1ENR |= RCC_AHB1ENR_GPIOC;

    #define CONSOLE_TX_GPIO             GPIOC
    #define CONSOLE_TX_PIN              GPIO_Pin_10
    #define CONSOLE_TX_SRC              GPIO_PinSource10
    #define CONSOLE_TX_AF               GPIO_AF_8

    #define CONSOLE_RX_GPIO             GPIOC
    #define CONSOLE_RX_PIN              GPIO_Pin_11
    #define CONSOLE_RX_SRC              GPIO_PinSource11
    #define CONSOLE_RX_AF               GPIO_AF_8

#elif defined(CONSOLE_TARGET) && (CONSOLE_TARGET == 5)
    #define CONSOLE_UART                UART5
    #define CONSOLE_UART_CLK()          RCC->APB1ENR |= RCC_APB1ENR_UART5;
    #define CONSOLE_GPIO_CLK()          RCC->AHB1ENR |= RCC_AHB1ENR_GPIOC | RCC_AHB1ENR_GPIOD;

    #define CONSOLE_TX_GPIO             GPIOC
    #define CONSOLE_TX_PIN              GPIO_Pin_12
    #define CONSOLE_TX_SRC              GPIO_PinSource12
    #define CONSOLE_TX_AF               GPIO_AF_8

    #define CONSOLE_RX_GPIO             GPIOD
    #define CONSOLE_RX_PIN              GPIO_Pin_2
    #define CONSOLE_RX_SRC              GPIO_PinSource2
    #define CONSOLE_RX_AF               GPIO_AF_8

#elif defined(CONSOLE_TARGET) && (CONSOLE_TARGET == 6)
    #define CONSOLE_UART                UART6
    #define CONSOLE_UART_CLK()          RCC->APB2ENR |= RCC_APB2ENR_UART6;
    #define CONSOLE_GPIO_CLK()          RCC->AHB1ENR |= RCC_AHB1ENR_GPIOC;

    #define CONSOLE_TX_GPIO             GPIOC
    #define CONSOLE_TX_PIN              GPIO_Pin_6
    #define CONSOLE_TX_SRC              GPIO_PinSource6
    #define CONSOLE_TX_AF               GPIO_AF_8

    #define CONSOLE_RX_GPIO             GPIOC
    #define CONSOLE_RX_PIN              GPIO_Pin_7
    #define CONSOLE_RX_SRC              GPIO_PinSource7
    #define CONSOLE_RX_AF               GPIO_AF_8

#elif defined(CONSOLE_TARGET) && (CONSOLE_TARGET == 7)
    #define CONSOLE_UART                UART7
    #define CONSOLE_UART_CLK()          RCC->APB1ENR |= RCC_APB1ENR_UART7;
    #define CONSOLE_GPIO_CLK()          RCC->AHB1ENR |= RCC_AHB1ENR_GPIOB;

    #define CONSOLE_TX_GPIO             GPIOB
    #define CONSOLE_TX_PIN              GPIO_Pin_6
    #define CONSOLE_TX_SRC              GPIO_PinSource1
    #define CONSOLE_TX_AF               GPIO_AF_8

    #define CONSOLE_RX_GPIO             GPIOB
    #define CONSOLE_RX_PIN              GPIO_Pin_7
    #define CONSOLE_RX_SRC              GPIO_PinSource7
    #define CONSOLE_RX_AF               GPIO_AF_8

#elif defined(CONSOLE_TARGET) && (CONSOLE_TARGET == 8)
    #define CONSOLE_UART                UART8
    #define CONSOLE_UART_CLK()          RCC->APB1ENR |= RCC_APB1ENR_UART8;
    #define CONSOLE_GPIO_CLK()          RCC->AHB1ENR |= RCC_AHB1ENR_GPIOE;

    #define CONSOLE_TX_GPIO             GPIOE
    #define CONSOLE_TX_PIN              GPIO_Pin_1
    #define CONSOLE_TX_SRC              GPIO_PinSource1
    #define CONSOLE_TX_AF               GPIO_AF_8

    #define CONSOLE_RX_GPIO             GPIOE
    #define CONSOLE_RX_PIN              GPIO_Pin_0
    #define CONSOLE_RX_SRC              GPIO_PinSource0
    #define CONSOLE_RX_AF               GPIO_AF_8

#endif

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Console_Exported_Variables
/// @{



#ifdef _CONSOLE_C_
#define GLOBAL


#else
#define GLOBAL extern
#endif


#undef GLOBAL



/// @}


////////////////////////////////////////////////////////////////////////////////
/// @defgroup Console_Exported_Functions
/// @{

void InitConsole(uint32_t baudrate);


/// @}


/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////


