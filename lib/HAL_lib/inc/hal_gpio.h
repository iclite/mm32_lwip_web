////////////////////////////////////////////////////////////////////////////////
/// @file     HAL_GPIO.H
/// @author   C Yuan
/// @version  v2.0.0
/// @date     2019-03-13
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE GPIO
///           FIRMWARE LIBRARY.
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
#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

// Files includes  -------------------------------------------------------------
#include "mm32_types.h"
#include "MM32.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup GPIO_HAL
/// @brief GPIO HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup GPIO_Exported_Types
/// @{


#define PA0                             (0x0000)
#define PA1                             (0x0001)
#define PA2                             (0x0002)
#define PA3                             (0x0003)
#define PA4                             (0x0004)
#define PA5                             (0x0005)
#define PA6                             (0x0006)
#define PA7                             (0x0007)
#define PA8                             (0x0008)
#define PA9                             (0x0009)
#define PA10                            (0x000A)
#define PA11                            (0x000B)
#define PA12                            (0x000C)
#define PA13                            (0x000D)
#define PA14                            (0x000E)
#define PA15                            (0x000F)

#define PB0                             (0x0100)
#define PB1                             (0x0101)
#define PB2                             (0x0102)
#define PB3                             (0x0103)
#define PB4                             (0x0104)
#define PB5                             (0x0105)
#define PB6                             (0x0106)
#define PB7                             (0x0107)
#define PB8                             (0x0108)
#define PB9                             (0x0109)
#define PB10                            (0x010A)
#define PB11                            (0x010B)
#define PB12                            (0x010C)
#define PB13                            (0x010D)
#define PB14                            (0x010E)
#define PB15                            (0x010F)

#define PC0                             (0x0200)
#define PC1                             (0x0201)
#define PC2                             (0x0202)
#define PC3                             (0x0203)
#define PC4                             (0x0204)
#define PC5                             (0x0205)
#define PC6                             (0x0206)
#define PC7                             (0x0207)
#define PC8                             (0x0208)
#define PC9                             (0x0209)
#define PC10                            (0x020A)
#define PC11                            (0x020B)
#define PC12                            (0x020C)
#define PC13                            (0x020D)
#define PC14                            (0x020E)
#define PC15                            (0x020F)

#define PD0                             (0x0300)
#define PD1                             (0x0301)
#define PD2                             (0x0302)
#define PD3                             (0x0303)
#define PD4                             (0x0304)
#define PD5                             (0x0305)
#define PD6                             (0x0306)
#define PD7                             (0x0307)
#define PD8                             (0x0308)
#define PD9                             (0x0309)
#define PD10                            (0x030A)
#define PD11                            (0x030B)
#define PD12                            (0x030C)
#define PD13                            (0x030D)
#define PD14                            (0x030E)
#define PD15                            (0x030F)

#define PE0                             (0x0400)
#define PE1                             (0x0401)
#define PE2                             (0x0402)
#define PE3                             (0x0403)
#define PE4                             (0x0404)
#define PE5                             (0x0405)
#define PE6                             (0x0406)
#define PE7                             (0x0407)
#define PE8                             (0x0408)
#define PE9                             (0x0409)
#define PE10                            (0x040A)
#define PE11                            (0x040B)
#define PE12                            (0x040C)
#define PE13                            (0x040D)
#define PE14                            (0x040E)
#define PE15                            (0x040F)

#define PF0                             (0x0500)
#define PF1                             (0x0501)
#define PF2                             (0x0502)
#define PF3                             (0x0503)
#define PF4                             (0x0504)
#define PF5                             (0x0505)
#define PF6                             (0x0506)
#define PF7                             (0x0507)
#define PF8                             (0x0508)
#define PF9                             (0x0509)
#define PF10                            (0x050A)
#define PF11                            (0x050B)
#define PF12                            (0x050C)
#define PF13                            (0x050D)
#define PF14                            (0x050E)
#define PF15                            (0x050F)

#define PG0                             (0x0600)
#define PG1                             (0x0601)
#define PG2                             (0x0602)
#define PG3                             (0x0603)
#define PG4                             (0x0604)
#define PG5                             (0x0605)
#define PG6                             (0x0606)
#define PG7                             (0x0607)
#define PG8                             (0x0608)
#define PG9                             (0x0609)
#define PG10                            (0x060A)
#define PG11                            (0x060B)
#define PG12                            (0x060C)
#define PG13                            (0x060D)
#define PG14                            (0x060E)
#define PG15                            (0x060F)

