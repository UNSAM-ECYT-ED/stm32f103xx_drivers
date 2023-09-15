/*
 * Description: Functions to initialize common system stuff of the MCU.
 *
 * Author: Julian Rodriguez (jnrodriguezz@hotmail.com)
 * Date: Aug 2023
 *
 */


/*-- Public functions declaration --------------------------------------------*/
/**
 * Initialize STM32F103 clocks. 
 * Supposing a base HSE frequency f_hse, the final frequencies of the clocks are:
 * 1) SYSCLK = f_hse * 9
 * 2) AHB = f_hse * 9 
 * 3) APB1 = f_hse * 4.5
 *
 * For example, in BluePill (which has an external oscillator of 8 MHz), the 
 * frequencies are:
 * 1) SYSCLK = 72 MHz (max frequency that can run the processor)
 * 2) AHB = 72 MHz
 * 3) APB1 = 36 MHz 
 */
void system_init(void);
