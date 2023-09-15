#include "stm32f103x8.h"
#include "system.h"
#include "gpio.h"

#define BLUEPILL_LED_GPIO_PORT  GPIOC
#define BLUEPILL_LED_GPIO_PIN   GPIO_PIN_13

#define CPU_CLOCK_MHZ           (72u)
#define CYCLES_PER_ITERATION    (7) 
#define LED_TOGGLE_PERIOD_US    (500000)

void __attribute__((optimize("O0"))) cpu_delay_us(uint32_t us)
{
    int i;
    int clock_cycles = ((CPU_CLOCK_MHZ * us) / CYCLES_PER_ITERATION);
    for(i = clock_cycles; i > 0; i--)
    {
        asm("NOP");
    }
}

int main(void)
{
    uint32_t odr;

    system_init();
    gpio_init();

    DEVMAP->GPIOs[BLUEPILL_LED_GPIO_PORT].REGs.CRH &= ~(0xf << 20); // clean
    DEVMAP->GPIOs[BLUEPILL_LED_GPIO_PORT].REGs.CRH |= (0x3 << 20);  // set
    
    while(1)
    {
        // Toggle the state of the pin. If the pin-bit of ODR is set, then
        // we need to write the high part of BSRR. In the other hand, if 
        // the pin-bit of ODR is not set, we need to write the low part of BSRR. 
        odr = DEVMAP->GPIOs[BLUEPILL_LED_GPIO_PORT].REGs.ODR;
        DEVMAP->GPIOs[BLUEPILL_LED_GPIO_PORT].REGs.BSRR = \
                ((odr   & (1 << BLUEPILL_LED_GPIO_PIN)) << 16) | \
                ((~odr  & (1 << BLUEPILL_LED_GPIO_PIN)) <<  0);

        cpu_delay_us(LED_TOGGLE_PERIOD_US);
    }

    return 0;
}
