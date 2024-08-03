/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Header file for Pre-Compiler configuration used by Port Module
 *
 * Author: Nada Hamed
 ******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_
/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION   (3U)
/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION           (1U)
#define PORT_CFG_SW_MINOR_VERSION           (0U)
#define PORT_CFG_SW_PATCH_VERSION           (0U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                      (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                      (STD_OFF)

/*Pre-processor switch to enable/disable the use of the function Port_SetPinMode(). */
#define PORT_SET_PIN_MODE_API                      (STD_ON)

/*Pre-processor switch to enable/disable the use of the function Port_SetPinDirection(). */
#define PORT_SET_PIN_DIRECTION_API                 (STD_ON)
/* Number of the configured Port Pins */
#define PORT_CONFIGURED_PINS                        (39U)

/* PORT Configured Port Pin ID number */
#define PORT_A_PIN_0                                (Port_PinType)0
#define PORT_A_PIN_1                                (Port_PinType)1
#define PORT_A_PIN_2                                (Port_PinType)2
#define PORT_A_PIN_3                                (Port_PinType)3
#define PORT_A_PIN_4                                (Port_PinType)4
#define PORT_A_PIN_5                                (Port_PinType)5
#define PORT_A_PIN_6                                (Port_PinType)6
#define PORT_A_PIN_7                                (Port_PinType)7

#define PORT_B_PIN_0                                (Port_PinType)8
#define PORT_B_PIN_1                                (Port_PinType)9
#define PORT_B_PIN_2                                (Port_PinType)10
#define PORT_B_PIN_3                                (Port_PinType)11
#define PORT_B_PIN_4                                (Port_PinType)12
#define PORT_B_PIN_5                                (Port_PinType)13
#define PORT_B_PIN_6                                (Port_PinType)14
#define PORT_B_PIN_7                                (Port_PinType)15

#define PORT_C_PIN_4                                (Port_PinType)16
#define PORT_C_PIN_5                                (Port_PinType)17
#define PORT_C_PIN_6                                (Port_PinType)18
#define PORT_C_PIN_7                                (Port_PinType)19

#define PORT_D_PIN_0                                (Port_PinType)20
#define PORT_D_PIN_1                                (Port_PinType)21
#define PORT_D_PIN_2                                (Port_PinType)22
#define PORT_D_PIN_3                                (Port_PinType)23
#define PORT_D_PIN_4                                (Port_PinType)24
#define PORT_D_PIN_5                                (Port_PinType)25
#define PORT_D_PIN_6                                (Port_PinType)26
#define PORT_D_PIN_7                                (Port_PinType)27

#define PORT_E_PIN_0                                (Port_PinType)28
#define PORT_E_PIN_1                                (Port_PinType)29
#define PORT_E_PIN_2                                (Port_PinType)30
#define PORT_E_PIN_3                                (Port_PinType)31
#define PORT_E_PIN_4                                (Port_PinType)32
#define PORT_E_PIN_5                                (Port_PinType)33

#define PORT_F_PIN_0                                (Port_PinType)34
#define PORT_F_PIN_1                                (Port_PinType)35
#define PORT_F_PIN_2                                (Port_PinType)36
#define PORT_F_PIN_3                                (Port_PinType)37
#define PORT_F_PIN_4                                (Port_PinType)38

