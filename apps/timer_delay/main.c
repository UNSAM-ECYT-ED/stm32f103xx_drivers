#include "stm32f103x8.h"
#include "system.h"
#include "gpio.h"

#define BLUEPILL_LED_GPIO_PORT  GPIOC
#define BLUEPILL_LED_GPIO_PIN   GPIO_PIN_13

#define LED_TOGGLE_PERIOD_MS    (10000)
#define LED_TOGGLE_PERIOD_US    (LED_TOGGLE_PERIOD_MS*1000)

static void config_timer(uint32_t ms_period)
{
    // Because we are using a prescaler of 2 in the APB1 bus,
    // the frequency of the timer is APB1_clk x 2
    uint32_t tim2_clk_freq_mhz = (system_get_apb1_clk_freq_hz() * 2)/1000000;

    /* Enable TIMER2 clock. */
    DEVMAP->RCC.REGs.APB1ENR |= 0x1;
    /* Set the prescaler of the TIMER to have a 1kHz frequency in it. */
    DEVMAP->TIMs[0].REGs.PSC = (tim2_clk_freq_mhz*1000)-1;
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

int main(void)
{
    uint32_t odr;

    system_init();
    gpio_init();
    config_timer(LED_TOGGLE_PERIOD_MS);

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

        timer_cpu_delay_us();
    }

    return 0;
}
