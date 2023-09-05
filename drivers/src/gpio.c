/*
 * Description: Functions to use the GPIOs of the MCU.
 *
 * Author: Julian Rodriguez (jnrodriguezz@hotmail.com)
 * Date: Aug 2023
 *
 */

#include "stm32f103x8.h"
#include "gpio.h"

/*-- Macros and constants ----------------------------------------------------*/
#define GPIO_NUMBER (16u)
#define TOP_GPIO_PIN_IN_CR (7u) /*! Top register in CRL and CRH register. */

/*-- Public functions definition ---------------------------------------------*/
void gpio_init(void)
{
    DEVMAP->RCC.REGs.APB2ENR |= 0x3E; // enable all GPIOs clock
}

void gpio_config_output(uint8_t gpio_port, GPIO_pin_number_t pin, 
        GPIO_pin_cnf_output_t config, GPIO_pin_mode_t mode)
{
    uint8_t crhl_offset = (pin % (TOP_GPIO_PIN_IN_CR+1)) * 4;
    uint8_t crhl_value = (config << 2) | (mode);

    /* Check if the Configuration Register Low (CRL) or 
     * Configuration Register High (CRH) must be used. */
    if( pin > TOP_GPIO_PIN_IN_CR )
    {   // Use CRH
        DEVMAP->GPIOs[gpio_port].REGs.CRH &= ~(0xf << crhl_offset);
        DEVMAP->GPIOs[gpio_port].REGs.CRH |= (crhl_value << crhl_offset);
    }
    else
    {   // Use CRL
        DEVMAP->GPIOs[gpio_port].REGs.CRL &= ~(0xf << crhl_offset);
        DEVMAP->GPIOs[gpio_port].REGs.CRL |= (crhl_value << crhl_offset);
    }
}

void gpio_toggle(uint8_t gpio_port, GPIO_pin_number_t pin)
{
    uint32_t odr = DEVMAP->GPIOs[gpio_port].REGs.ODR;

    // Toggle the state of the pin. If the pin-bit of ODR is set, then
    // we need to write the high part of BSRR. In the other hand, if 
    // the pin-bit of ODR is not set, we need to write the low part of BSRR.
    DEVMAP->GPIOs[gpio_port].REGs.BSRR = ((odr & (1 << pin)) << GPIO_NUMBER) | \
                                         (~odr & (1 << pin));
}

void gpio_write(uint8_t gpio_port, GPIO_pin_number_t pin, GPIO_pin_state_t state)
{
    asm("NOP");
}
