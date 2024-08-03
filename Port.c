/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Nada Hamed
 ******************************************************************************/

#include "Port.h"
#include "tm4c123gh6pm_registers.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

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

void Port_Init(const Port_ConfigType* ConfigPtr )
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
                        PORT_E_PARAM_CONFIG);
    }
    else
#endif
    {      /*
     * Set the module state to initialized and point to the PB configuration structure using a global pointer.
     * This global pointer is global to be used by other functions to read the PB configuration structures
     */
        Port_Status = PORT_INITIALIZED;
        volatile uint32 * Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */
        uint8 count;
        for(count=0 ; count<PORT_CONFIGURED_PINS;count++)
        {
            switch(ConfigPtr[count].port_num)
            {
            case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
            case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
            case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
            case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
            case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
            case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
            }

            if( ((ConfigPtr[count].port_num == 3) && (ConfigPtr[count].pin_num == 7)) || ((ConfigPtr[count].port_num == 5) && (ConfigPtr[count].pin_num == 0)) ) /* PD7 or PF0 */
            {
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B; /* Unlock the GPIOCR register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_COMMIT_REG_OFFSET) , ConfigPtr[count].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }

            else if( (ConfigPtr[count].port_num == 2) && (ConfigPtr[count].pin_num <= 3) ) /* PC0 to PC3 */
            {
                /* Do Nothing ...  this is the JTAG pins */
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

            switch(ConfigPtr[count].mode)
            {
            case  0:   /* ADC MODE */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET ) , ConfigPtr[count].pin_num); /* Clear the corresponding bit in the GPIODEN register to disable Digital function */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[count].pin_num);  /* Set the corresponding bit in the GPIOAMSEL register to configure it as ADC input pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET ),ConfigPtr[count].pin_num);   /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
                // *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[count].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
                // *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |=(0x0000000F << (ConfigPtr->pin_num * 4));   /*Setting the PMCx bits for this pin */
                break;

            case  1:  /* CAN0 AND CAN1 MODE */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[count].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
                if(ConfigPtr[count].port_num == 5)
                {/*for port F have CAN PMCx=3*/
                    *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000003 << (ConfigPtr[count].pin_num * 4));     /* Set the PMCx bits for this pin */
                }
                else
                {
                    *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000008 << (ConfigPtr[count].pin_num * 4));     /* Set the PMCx bits for this pin */
                }

                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,ConfigPtr[count].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[count].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                break;

            case  2: /* GPIO MODE */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[count].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[count].pin_num * 4));     /* Clear the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[count].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                break;

            case  3:  /* UART MODE */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[count].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[count].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000001 << (ConfigPtr[count].pin_num * 4));     /* Set the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[count].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                break;

            case  4:  /* M0PWM MODE */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[count].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[count].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000004 << (ConfigPtr[count].pin_num * 4));     /* Set the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[count].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                break;

            case  5:  /* I2C MODE*/
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[count].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[count].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000003 << (ConfigPtr[count].pin_num * 4));     /* Set the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[count].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                break;

            case  6:  /*SSI0 MODE */
            case  7:  /*SSI1 MODE */
            case  8: /* SSI2 MODE */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[count].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[count].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000002 << (ConfigPtr[count].pin_num * 4));     /* Set the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[count].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                break;
            case  9: /* SSI3 MODE */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[count].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[count].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000001 << (ConfigPtr[count].pin_num * 4));     /* Set the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[count].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                break;
            case  10: /* M1PWM MODE */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[count].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[count].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000005 << (ConfigPtr[count].pin_num * 4));     /* Set the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[count].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                break;
            case  11: /* IDX0 and IDX1 MODE */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[count].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[count].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000006 << (ConfigPtr[count].pin_num * 4));     /* Set the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[count].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                break;
            case  12: /* TxCCPx MODE */
            case  13: /* WTxCCPx MODE */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[count].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[count].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000007 << (ConfigPtr[count].pin_num * 4));     /* Set the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[count].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                break;
            case  14: /* USB MODE */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[count].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[count].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000008 << (ConfigPtr[count].pin_num * 4));     /* Set the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[count].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                break;
            case  15: /* TRD1 AND TRD0 MODE */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[count].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[count].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x0000000E << (ConfigPtr[count].pin_num * 4));     /* Set the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[count].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                break;

            }

            if(ConfigPtr[count].direction == PORT_PIN_OUT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr[count].pin_num);/* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                if(ConfigPtr[count].initial_value == PORT_PIN_LEVEL_HIGH)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr[count].pin_num); /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr[count].pin_num); /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                }
            }

            else if(ConfigPtr[count].direction == PORT_PIN_IN)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr[count].pin_num);    /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                if(ConfigPtr[count].resistor == PULL_UP)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr[count].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                }
                else if(ConfigPtr[count].resistor == PULL_DOWN)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr[count].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                }
                else if(ConfigPtr[count].resistor == OFF)
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr[count].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr[count].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                }
            }
            else
            {
                /* Do Nothing */
            }
            /*count equals PinID store info about Pin*/
            if (ConfigPtr[count].MODE_Change == YES_MODE_CHANGE)
            {/*pin Mode is changeable during runtime*/
                ModeChangeProperty_arr[count]=STD_ON;
            }
            else
            {/*pin Mode is not changeable during runtime*/
                ModeChangeProperty_arr[count]=STD_OFF;
            }
            if (ConfigPtr[count].DIR_Change == YES_DIR_CHANGE)
            {/*pin direction is changeable during runtime*/
                DirChangeProperty_arr[count]=STD_ON;
            }
            else
            {/*pin direction is not changeable during runtime*/
                DirChangeProperty_arr[count]=STD_OFF;
            }
        }
    }
}
/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Pin Port-> Pin ID number(0->38) ,Direction-> Port Pin Direction
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Sets the port pin direction
 ************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API  == STD_ON)
