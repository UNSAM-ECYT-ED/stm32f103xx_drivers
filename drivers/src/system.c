/*
 * Description: Functions to initialize common system stuff of the MCU.
 *
 * Author: Julian Rodriguez (jnrodriguezz@hotmail.com)
 * Date: Aug 2023
 *
 */

#include "stm32f103x8.h"

/*! Flash wait states that can be set. */
enum
{
    SYSTEM_FLASH_0_WAIT_STATES =    0,
    SYSTEM_FLASH_1_WAIT_STATES,
    SYSTEM_FLASH_2_WAIT_STATES,
    SYSTEM_FLASH_MAX_WAIT_STATES =  2
};

/*! AHB prescaler values that can be used. */
enum
{
    SYSTEM_AHB_PRESCALER_1 =    0,
    SYSTEM_AHB_PRESCALER_2 =    0b1000,
    SYSTEM_AHB_PRESCALER_4 =    0b1001,
    SYSTEM_AHB_PRESCALER_8 =    0b1010,
    SYSTEM_AHB_PRESCALER_16 =   0b1011,
    SYSTEM_AHB_PRESCALER_64 =   0b1100,
    SYSTEM_AHB_PRESCALER_128 =  0b1101,
    SYSTEM_AHB_PRESCALER_256 =  0b1110,
    SYSTEM_AHB_PRESCALER_512 =  0b1111,
    SYSTEM_AHB_PRESCALER_MAX =  0b1111
};

/*! APB1 prescaler values that can be used. */
enum
{
    SYSTEM_APB1_PRESCALER_1 =    0,
    SYSTEM_APB1_PRESCALER_2 =    0b100,
    SYSTEM_APB1_PRESCALER_4 =    0b101,
    SYSTEM_APB1_PRESCALER_8 =    0b110,
    SYSTEM_APB1_PRESCALER_16 =   0b111,
    SYSTEM_APB1_PRESCALER_MAX =  0b111
};

/*! HSE prescaler values that can be used. */
enum
{
    SYSTEM_HSE_PRESCALER_1 =    0,
    SYSTEM_HSE_PRESCALER_0P5,       /*! PLLXTPRE = 1 => divide by 2 the HSE. */
    SYSTEM_HSE_PRESCALER_MAX =  1
};

/*! SYSCLK source selection values. */
enum
{
    SYSTEM_SYSCLK_SOURCE_SEL_HSI = 0,   /*! Sel HSI as the source of the SYSCLK.*/
    SYSTEM_SYSCLK_SOURCE_SEL_HSE,       /*! Sel HSE as the source of the SYSCLK.*/
    SYSTEM_SYSCLK_SOURCE_SEL_PLL,       /*! Sel PLL as the source of the SYSCLK.*/
    SYSTEM_SYSCLK_SOURCE_SEL_MAX = 3,
};

/*! PLL prescaler values that can be used. */
enum
{
    SYSTEM_PLL_PRESCALER_2 =    0, 
    SYSTEM_PLL_PRESCALER_3 =    0b0001,       
    SYSTEM_PLL_PRESCALER_4 =    0b0010, 
    SYSTEM_PLL_PRESCALER_5 =    0b0011, 
    SYSTEM_PLL_PRESCALER_6 =    0b0100, 
    SYSTEM_PLL_PRESCALER_7 =    0b0101, 
    SYSTEM_PLL_PRESCALER_8 =    0b0110, 
    SYSTEM_PLL_PRESCALER_9 =    0b0111, 
    SYSTEM_PLL_PRESCALER_MAX =  0b0111,
};

/*-- Private functions definition --------------------------------------------*/

/**
 * Configure processor flash wait states.
 * The processor fetch instructions and gather data from a flash through
 * it's AHB bus. Often, the memory is way slower than the processor, so there
 * is a latency there. For this reason, the processor introduces some "wait
 * states" when is accessing to the memory. When the processor clock is faster
 * it will need more clock cycles until the memory prepares the data.
 * We can set the amount of "wait states" the processor do, the value set 
 * must follow the following rules:
 * 1) 0 wait states, if:                SYSCLK  <= 24 MHz
 * 2) 1 wait states, if:    24 MHz <    SYSCLK  <= 48 MHz
 * 3) 2 wait states, if:    48 MHz <    SYSCLK  <  72 MHz
 *
 * @param wait amount of wait states (see SYSTEM_FLASH_x_WAIT_STATES enum).
 */