#define PH0                             (0x0700)
#define PH1                             (0x0701)
#define PH2                             (0x0702)
#define PH3                             (0x0703)
#define PH4                             (0x0704)
#define PH5                             (0x0705)
#define PH6                             (0x0706)
#define PH7                             (0x0707)
#define PH8                             (0x0708)
#define PH9                             (0x0709)
#define PH10                            (0x070A)
#define PH11                            (0x070B)
#define PH12                            (0x070C)
#define PH13                            (0x070D)
#define PH14                            (0x070E)
#define PH15                            (0x070F)

////////////////////////////////////////////////////////////////////////////////
/// @brief  Output Maximum frequency selection
////////////////////////////////////////////////////////////////////////////////
typedef enum {
#if defined(__MM3N1) || defined(__MM3O1) || defined(__MM0Q1)
    GPIO_Speed_10MHz = 1,  ///< Maximum speed is 10MHz
    GPIO_Speed_20MHz,      ///< Maximum speed is 20MHz
    GPIO_Speed_50MHz       ///< Maximum speed is 50MHz
#elif defined(__MM0N1) || defined(__MM0P1)
    GPIO_Speed_50MHz = 1,  ///< Maximum speed is 50MHz
    GPIO_Speed_20MHz,      ///< Maximum speed is 20MHz
    GPIO_Speed_10MHz       ///< Maximum speed is 10MHz
#else
    GPIO_Speed_50MHz = 1,  ///< Maximum speed is 50MHz
    GPIO_Speed_20MHz = 1,      ///< Maximum speed is 20MHz
    GPIO_Speed_10MHz = 1       ///< Maximum speed is 10MHz
#endif
} GPIOSpeed_TypeDef;


////////////////////////////////////////////////////////////////////////////////
/// @brief  Configuration Mode enumeration
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    GPIO_Mode_AIN       = 0x00,  ///< Analog input
    GPIO_Mode_FLOATING 	= 0x04,  ///< Floating input
    GPIO_Mode_IPD       = 0x28,  ///< Pull down input
    GPIO_Mode_IPU       = 0x48,  ///< Pull up input
    GPIO_Mode_Out_OD    = 0x14,  ///< Universal open drain output
    GPIO_Mode_Out_PP    = 0x10,  ///< Universal push-pull output
    GPIO_Mode_AF_OD     = 0x1C,  ///< Multiplex open drain output
    GPIO_Mode_AF_PP     = 0x18   ///< Multiplexed push-pull output
} GPIOMode_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  Bit_SET and Bit_RESET enumeration
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    Bit_RESET = 0,  ///< bit reset
    Bit_SET         ///< bit set
} BitAction;

////////////////////////////////////////////////////////////////////////////////
/// @brief  GPIO Init structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    u16               GPIO_Pin;    ///< GPIO_Pin
    GPIOSpeed_TypeDef GPIO_Speed;  ///< GPIO_Speed
    GPIOMode_TypeDef  GPIO_Mode;   ///< GPIO_Mode
} GPIO_InitTypeDef;

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup GPIO_Exported_Constants
/// @{

#define GPIO_Speed_2MHz GPIO_Speed_20MHz

#define GPIO_Pin_0 					(0x0001U)    								///< Pin 0 selected
#define GPIO_Pin_1 					(0x0002U)    								///< Pin 1 selected
#define GPIO_Pin_2 					(0x0004U)    								///< Pin 2 selected
#define GPIO_Pin_3 					(0x0008U)    								///< Pin 3 selected
#define GPIO_Pin_4 					(0x0010U)    								///< Pin 4 selected
#define GPIO_Pin_5 					(0x0020U)    								///< Pin 5 selected
#define GPIO_Pin_6 					(0x0040U)    								///< Pin 6 selected
#define GPIO_Pin_7 					(0x0080U)    								///< Pin 7 selected
#define GPIO_Pin_8 					(0x0100U)    								///< Pin 8 selected
#define GPIO_Pin_9 					(0x0200U)    								///< Pin 9 selected
#define GPIO_Pin_10 				(0x0400U)   								///< Pin 10 selected
#define GPIO_Pin_11 				(0x0800U)   								///< Pin 11 selected
#define GPIO_Pin_12 				(0x1000U)   								///< Pin 12 selected
#define GPIO_Pin_13 				(0x2000U)   								///< Pin 13 selected
#define GPIO_Pin_14 				(0x4000U)   								///< Pin 14 selected
#define GPIO_Pin_15 				(0x8000U)   								///< Pin 15 selected
#define GPIO_Pin_All 				(0xFFFFU)  									///< All pins selected


