/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Nada Hamed
 ******************************************************************************/
#include "Port.h"
/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION   (3U)
/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION           (1U)
#define PORT_PBCFG_SW_MINOR_VERSION           (0U)
#define PORT_PBCFG_SW_PATCH_VERSION           (0U)
/* AUTOSAR Version checking between Port_PBCfg.h and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBCfg.h and Port.h files */
#if ((Port_PBCFG_SW_MAJOR_VERSION != Port_SW_MAJOR_VERSION)\
        ||  (Port_PBCFG_SW_MINOR_VERSION != Port_SW_MINOR_VERSION)\
        ||  (Port_PBCFG_SW_PATCH_VERSION != Port_SW_PATCH_VERSION))
#error "The SW version of Port_PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init API */

const Port_ConfigType Port_Configurations [PORT_CONFIGURED_PINS]= {

                                                            {PortConf_PA0_PORT_NUM , PortConf_PA0_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PA1_PORT_NUM , PortConf_PA1_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PA2_PORT_NUM , PortConf_PA2_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PA3_PORT_NUM , PortConf_PA3_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PA4_PORT_NUM , PortConf_PA4_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PA5_PORT_NUM , PortConf_PA5_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PA6_PORT_NUM , PortConf_PA6_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PA7_PORT_NUM , PortConf_PA7_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PB0_PORT_NUM , PortConf_PB0_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PB1_PORT_NUM , PortConf_PB1_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PB2_PORT_NUM , PortConf_PB2_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PB3_PORT_NUM , PortConf_PB3_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PB4_PORT_NUM , PortConf_PB4_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PB5_PORT_NUM , PortConf_PB5_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PB6_PORT_NUM , PortConf_PB6_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PB7_PORT_NUM , PortConf_PB7_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PC4_PORT_NUM , PortConf_PC4_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PC5_PORT_NUM , PortConf_PC5_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PC6_PORT_NUM , PortConf_PC6_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PC7_PORT_NUM , PortConf_PC7_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PD0_PORT_NUM , PortConf_PD0_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PD1_PORT_NUM , PortConf_PD1_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PD2_PORT_NUM , PortConf_PD2_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PD3_PORT_NUM , PortConf_PD3_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PD4_PORT_NUM , PortConf_PD4_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PD5_PORT_NUM , PortConf_PD5_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PD6_PORT_NUM , PortConf_PD6_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PD7_PORT_NUM , PortConf_PD7_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PE0_PORT_NUM , PortConf_PE0_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PE1_PORT_NUM , PortConf_PE1_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PE2_PORT_NUM , PortConf_PE2_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PE3_PORT_NUM , PortConf_PE3_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PE4_PORT_NUM , PortConf_PE4_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PE5_PORT_NUM , PortConf_PE5_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PF0_PORT_NUM , PortConf_PF0_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_LED1_PORT_NUM, PortConf_LED1_PORT_PIN_NUM, PortConf_LED1_DIRECTION, PortConf_LED1_RESISTOR, PortConf_LED1_INTIAL_VALUE, PortConf_LED1_MODE, PortConf_LED1_DIR_CHANGE , PortConf_LED1_MODE_CHANGE },
                                                            {PortConf_PF2_PORT_NUM , PortConf_PF2_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_PF3_PORT_NUM , PortConf_PF3_PORT_PIN_NUM  , PortConf_DEFAULT_DIRECTION, PortConf_DEFAULT_RESISTOR, PortConf_DEFAULT_INTIAL_VALUE , PortConf_DEFAULT_MODE, PortConf_DEFAULT_DIR_CHANGE , PortConf_DEFAULT_MODE_CHANGE},
                                                            {PortConf_SW1_PORT_NUM , PortConf_SW1_PORT_PIN_NUM , PortConf_SW1_DIRECTION, PortConf_SW1_RESISTOR, PortConf_SW1_INTIAL_VALUE , PortConf_SW1_MODE, PortConf_SW1_DIR_CHANGE, PortConf_SW1_MODE_CHANGE}
};


















