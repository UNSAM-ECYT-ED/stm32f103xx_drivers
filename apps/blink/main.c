#include "stm32f103x8.h"
#include "system.h"
#include "gpio.h"

#define BLUEPILL_LED_GPIO_PORT  GPIOC
#define BLUEPILL_LED_GPIO_PIN   GPIO_PIN_13

#define CPU_CLOCK_MHZ           (72u)
#define LED_TOGGLE_PERIOD_US    (5000000)

void cpu_delay_us(uint32_t us)
{
    int i;
    int clock_cycles = (CPU_CLOCK_MHZ * us);

    for(i = 0; i < clock_cycles; i++)
    {
        asm("NOP");
    }
}

int main(void)
{
    system_init();
    gpio_init();
    
    gpio_config_output(
            BLUEPILL_LED_GPIO_PORT, BLUEPILL_LED_GPIO_PIN,
            GPIO_PIN_CNF_OUTPUT_PP, GPIO_PIN_MODE_OUTPUT_10MHZ);

    // turn on LED on BluePill
    gpio_write(BLUEPILL_LED_GPIO_PORT, 
            BLUEPILL_LED_GPIO_PIN, GPIO_PIN_RESET);

    gpio_toggle(BLUEPILL_LED_GPIO_PORT, BLUEPILL_LED_GPIO_PIN);
    gpio_toggle(BLUEPILL_LED_GPIO_PORT, BLUEPILL_LED_GPIO_PIN);
 
    while(1)
    {
        gpio_toggle(BLUEPILL_LED_GPIO_PORT, BLUEPILL_LED_GPIO_PIN);
        cpu_delay_us(LED_TOGGLE_PERIOD_US);
    }

    return 0;
}
