/*
 * Description: Functions to initialize common system stuff of the MCU.
 *
 * Author: Julian Rodriguez (jnrodriguezz@hotmail.com)
 * Date: Aug 2023
 *
 */


/*-- Macros and constants ----------------------------------------------------*/

/*-- Public functions declaration --------------------------------------------*/
/**
 * Initialize STM32F103 clocks. 
 * Supposing a base HSE frequency f_hse, the final frequencies of the clocks are:
 * 1) SYSCLK = f_hse * 2
 * 2) AHB = f_hse * 1
 * 3) APB1 = f_hse * 2
 *
 * For example, in BluePill (which has an external oscillator of 8 MHz), the 
 * frequencies are:
 * 1) SYSCLK = 16 MHz
 * 2) AHB = 16 MHz
 * 3) APB1 = 16 MHz 
 */
void system_init(void);

/* Get SYSCLK clock frequency in Hz. */
uint32_t system_get_sysclk_clk_freq_hz(void);

/* Get AHB clock frequency in Hz. */
uint32_t system_get_ahb_clk_freq_hz(void);

/* Get APB1 clock frequency in Hz. */
uint32_t system_get_apb1_clk_freq_hz(void);