/********************** PORT Configuration for Used PORT_PINS ******************************/
/* PORT Configured Port NUM  */
#define PortConf_LED1_PORT_NUM                            (Port_PinType)5 /* PORTF */
#define PortConf_SW1_PORT_NUM                             (Port_PinType)5 /* PORTF */
/*PORT Configured PORT_PIN NUM */
#define PortConf_LED1_PORT_PIN_NUM                        (Port_PinType)1 /* Pin 1 in PORTF */
#define PortConf_SW1_PORT_PIN_NUM                         (Port_PinType)4 /* Pin 4 in PORTF */
/*PORT Configured  PORT DIRECTION */
#define PortConf_LED1_DIRECTION                           ((Port_PinDirectionType)PORT_PIN_OUT) /* Pin 1 in PORTF Direction */
#define PortConf_SW1_DIRECTION                            ((Port_PinDirectionType)PORT_PIN_IN )/* Pin 4 in PORTF Direction*/
/*PORT Configured RESISTOR */
#define PortConf_LED1_RESISTOR                            ((Port_InternalResistor)OFF)/* Pin 1 in PORTF Intial Resistor */
#define PortConf_SW1_RESISTOR                             ((Port_InternalResistor)PULL_UP) /* Pin 4 in PORTF Intial Resistor  */
/*PORT Configured  INTIAL VALUE */
#define PortConf_LED1_INTIAL_VALUE                        ((PORT_PIN_LEVEL_VALUE)PORT_PIN_LEVEL_LOW) /* Pin 1 in PORTF INTIAL VALUE*/
#define PortConf_SW1_INTIAL_VALUE                         ((PORT_PIN_LEVEL_VALUE)PORT_PIN_LEVEL_LOW) /* Pin 4 in PORTF INTIAL VALUE*/
/*PORT Configured MODE*/
#define PortConf_LED1_MODE                                ((Port_PinModeType)PORT_PIN_MODE_GPIO) /* Pin 1 in PORTF Intial Mode */
#define PortConf_SW1_MODE                                 ((Port_PinModeType)PORT_PIN_MODE_GPIO) /* Pin 4 in PORTF Intial Mode */
/*PORT Configured MODE CHANGE PROPERTY*/
#define PortConf_LED1_MODE_CHANGE                        ((PORT_PIN_MODE_CHANGEABLE)YES_MODE_CHANGE) /* Pin 1 in PORTF MODE CHANGE PROPERTY */
#define PortConf_SW1_MODE_CHANGE                         ((PORT_PIN_MODE_CHANGEABLE)YES_MODE_CHANGE) /* Pin 4 in PORTF MODE CHANGE PROPERTY*/
/*PORT Configured DIRECTION CHANGE PROPERTY*/
#define PortConf_LED1_DIR_CHANGE                         ((PORT_PIN_DIRECTION_CHANGEABLE)YES_DIR_CHANGE) /* Pin 1 in PORTF DIRECTION CHANGE PROPERTY*/
#define PortConf_SW1_DIR_CHANGE                          ((PORT_PIN_DIRECTION_CHANGEABLE)YES_DIR_CHANGE) /* Pin 4 in PORTF DIRECTION CHANGE PROPERTY*/