void Port_SetPinDirection(Port_PinType Pin , Port_PinDirectionType Direction)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the Pin ID is Correct */
    if(Pin>=PORT_CONFIGURED_PINS)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
    }
    else
    {
        /* No Action Required */
    }
    /*Check if Port Pin configured as changeable*/
    if (DirChangeProperty_arr[Pin] == STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
    }
    else
    {
        /* No Action Required */
    }
#endif

    volatile uint32 * Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    if(Pin<=7)
    {
        Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
    }
    else if(Pin>=8 && Pin<=15)
    {
        Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
    }
    else if(Pin>=16 && Pin<=19)
    {
        Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
    }
    else if(Pin>=20 && Pin<=27)
    {
        Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
    }
    else if(Pin>=28 && Pin<=33)
    {
        Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
    }
    else if(Pin>=34 && Pin<=38)
    {
        Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
    }

    if(Direction==PORT_PIN_IN)
    {/*Input Pin*/
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) ,Port_Configurations[Pin].pin_num);    /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

    }
    else
    {/*Output Pin*/
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) ,Port_Configurations[Pin].pin_num);    /* Setting the corresponding bit in the GPIODIR register to configure it as Output pin */
    }
}


#endif

/************************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Refreshes port direction.The function Port_RefreshPortDirection
 * shall exclude those port pins from refreshing that are configured as
 *  ‘pin direction changeable during runtime‘.
 ************************************************************************************/
void Port_RefreshPortDirection(void)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
    }
    else
    {
        /* No Action Required */
    }
