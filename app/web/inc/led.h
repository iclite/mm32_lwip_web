////////////////////////////////////////////////////////////////////////////////
/// @file     LED.H
/// @author   LiuYQ
/// @version  v1.0.0
/// @date     2021-05-25
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE LED
///           EXAMPLES.
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
#ifndef __LED_H
#define __LED_H

// Files includes  -------------------------------------------------------------


////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Application_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Application_LED
/// @brief LED example modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup LED_Exported_Variables
/// @{

#ifdef _LED_C_

#define GLOBAL
#else
#define GLOBAL extern

#endif


#undef GLOBAL

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup LED_Exported_Functions
/// @{

void vLedTask(void * pvParameters);

/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif /* __LED_H */
////////////////////////////////////////////////////////////////////////////////
