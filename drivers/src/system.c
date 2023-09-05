/*
 * Description: Functions to initialize common system stuff of the MCU.
 *
 * Author: Julian Rodriguez (jnrodriguezz@hotmail.com)
 * Date: Aug 2023
 *
 */

#include "stm32f103x8.h"

/*-- Public functions definition ---------------------------------------------*/
void system_init(void)
{
	// PCLK code
	DEVMAP->RCC.REGs.CR    |= (1 << 16);			// Enable HSE
	while (!(DEVMAP->RCC.REGs.CR & (1 << 17)));		// Wait for HSE is locked

	DEVMAP->RCC.REGs.CR    &= ~(1 << 24);			// Disable PLL
	DEVMAP->RCC.REGs.CFGR  |= (0b0111 << 18);		// Set PLLMULL to 9. Set PLL output clock to 72 Mhz
	DEVMAP->RCC.REGs.CFGR  |=  (1 << 16);			// Select HSE as the PLL source clock
	DEVMAP->RCC.REGs.CR    |=  (1 << 24);			// Enable PLL
	while (!(DEVMAP->RCC.REGs.CR & (1 << 25)));		// Wait for PLL to lock

	DEVMAP->FLASH.REGs.ACR |= (0b010 << 0);			// Set FLASH WAIT STATE to 2
	DEVMAP->RCC.REGs.CFGR  |= (0b0000 << 4);		// Set AHB HPRE division to 1. Set AHB clock to 72 Mhz
	DEVMAP->RCC.REGs.CFGR  |= (0b100 << 8);			// Set APB1 PPRE1 division to 2. Set AHB clock to 36 Mhz
	DEVMAP->RCC.REGs.CFGR  |= (0b10 << 14);			// Set ADCPRE 72Mhz/6 = 12Mhz

	DEVMAP->RCC.REGs.CFGR  |= (0b10 << 0);			// Select PLL clock as the system clock
	while (!(DEVMAP->RCC.REGs.CFGR & (0b10 << 2)));	// Wait for PLL clock to be selected
}
