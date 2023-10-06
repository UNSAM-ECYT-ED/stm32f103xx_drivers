/*
 * Description: Functions to use the GPIOS of the MCU.
 *
 * Author: Julian Rodriguez (jnrodriguezz@hotmail.com)
 * Date: Aug 2023
 *
 */

#include <stdint.h>

/*-- Public variable type declaration ----------------------------------------*/
typedef enum
{
    GPIO_PIN_0   = 0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15,
    GPIO_PIN_MAX 
} GPIO_pin_number_t;

typedef enum
{
    GPIO_PIN_RESET  = 0u,
    GPIO_PIN_SET    = 1u
} GPIO_pin_state_t;

typedef enum
{
    /* When MODE[1:0] == 0 */
    ANALOG_PIN_CNF_INPUT =      0u, /*! Analog mode. */
    FLOATING_PIN_CNF_INPUT  =   1u, /*! Floating input. */
    GPIO_PIN_CNF_INPUT_PULL =   2u, /*! Input with pull-up/pull-down. */
    
    /* When MODE[1:0] > 0 */
    GPIO_PIN_CNF_OUTPUT_PP =    0u, /*! Output Push-pull. */
    GPIO_PIN_CNF_OUTPUT_OD =    1u, /*! Output Open-drain. */
    AFIO_PIN_CNF_OUTPUT_PP =    2u, /*! Alternate function output push-pull. */
    AFIO_PIN_CNF_OUTPUT_OD =    3u, /*! Alternate function output open-drain. */
} GPIO_pin_cnf_t;

typedef enum
{
    GPIO_PIN_MODE_INPUT =           0u,
    GPIO_PIN_MODE_OUTPUT_10MHZ =    1u,
    GPIO_PIN_MODE_OUTPUT_2MHZ =     2u,
    GPIO_PIN_MODE_OUTPUT_50MHZ =    3u,
} GPIO_pin_mode_t;

/*-- Public functions declaration --------------------------------------------*/
void gpio_init(void);
void gpio_config_output(uint8_t gpio_port, GPIO_pin_number_t pin, 
        GPIO_pin_cnf_t config, GPIO_pin_mode_t mode);
void gpio_toggle(uint8_t gpio_port, GPIO_pin_number_t pin);
void gpio_write(uint8_t gpio_port, GPIO_pin_number_t pin, GPIO_pin_state_t state);
