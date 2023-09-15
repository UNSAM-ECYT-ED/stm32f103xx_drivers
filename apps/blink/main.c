#include "stm32f103x8.h"
#include "system.h"
#include "gpio.h"

#define USE_TIMER_DELAY

#define BLUEPILL_LED_GPIO_PORT  GPIOC
#define BLUEPILL_LED_GPIO_PIN   GPIO_PIN_13

#define CPU_CLOCK_MHZ           (72u)
#define APB1_CLOCK_MHZ          (36u)
#define CYCLES_PER_ITERATION    (22u) 
#define LED_TOGGLE_PERIOD_MS    (500)
#define LED_TOGGLE_PERIOD_US    (LED_TOGGLE_PERIOD_MS*1000)

#ifdef USE_TIMER_DELAY
static void config_timer(uint32_t ms_period)
{
    /* Enable TIMER2 clock. */
    DEVMAP->RCC.REGs.APB1ENR |= 0x1;
    /* Set the prescaler of the TIMER to have a 1kHz frequency in it. */
    DEVMAP->TIMs[0].REGs.PSC = (APB1_CLOCK_MHZ*1000)-1;
    /* Set the auto-reload value to achieve the desired delay. 
     * Note: Remember that this value must be 16-bits wide. */
    DEVMAP->TIMs[0].REGs.ARR = ms_period -1;
    /* Set one-pulse mode. */
    DEVMAP->TIMs[0].REGs.CR1 |= (1 << 3);
    /* Re-initialize the counter and generate and update of the registers. */
    DEVMAP->TIMs[0].REGs.EGR |= 0x1; 
    /* Disable the timer counter. */
    DEVMAP->TIMs[0].REGs.CR1 &= ~(0x1);
}

static void timer_cpu_delay_us(void)
{   
    /* Enable the timer counter. */
    DEVMAP->TIMs[0].REGs.CR1 |= 0x1;
    /* Wait until timer ends checking UIF field in SR. */
    while( !(DEVMAP->TIMs[0].REGs.SR & 0x1) ) {};
    /* Clear update flag. */
    DEVMAP->TIMs[0].REGs.SR &= ~(0x1);    
}
#else
static void __attribute__((optimize("O0"))) busy_loop_cpu_delay_us(uint32_t us)
{
    int clock_cycles = ((CPU_CLOCK_MHZ * us) / CYCLES_PER_ITERATION);
    int i;
    for(i = clock_cycles; i > 0; i--)
    {
        asm("NOP");
    }
}
#endif

int main(void)
{
    uint32_t odr;

    system_init();
    gpio_init();

#ifdef USE_TIMER_DELAY
    config_timer(LED_TOGGLE_PERIOD_MS);
#endif

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

#ifdef USE_TIMER_DELAY
        timer_cpu_delay_us();
#else
        busy_loop_cpu_delay_us(LED_TOGGLE_PERIOD_US);
#endif
    }

    return 0;
}
