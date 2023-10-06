/*
 * Description: Memory map and peripherals of STM32F103x8 MCUs. Also, we have
 * the IVT here.
 *
 * Author: Julian Rodriguez (jnrodriguezz@hotmail.com)
 * Date: Aug 2023
 *
 */

#include "stm32f103x8.h"

/*-- Private functions definition --------------------------------------------*/
__attribute__((weak)) void handler_systick(void)
{
    asm("NOP");
}

__attribute__((weak)) void handler_adc1_2(void)
{
     asm("NOP");   
}

__attribute__((weak)) void handler_usart1(void)
{
    asm("NOP");
}

__attribute__((weak)) int main(void)
{
    asm("NOP");
    return 0;
}

/*-- Public variables declaration --------------------------------------------*/
volatile _CTX * const CTX = ((_CTX *) 0xE0000000);
volatile _DEVMAP * const DEVMAP = ((_DEVMAP *) 0x40000000);

/*! MCU Interrupt Vector Table. */
const interrupt_t vector_table[] __attribute__ ((section(".vtab"))) = {
	STACKINIT,												// 0x0000_0000 Stack Pointer
	(interrupt_t) main,										// 0x0000_0004 Reset
	0,														// 0x0000_0008
	0,														// 0x0000_000C
	0,														// 0x0000_0010
	0,														// 0x0000_0014
	0,														// 0x0000_0018
	0,														// 0x0000_001C
	0,														// 0x0000_0020
	0,														// 0x0000_0024
	0,														// 0x0000_0028
	0,														// 0x0000_002C
	0,														// 0x0000_0030
	0,														// 0x0000_0034
	0,														// 0x0000_0038
	handler_systick,										// 0x0000_003C SYSTICK
	0,														// 0x0000_0040
	0,														// 0x0000_0044
	0,														// 0x0000_0048
	0,														// 0x0000_004C
	0,														// 0x0000_0050
	0,														// 0x0000_0054
	0,														// 0x0000_0058
	0,														// 0x0000_005C
	0,														// 0x0000_0060
	0,														// 0x0000_0064
	0,														// 0x0000_0068
	0,														// 0x0000_006C
	0,														// 0x0000_0070
	0,														// 0x0000_0074
	0,														// 0x0000_0078
	0,														// 0x0000_007C
	0,														// 0x0000_0080
	0,														// 0x0000_0084
	handler_adc1_2,											// 0x0000_0088
	0,														// 0x0000_008C
	0,														// 0x0000_0090
	0,														// 0x0000_0094
	0,														// 0x0000_0098
	0,														// 0x0000_009C
	0,														// 0x0000_00A0
	0,														// 0x0000_00A4
	0,														// 0x0000_00A8
	0,														// 0x0000_00AC
	0,														// 0x0000_00B0 TIM2
	0,														// 0x0000_00B4
	0,														// 0x0000_00B8
	0,														// 0x0000_00BC
	0,														// 0x0000_00C0
	0,														// 0x0000_00C4
	0,														// 0x0000_00C8
	0,														// 0x0000_00CC
	0,														// 0x0000_00D0
	handler_usart1,											// 0x0000_00D4 USART1
	0,														// 0x0000_00D8
	0,														// 0x0000_00DC
};


