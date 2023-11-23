/*
 * Description: Functions to use the ADC of the MCU.
 *
 * Author: Julian Rodriguez (jnrodriguezz@hotmail.com)
 * Date: Nov 2023
 *
 */

#include <stdint.h>

/*-- Public variable type declaration ----------------------------------------*/
typedef enum
{
    ADCPRE_2 =  0x0,
    ADCPRE_4 =  0x1,
    ADCPRE_6 =  0x2,
    ADCPRE_8 =  0x3
} adc_prescaler_t; 

/*-- Public functions declaration --------------------------------------------*/
/**
 * Initialize a given ADC with right-alignment and calibrate it.
 * By default, the ADC is configured in continous conversion mode.
 *
 * @param[in] adc_num set to 0 to config ADC1 or set to 1 to config ADC2.
 *
 * @param[in] prescaler the prescaler to divide the APB clock.
 */
void adc_init(uint8_t adc_num, adc_prescaler_t prescaler);

/**
 * Read ADC counts from data register.
 *
 * @param[in] adc_num set to 0 to config ADC1 or set to 1 to config ADC2.
 */
uint16_t adc_read_count(uint8_t adc_num);