#endif
    uint8 count;

    for(count=0;count<PORT_CONFIGURED_PINS;count++)
    {
        volatile uint32 * Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */

        /*this port configured as ‘pin direction not changeable during runtime‘.*/
        if(DirChangeProperty_arr[count]==STD_OFF)
        {
            if(count<=7)
            {
                Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            }
            else if(count>=8 && count<=15)
            {
                Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            }
            else if(count>=16 && count<=19)
            {
                Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            }
            else if(count>=20 && count<=27)
            {
                Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            }
            else if(count>=28 && count<=33)
            {
                Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            }
            else if(count>=34 && count<=38)
            {
                Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            }
            /*Refresh Port_Pin Direction*/
            if(Port_Configurations[count].direction == PORT_PIN_IN)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) ,Port_Configurations[count].pin_num);    /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

            }
            else
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) ,Port_Configurations[count].pin_num);    /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            }
        }

        else
        {
            /* No Action Required */
        }

    }
}
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
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode )
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
    }
    else
    {
        /* No Action Required */
    }
    /*Check if Port Pin configured as changeable*/
    if (ModeChangeProperty_arr[Pin] == STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID ,
                        PORT_E_MODE_UNCHANGEABLE);
    }
    else
    {
        /*NOTHING*/
    }
    /* Check if the Pin ID is Correct */
    if(Pin>=PORT_CONFIGURED_PINS)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
    }
    else
    {
        /* No Action Required */
    }
    boolean error = TRUE;
    /*Check If Port Pin Mode passed is Supported by this Pin */
    switch(Pin)
    {
    case 0:/*PA0*/
    case 1:/*PA1*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_UART)||(Mode==PORT_PIN_MODE_CAN))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 2:/*PA2*/
    case 3:/*PA3*/
    case 4:/*PA4*/
    case 5:/*PA5*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_SSI0))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 6:/*PA6*/
    case 7:/*PA7*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_I2C)||(Mode==PORT_PIN_MODE_M1PWM))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 8:/*PB0*/
    case 9:/*PB1*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_UART)||(Mode==PORT_PIN_MODE_TxCCPx))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 10:/*PB2*/
    case 11:/*PB3*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_I2C)||(Mode==PORT_PIN_MODE_TxCCPx))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 12:/*PB4*/
    case 13:/*PB5*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_ADC)||(Mode==PORT_PIN_MODE_SSI2)||(Mode==PORT_PIN_MODE_M0PWM)||(Mode==PORT_PIN_MODE_CAN)||(Mode==PORT_PIN_MODE_TxCCPx))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 14:/*PB6*/
    case 15:/*PB7*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_SSI2)||(Mode==PORT_PIN_MODE_M0PWM)||(Mode==PORT_PIN_MODE_TxCCPx))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 16:/*PC4*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_UART)||(Mode==PORT_PIN_MODE_M0PWM)||(Mode==PORT_PIN_MODE_IDX)||(Mode==PORT_PIN_MODE_WTxCCPx))
            error = FALSE;
        else
            error = TRUE;
        break;
    case 17:/*PC5*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_UART)||(Mode==PORT_PIN_MODE_M0PWM)||(Mode==PORT_PIN_MODE_WTxCCPx))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 18:/*PC6*/
    case 19:/*PC7*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_UART)||(Mode==PORT_PIN_MODE_WTxCCPx)||(Mode==PORT_PIN_MODE_USB))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 20:/*PD0*/
    case 21:/*PD1*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_ADC)||(Mode==PORT_PIN_MODE_SSI3)||(Mode==PORT_PIN_MODE_SSI1)
                ||(Mode==PORT_PIN_MODE_I2C)||(Mode==PORT_PIN_MODE_M0PWM)||(Mode==PORT_PIN_MODE_M1PWM)||(Mode==PORT_PIN_MODE_WTxCCPx))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 22:/*PD2*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_ADC)||(Mode==PORT_PIN_MODE_SSI3)||(Mode==PORT_PIN_MODE_SSI1)
                ||(Mode==PORT_PIN_MODE_WTxCCPx)||(Mode==PORT_PIN_MODE_USB))
            error = FALSE;
        else
            error = TRUE;
        break;
    case 23:/*PD3*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_ADC)||(Mode==PORT_PIN_MODE_SSI3)
                ||(Mode==PORT_PIN_MODE_SSI1)||(Mode==PORT_PIN_MODE_IDX)||(Mode==PORT_PIN_MODE_WTxCCPx)||(Mode==PORT_PIN_MODE_USB))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 24:/*PD4*/
    case 25:/*PD5*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_UART)||(Mode==PORT_PIN_MODE_WTxCCPx))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 26:/*PD6*/
    case 27:/*PD7*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_UART)||(Mode==PORT_PIN_MODE_WTxCCPx))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 28:/*PE0*/
    case 29:/*PE1*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_UART)||(Mode==PORT_PIN_MODE_ADC))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 30:/*PE2*/
    case 31:/*PE3*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_ADC))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 32:/*PE4*/
    case 33:/*PE5*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_ADC)||(Mode==PORT_PIN_MODE_UART)||(Mode==PORT_PIN_MODE_I2C)||(Mode==PORT_PIN_MODE_M0PWM)||(Mode==PORT_PIN_MODE_M1PWM)||(Mode==PORT_PIN_MODE_CAN))
            error = FALSE;
        else
            error = TRUE;
        break;
    case 34:/*PF0*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_SSI1)||(Mode==PORT_PIN_MODE_M1PWM)||(Mode==PORT_PIN_MODE_CAN)||(Mode==PORT_PIN_MODE_TxCCPx))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 35:/*PF1*/
    case 36:/*PF2*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_SSI1)||(Mode==PORT_PIN_MODE_M1PWM)||(Mode==PORT_PIN_MODE_TxCCPx)||(Mode==PORT_PIN_MODE_TRD))
            error = FALSE;
        else
            error = TRUE;
        break;

    case 37:/*PF3*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_SSI1)||(Mode==PORT_PIN_MODE_M1PWM)||(Mode==PORT_PIN_MODE_CAN)||(Mode==PORT_PIN_MODE_TxCCPx))
            error = FALSE;
        else
            error = TRUE;
        break;
    case 38:/*PF4*/
        if((Mode==PORT_PIN_MODE_GPIO)||(Mode==PORT_PIN_MODE_IDX)||(Mode==PORT_PIN_MODE_TxCCPx)||(Mode==PORT_PIN_MODE_USB))
            error = FALSE;
        else
            error = TRUE;
        break;
    }
    /*If enterred mode not supported by this pin or incorrect mode input_mode>15*/
    if(error==TRUE)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
    }
    else
    {
        /*No Action Required*/
    }
