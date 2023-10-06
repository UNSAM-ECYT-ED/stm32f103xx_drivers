/*
 * Description: Functions to use the uart of the MCU.
 *
 * Author: Julian Rodriguez (jnrodriguezz@hotmail.com)
 * Date: Sep 2023
 *
 */

#include <stdint.h>

/*-- Public variable type declaration ----------------------------------------*/
typedef enum
{
    UART_BAUDRATE_9600 =    9600,
    UART_BAUDRATE_19200 =   19200, 
    UART_BAUDRATE_38400 =   38400,
    UART_BAUDRATE_115200 =  115200,
    UART_BAUDRATE_MAX = UART_BAUDRATE_115200
} uart_baudrate_t;

/*-- Public functions declaration --------------------------------------------*/
/**
 * Initialize UART configuring the baudrate and enabling it using it's CR1 
 * register.
 *
 * @param[in] baudrate the baudrate of the UART. See uart_baudrate_t to see
 * the allowed baudrates.
 */
void uart_init(uart_baudrate_t baudrate);

/**
 * Send a packet of "len" bytes contained in "tx_buff through the UART in a 
 * blocking fashion. This function will block until all the frame is sent.
 *
 * @param[in] tx_buff buffer where is contained the message to send.
 * 
 * @param[in] len quantity of bytes to send.
 */
void uart_tx_blocking(char *tx_buff, uint32_t len);

/**
 * Receive a packet of "len" bytes and store them in "rx_buff" in a blocking
 * fashion. This function will block until len bytes are received.
 *
 * @param[in] rx_buff buffer where will be stored the received bytes.
 * 
 * @param[in] len quantity of bytes to receive.
 */
void uart_rx_blocking(char *rx_buff, uint32_t len);

/**
 * Enable UART TX interrupt using TXEIE field of CR1 register.
 */
void uart_enable_tx_interrupt(void);

/**
 * Disable UART TX interrupt using TXEIE field of CR1 register.
 */
void uart_disable_tx_interrupt(void);

/**
 * Enable UART RX interrupt using RXNEIE field of CR1 register.
 */
void uart_enable_rx_interrupt(void);