static inline void system_config_flash_latency(uint8_t wait_states)
{
    DEVMAP->FLASH.REGs.ACR |= (wait_states << 0);
}

/**
 * Configure AHB clock prescaler.
 * Use the field HPRE of the register CFGR of the RCC to config AHB 
 * prescaler. 
 *
 * @param prescaler prescaler used, see the enum SYSTEM_AHB_PRESCALER_x.
 */
static inline void system_config_ahb_prescaler(uint8_t prescaler)
{
	DEVMAP->RCC.REGs.CFGR  |= (prescaler << 4);
}

/**
 * Configure APB1 clock prescaler.
 * Use the field PPRE1 of the register CFGR of the RCC to config APB1 
 * prescaler.
 *
 * @param prescaler prescaler used, see the enum SYSTEM_APB1_PRESCALER_x.
 */
static inline void system_config_apb1_prescaler(uint8_t prescaler)
{
	DEVMAP->RCC.REGs.CFGR  |= (prescaler << 8);
}

/**
 * Configure HSE clock prescaler.
 * Use the field PLLXTPRE of the register CFGR of the RCC to config HSE
 * prescaler.
 *
 * @param prescaler prescaler used, see the enum SYSTEM_HSE_PRESCALER_x.
 */
static inline void system_config_hse_prescaler(uint8_t prescaler)
{
	DEVMAP->RCC.REGs.CFGR  |= (prescaler << 17);
}

/**
 * Enable HSE and wait until it is ready.
 * Enable HSE using field HSEON of register CR. Then waits until it's oscillator
 * it is ready polling field HSERDY (bit 17) of CR.
 */
static inline void system_enable_hse(void)
{
	DEVMAP->RCC.REGs.CR |= (1 << 16);	        // Enable HSE
	while (!(DEVMAP->RCC.REGs.CR & (1 << 17))); // Wait for HSE is locked
}

/**
 * Configure STM32F103 PLL to multiply input freq by 9 and selecting as input
 * the HSE clock.
 * This function use the registers CR and CFGR of RCC.
 * @param prescaler prescaler used, see the enum SYSTEM_PLL_PRESCALER.
 */
static inline void system_config_pll(uint8_t prescaler)
{
	DEVMAP->RCC.REGs.CR    &= ~(1 << 24);		    // PLLON = Disable PLL
	DEVMAP->RCC.REGs.CFGR  |=  (prescaler << 18);   // PLLMUL (max 72 MHz)
	DEVMAP->RCC.REGs.CFGR  |=  (1 << 16);		    // PLLSRC = Select HSE as the PLL source clock
	DEVMAP->RCC.REGs.CR    |=  (1 << 24);		    // PLLON = Enable PLL
	while (!(DEVMAP->RCC.REGs.CR & (1 << 25)));	    // PLLRDY = Wait for PLL to lock
}

/**
 * Configure STM32F103 system clock (SYSCLK) source and wait until it is set 
 * by the hardware.
 * 
 * @param source the clock that will be the source of the SYSCLK, see 
 * SYSTEM_SYSCLK_SOURCE_SEL_x enum.
 */
static inline void system_select_sysclk_source(uint8_t source)
{
	DEVMAP->RCC.REGs.CFGR  |= (source << 0);
	while (!(DEVMAP->RCC.REGs.CFGR & (source << 2)));	// Wait for PLL clock to be selected
}

/*-- Public functions definition ---------------------------------------------*/
void system_init(void)
{
    system_config_flash_latency(SYSTEM_FLASH_2_WAIT_STATES);
    system_config_hse_prescaler(SYSTEM_HSE_PRESCALER_1); 
    system_config_ahb_prescaler(SYSTEM_AHB_PRESCALER_1);  
    system_config_apb1_prescaler(SYSTEM_APB1_PRESCALER_2);	
    system_enable_hse();
    system_config_pll(SYSTEM_PLL_PRESCALER_9);
    system_select_sysclk_source(SYSTEM_SYSCLK_SOURCE_SEL_PLL);
}