#define GPIO_AF_0 					(0x00U)  									///< Alternative function 0
#define GPIO_AF_1 					(0x01U)  									///< Alternative function 1
#define GPIO_AF_2 					(0x02U)  									///< Alternative function 2
#define GPIO_AF_3 					(0x03U)  									///< Alternative function 3
#define GPIO_AF_4 					(0x04U)  									///< Alternative function 4
#define GPIO_AF_5 					(0x05U)  									///< Alternative function 5
#define GPIO_AF_6 					(0x06U)  									///< Alternative function 6
#define GPIO_AF_7 					(0x07U)  									///< Alternative function 7

#define GPIO_AF_8                   (0x08U)                                     ///< Alternative function 8
#define GPIO_AF_9                   (0x09U)                                     ///< Alternative function 9
#define GPIO_AF_10                  (0x0AU)                                     ///< Alternative function 10
#define GPIO_AF_11                  (0x0BU)                                     ///< Alternative function 11
#define GPIO_AF_12                  (0x0CU)                                     ///< Alternative function 12
#define GPIO_AF_13                  (0x0DU)                                     ///< Alternative function 13
#define GPIO_AF_14                  (0x0EU)                                     ///< Alternative function 14
#define GPIO_AF_15                  (0x0FU)                                     ///< Alternative function 15

#define GPIO_PortSourceGPIOA 		(0x00U)
#define GPIO_PortSourceGPIOB 		(0x01U)
#define GPIO_PortSourceGPIOC 		(0x02U)
#define GPIO_PortSourceGPIOD 		(0x03U)

#define GPIO_PinSource0  			(0x00U)
#define GPIO_PinSource1  			(0x01U)
#define GPIO_PinSource2  			(0x02U)
#define GPIO_PinSource3  			(0x03U)
#define GPIO_PinSource4  			(0x04U)
#define GPIO_PinSource5  			(0x05U)
#define GPIO_PinSource6  			(0x06U)
#define GPIO_PinSource7  			(0x07U)
#define GPIO_PinSource8  			(0x08U)
#define GPIO_PinSource9  			(0x09U)
#define GPIO_PinSource10 			(0x0AU)
#define GPIO_PinSource11 			(0x0BU)
#define GPIO_PinSource12 			(0x0CU)
#define GPIO_PinSource13 			(0x0DU)
#define GPIO_PinSource14 			(0x0EU)
#define GPIO_PinSource15 			(0x0FU)

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup GPIO_Exported_Variables
/// @{

#ifdef _HAL_GPIO_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif



#undef GLOBAL

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup GPIO_Exported_Functions
/// @{
void GPIO_DeInit(GPIO_TypeDef* GPIOx);
void GPIO_AFIODeInit(void);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* pInitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* pInitStruct);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, u16 pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, u16 pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, u16 pin, BitAction value);
void GPIO_Write(GPIO_TypeDef* GPIOx, u16 value);
void GPIO_PinLock(GPIO_TypeDef* GPIOx, u16 pin, FunctionalState newState);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, u16 pin);
bool GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, u16 pin);
bool GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, u16 pin);

u16 GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
u16 GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);

#if defined(__MM3N1)
void GPIO_PinRemapConfig(u32 GPIO_Remap, FunctionalState newState);
#else
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, u8 pin, u8 GPIO_AF);
#endif

void exGPIO_PinAFConfig(GPIO_TypeDef* GPIOx, u16 pin, s32 remap, s8 funcAF);

void MM32_HAL_GPIO_SetPP(u16 target);

/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif /* __HAL_GPIO_H */
////////////////////////////////////////////////////////////////////////////////
