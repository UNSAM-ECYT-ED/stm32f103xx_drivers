/*
 * Description: Functions to config and use the systick of Cortex-M processor.
 *
 * Author: Julian Rodriguez (jnrodriguezz@hotmail.com)
 * Date: Sep 2023
 *
 */

#include <stdbool.h>

/*-- Public functions declaration --------------------------------------------*/
/**
 * Configure systick reload frequency using the external clock and enable
 * the interrupt.
 * Cortex-M3's Systick can use the processor clock or an external reference clock.
 * In STM32F10xx:
 * 1) the external clock is the AHB bus clock divided by 8.
 * 2) the processor clock is the AHB bus clock.
 *
 * If the reload value of the systick is 1, then, it will trigger the interrupt
 * 
 *
 * For more information read: "STM32F10xx Cortex-M3 programming manual".
 *
 * @param[in] interrupt_hz the desired frequency of the systick interrupt in Hz.
 * 
 * @param[in] use_external_clock set to true if you want to use the external 
 * clock or if you want to use the processor clock, This function will do the 
 * math for both cases.
 */
void systick_config_interrupt(uint32_t interrupt_hz, bool use_external_clock);

/**
 * Enable systick interrupt.
 */
void systick_enable_interrupt(void);

/**
 * Enable systick counter.
 */
void systick_enable_count(void);
