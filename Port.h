 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Nada Hamed
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Mohamed Tarek's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)
/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)
/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif
/* Dio Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PORT Init */
#define PORT_INIT_SID                          (uint8)0x00

/* Service ID for PORT Set Pin Direction */
#define PORT_SET_PIN_DIRECTION_SID             (uint8)0x01

/* Service ID for Refresh Direction PORT */
#define PORT_REFRESH_PORT_DIRECTION_SID        (uint8)0x02

/* Service ID for PORT GetVersionInfo  */
#define PORT_GET_VERSION_INFO_SID              (uint8)0x03

/* Service ID for PORT Set Pin Mode */
#define PORT_SET_PIN_MODE_SID                  (uint8)0x04
/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                          (uint8)0x0A

/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE             (uint8)0x0B

/* API Port_Init service called with wrong parameter. */
#define PORT_E_PARAM_CONFIG                       (uint8)0x0C

/*
 * The API service shall return immediately without any further action,
 * beside reporting this development error.
 */
#define PORT_E_PARAM_POINTER                       (uint8)0x10

/* API Port_Init service called with wrong parameter. */
#define PORT_E_PARAM_INVALID_MODE                  (uint8)0x0D

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE                   (uint8)0x0E

/* API service called without module initialization */
#define PORT_E_UNINIT                              (uint8)0x0F

/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
/* Type definition for PORT Pin num used by the PORT APIs */
typedef uint8 Port_PinType;

/* Type definition for PORT Pin Mode */
typedef uint8 Port_PinModeType;

/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,PORT_PIN_OUT
}Port_PinDirectionType ;

/* Description: Enum to hold PIN Level value */
typedef enum
{
   PORT_PIN_LEVEL_LOW,PORT_PIN_LEVEL_HIGH
}PORT_PIN_LEVEL_VALUE ;

/* Description: Enum to hold  PIN DIR CHANGEBILITY */
typedef enum
{
   NO_DIR_CHANGE,YES_DIR_CHANGE
}PORT_PIN_DIRECTION_CHANGEABLE ;

/* Description: Enum to hold PIN PIN MODE CHANGEBILITY */
typedef enum
{
    NO_MODE_CHANGE,YES_MODE_CHANGE
}PORT_PIN_MODE_CHANGEABLE ;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: Enum to hold Port pin mode from mode list*/
typedef enum
{
    PORT_PIN_MODE_ADC,PORT_PIN_MODE_CAN,PORT_PIN_MODE_GPIO,PORT_PIN_MODE_UART,
    PORT_PIN_MODE_M0PWM ,PORT_PIN_MODE_I2C ,PORT_PIN_MODE_SSI0,
    PORT_PIN_MODE_SSI1 ,PORT_PIN_MODE_SSI2,PORT_PIN_MODE_SSI3,PORT_PIN_MODE_M1PWM,PORT_PIN_MODE_IDX
    ,PORT_PIN_MODE_TxCCPx,PORT_PIN_MODE_WTxCCPx,PORT_PIN_MODE_USB,PORT_PIN_MODE_TRD
}PORT_PIN_MODE;


/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *  3. the direction of pin --> INPUT or OUTPUT
 *  4. the internal resistor --> Disable, Pull up or Pull down
 *  5. the initial value of pin if its input
 *  6. the mode of the pin
 *  7. is it DIRECTION_CHANGEABLE
 *  8. is it MODE_CHANGEABLE
 */
typedef struct 
{
    Port_PinType port_num;
    Port_PinType pin_num;
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;/*if its input(button)*/
    PORT_PIN_LEVEL_VALUE initial_value;/*if its output (led)*/
    Port_PinModeType mode;
    PORT_PIN_DIRECTION_CHANGEABLE DIR_Change;
    PORT_PIN_MODE_CHANGEABLE MODE_Change;
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function toInitializes the Port Driver module.
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr ) ;

/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin Port-> Pin ID number ,Direction-> Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Sets the port pin direction
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API  == STD_ON)
void Port_SetPinDirection(Port_PinType Pin , Port_PinDirectionType Direction);
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void);

/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin , Mode
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Sets the port pin mode.
************************************************************************************/
#if (PORT_SET_PIN_MODE_API  == STD_ON)
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode );
#endif

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): versioninfo
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function Returns the version information of this module.
************************************************************************************/
#if (PORT_VERSION_INFO_API  == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo );

#endif
/*******************************************************************************
 *                       Global And External Variables                         *
 *******************************************************************************/

/* Extern PB structures to be used by PORT and other modules */
extern const  Port_ConfigType Port_Configurations [PORT_CONFIGURED_PINS];
/*Global arrays to store property of mode and direction changeability  for each configured pin*/
uint8 ModeChangeProperty_arr[PORT_CONFIGURED_PINS];
uint8 DirChangeProperty_arr[PORT_CONFIGURED_PINS];

#endif /* PORT_H */