/********************** PORT Configuration for Unused PORT_PINS ******************************/
/*PORT Configured  DEFAULT PORT DIRECTION FOR UNUSED PORT_PINS */
#define PortConf_DEFAULT_DIRECTION                       ((Port_PinDirectionType)PORT_PIN_IN )/* Default Input Direction */
/*PORT Configured  DEFAULT PORT RESISTOR FOR UNUSED PORT_PINS */
#define PortConf_DEFAULT_RESISTOR                        ((Port_InternalResistor)OFF) /* Default Input Resistor */
/*PORT Configured  DEFAULT PORT INTIAL VALUE FOR UNUSED PORT_PINS */
#define PortConf_DEFAULT_INTIAL_VALUE                    ((PORT_PIN_LEVEL_VALUE)PORT_PIN_LEVEL_LOW) /*Default Initial Value */
/*PORT Configured  DEFAULT PORT MODE FOR UNUSED PORT_PINS */
#define PortConf_DEFAULT_MODE                            ((Port_PinModeType)PORT_PIN_MODE_GPIO) /*Default Mode */
/*PORT Configured DEFAULT DIRECTION CHANGE PROPERTY FOR UNUSED PORT_PINS*/
#define PortConf_DEFAULT_DIR_CHANGE                      ((PORT_PIN_DIRECTION_CHANGEABLE)NO_DIR_CHANGE) /* DEFAULT DIRECTION CHANGE PROPERTY*/
/*PORT Configured DEFAULT MODE CHANGE PROPERTY FOR UNUSED PORT_PINS*/
#define PortConf_DEFAULT_MODE_CHANGE                     ((PORT_PIN_MODE_CHANGEABLE)NO_MODE_CHANGE) /* DEFAULT MODE CHANGE PROPERTY */
/*PORT Configured PORT and PORT_PIN NUM for Unused PORT_PINS  */
#define PortConf_PA0_PORT_NUM                             (Port_PinType)0 /* PORTA */
#define PortConf_PA1_PORT_NUM                             (Port_PinType)0/* PORTA */
#define PortConf_PA0_PORT_PIN_NUM                         (Port_PinType)0 /* Pin 0 in PORTA */
#define PortConf_PA1_PORT_PIN_NUM                         (Port_PinType)1/* Pin 1 in PORTF */
#define PortConf_PA2_PORT_NUM                             (Port_PinType)0 /* PORTA */
#define PortConf_PA3_PORT_NUM                             (Port_PinType)0/* PORTA */
#define PortConf_PA2_PORT_PIN_NUM                         (Port_PinType)2/* Pin 2 in PORTA */
#define PortConf_PA3_PORT_PIN_NUM                         (Port_PinType)3/* Pin 3 in PORTA */
#define PortConf_PA4_PORT_NUM                             (Port_PinType)0 /* PORTA */
#define PortConf_PA5_PORT_NUM                             (Port_PinType)0/* PORTA */
#define PortConf_PA4_PORT_PIN_NUM                         (Port_PinType)4/* Pin 4 in PORTA */
#define PortConf_PA5_PORT_PIN_NUM                         (Port_PinType)5/* Pin 5 in PORTA */
#define PortConf_PA6_PORT_NUM                             (Port_PinType)0 /* PORTA */
#define PortConf_PA7_PORT_NUM                             (Port_PinType)0/* PORTA */
#define PortConf_PA6_PORT_PIN_NUM                         (Port_PinType)6/* Pin 6 in PORTA */
#define PortConf_PA7_PORT_PIN_NUM                         (Port_PinType)7/* Pin 7 in PORTA */

#define PortConf_PB0_PORT_NUM                             (Port_PinType)1 /* PORTB */
#define PortConf_PB1_PORT_NUM                             (Port_PinType)1/* PORTB */
#define PortConf_PB0_PORT_PIN_NUM                         (Port_PinType)0 /* Pin 0 in PORTB */
#define PortConf_PB1_PORT_PIN_NUM                         (Port_PinType)1/* Pin 1 in PORTB */
#define PortConf_PB2_PORT_NUM                             (Port_PinType)1 /* PORTB */
#define PortConf_PB3_PORT_NUM                             (Port_PinType)1 /* PORTB */
#define PortConf_PB2_PORT_PIN_NUM                         (Port_PinType)2/* Pin 2 in PORTB */
#define PortConf_PB3_PORT_PIN_NUM                         (Port_PinType)3/* Pin 3 in PORTB */
#define PortConf_PB4_PORT_NUM                             (Port_PinType)1 /* PORTB */
#define PortConf_PB5_PORT_NUM                             (Port_PinType)1 /* PORTB */
#define PortConf_PB4_PORT_PIN_NUM                         (Port_PinType)4/* Pin 4 in PORTB */
#define PortConf_PB5_PORT_PIN_NUM                         (Port_PinType)5/* Pin 5 in PORTB */
#define PortConf_PB6_PORT_NUM                             (Port_PinType)1 /* PORTB */
#define PortConf_PB7_PORT_NUM                             (Port_PinType)1 /* PORTB */
#define PortConf_PB6_PORT_PIN_NUM                         (Port_PinType)6/* Pin 6 in PORTB */
#define PortConf_PB7_PORT_PIN_NUM                         (Port_PinType)7/* Pin 7 in PORTB */

#define PortConf_PC4_PORT_NUM                             (Port_PinType)2 /* PORTC */
#define PortConf_PC5_PORT_NUM                             (Port_PinType)2 /* PORTC */
#define PortConf_PC4_PORT_PIN_NUM                         (Port_PinType)4/* Pin 4 in PORTC */
#define PortConf_PC5_PORT_PIN_NUM                         (Port_PinType)5/* Pin 5 in PORTC */
#define PortConf_PC6_PORT_NUM                             (Port_PinType)2 /* PORTC */
#define PortConf_PC7_PORT_NUM                             (Port_PinType)2 /* PORTC */
#define PortConf_PC6_PORT_PIN_NUM                         (Port_PinType)6/* Pin 6 in PORTC */
#define PortConf_PC7_PORT_PIN_NUM                         (Port_PinType)7/* Pin 7 in PORTC */