#endif

    volatile uint32 * Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    if(Pin<=7)
    {
        Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
    }
    else if(Pin>=8 && Pin<=15)
    {
        Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
    }
    else if(Pin>=16 && Pin<=19)
    {
        Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
    }
    else if(Pin>=20 && Pin<=27)
    {
        Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
    }
    else if(Pin>=28 && Pin<=33)
    {
        Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
    }
    else if(Pin>=34 && Pin<=38)
    {
        Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
    }
    switch(Mode)
    {
    case  0:   /* ADC MODE */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET ) , Port_Configurations[Pin].pin_num); /* Clear the corresponding bit in the GPIODEN register to disable Digital function */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configurations[Pin].pin_num);  /* Set the corresponding bit in the GPIOAMSEL register to configure it as ADC input pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET ),Port_Configurations[Pin].pin_num);   /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
        //*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurations[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
        //*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &=(0x0000000F << (ConfigPtr->pin_num * 4));   /*Setting the PMCx bits for this pin */
        break;

    case  1:  /* CAN0 AND CAN1 MODE */
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurations[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
        if(Port_Configurations[Pin].port_num == 5)
        {/*for port F have CAN PMCx=3*/
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000003 << (Port_Configurations[Pin].pin_num * 4));     /* Set the PMCx bits for this pin */
        }
        else
        {
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000008 << (Port_Configurations[Pin].pin_num * 4));     /* Set the PMCx bits for this pin */
        }

        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configurations[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,Port_Configurations[Pin].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configurations[Pin].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        break;

    case  2: /* GPIO MODE */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,Port_Configurations[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configurations[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurations[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configurations[Pin].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        break;

    case  3:  /* UART MODE */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,Port_Configurations[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configurations[Pin].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurations[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000001 << (Port_Configurations[Pin].pin_num * 4));     /* Set the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) ,Port_Configurations[Pin].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        break;

    case  4:  /* M0PWM MODE */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configurations[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,Port_Configurations[Pin].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurations[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000004 <<(Port_Configurations[Pin].pin_num * 4));     /* Set the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) ,Port_Configurations[Pin].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        break;

    case  5:  /* I2C MODE*/
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configurations[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configurations[Pin].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurations[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000003 << (Port_Configurations[Pin].pin_num * 4));     /* Set the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) ,Port_Configurations[Pin].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        break;

    case  6:  /*SSI0 MODE */
    case  7:  /*SSI1 MODE */
    case  8: /* SSI2 MODE */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,Port_Configurations[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configurations[Pin].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurations[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000002 << (Port_Configurations[Pin].pin_num * 4));     /* Set the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configurations[Pin].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        break;

    case  9: /* SSI3 MODE */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configurations[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configurations[Pin].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurations[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000001 << (Port_Configurations[Pin].pin_num * 4));     /* Set the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configurations[Pin].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        break;
    case  10: /* M1PWM MODE */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configurations[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configurations[Pin].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurations[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000005 << (Port_Configurations[Pin].pin_num * 4));     /* Set the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configurations[Pin].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        break;
    case  11: /* IDX0 AND IDX1 MODE */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configurations[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configurations[Pin].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurations[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000006 << (Port_Configurations[Pin].pin_num * 4));     /* Set the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configurations[Pin].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        break;
    case  12: /* TxCCPx MODE */
    case  13: /* WTxCCPx MODE */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configurations[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configurations[Pin].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurations[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000007 << (Port_Configurations[Pin].pin_num * 4));     /* Set the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configurations[Pin].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        break;
    case  14: /* USB MODE */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configurations[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configurations[Pin].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurations[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000008 << (Port_Configurations[Pin].pin_num * 4));     /* Set the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configurations[Pin].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        break;
    case  15: /* TRD0 AND TRD1 MODE */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configurations[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configurations[Pin].pin_num);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurations[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin before setting new value*/
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x0000000E << (Port_Configurations[Pin].pin_num * 4));     /* Set the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configurations[Pin].pin_num);   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        break;
    }
}
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
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo )
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT);
    }
    else
    {
        /* No Action Required */
    }
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }
    else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}

#endif
























