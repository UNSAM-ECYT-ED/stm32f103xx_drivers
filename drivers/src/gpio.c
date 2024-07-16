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

/*-- Public functions definition ---------------------------------------------*/
void gpio_init(void)
{
    DEVMAP->RCC.REGs.APB2ENR |= 0x3E; // enable all GPIOs clock
}

void gpio_config_output(uint8_t gpio_port, GPIO_pin_number_t pin, 
        GPIO_pin_cnf_t config, GPIO_pin_mode_t mode)
{
    // Note: Students must implement this
    asm("NOP");
}

void gpio_toggle(uint8_t gpio_port, GPIO_pin_number_t pin)
{
    // Note: Students must implement this
    asm("NOP");
}

void gpio_write(uint8_t gpio_port, GPIO_pin_number_t pin, GPIO_pin_state_t state)
{
    // Note: Students must implement this
    asm("NOP");
}