#define PortConf_PD0_PORT_NUM                             (Port_PinType)3 /* PORTD */
#define PortConf_PD1_PORT_NUM                             (Port_PinType)3/* PORTD */
#define PortConf_PD0_PORT_PIN_NUM                         (Port_PinType)0 /* Pin 0 in PORTD */
#define PortConf_PD1_PORT_PIN_NUM                         (Port_PinType)1/* Pin 1 in PORTD */
#define PortConf_PD2_PORT_NUM                             (Port_PinType)3 /* PORTD */
#define PortConf_PD3_PORT_NUM                             (Port_PinType)3 /* PORTD */
#define PortConf_PD2_PORT_PIN_NUM                         (Port_PinType)2/* Pin 2 in PORTD */
#define PortConf_PD3_PORT_PIN_NUM                         (Port_PinType)3/* Pin 3 in PORTD */
#define PortConf_PD4_PORT_NUM                             (Port_PinType)3 /* PORTD */
#define PortConf_PD5_PORT_NUM                             (Port_PinType)3 /* PORTD */
#define PortConf_PD4_PORT_PIN_NUM                         (Port_PinType)4/* Pin 4 in PORTD */
#define PortConf_PD5_PORT_PIN_NUM                         (Port_PinType)5/* Pin 5 in PORTD */
#define PortConf_PD6_PORT_NUM                             (Port_PinType)3 /* PORTD */
#define PortConf_PD7_PORT_NUM                             (Port_PinType)3 /* PORTD */
#define PortConf_PD6_PORT_PIN_NUM                         (Port_PinType)6/* Pin 6 in PORTD */
#define PortConf_PD7_PORT_PIN_NUM                         (Port_PinType)7/* Pin 7 in PORTD */

#define PortConf_PE0_PORT_NUM                             (Port_PinType)4 /* PORTE */
#define PortConf_PE1_PORT_NUM                             (Port_PinType)4 /* PORTE */
#define PortConf_PE0_PORT_PIN_NUM                         (Port_PinType)0 /* Pin 0 in PORTE */
#define PortConf_PE1_PORT_PIN_NUM                         (Port_PinType)1/* Pin 1 in PORTE */
#define PortConf_PE2_PORT_NUM                             (Port_PinType)4 /* PORTE */
#define PortConf_PE3_PORT_NUM                             (Port_PinType)4 /* PORTE */
#define PortConf_PE2_PORT_PIN_NUM                         (Port_PinType)2/* Pin 2 in PORTE */
#define PortConf_PE3_PORT_PIN_NUM                         (Port_PinType)3/* Pin 3 in PORTE */
#define PortConf_PE4_PORT_NUM                             (Port_PinType)4 /* PORTE */
#define PortConf_PE5_PORT_NUM                             (Port_PinType)4 /* PORTE */
#define PortConf_PE4_PORT_PIN_NUM                         (Port_PinType)4/* Pin 4 in PORTE */
#define PortConf_PE5_PORT_PIN_NUM                         (Port_PinType)5/* Pin 5 in PORTE */

#define PortConf_PF0_PORT_NUM                             (Port_PinType)5 /* PORTF */
#define PortConf_PF0_PORT_PIN_NUM                         (Port_PinType)0 /* Pin 0 in PORTF */
#define PortConf_PF2_PORT_NUM                             (Port_PinType)5 /* PORTF */
#define PortConf_PF3_PORT_NUM                             (Port_PinType)5 /* PORTF */
#define PortConf_PF2_PORT_PIN_NUM                         (Port_PinType)2/* Pin 2 in PORTF */
#define PortConf_PF3_PORT_PIN_NUM                         (Port_PinType)3/* Pin 3 in PORTF */


#endif /* PORT_CFG_H_ */
