#ifndef UART_RING_H
#define UART_RING_H

#include "stm32fxxx_hal.h"
#include "ring_buffer.h"

/* UART ring buffer structure */
typedef struct {

    UART_HandleTypeDef *huart;     // UART handle
    ring_buffer_t rx;              // RX ring buffer
    uint8_t rx_byte;               // Temporary received byte
    volatile uint32_t overflow_count; // Number of buffer overflows

} uart_ring_t;

/* Initialize UART ring buffer */
void uart_ring_init(uart_ring_t *u, UART_HandleTypeDef *huart,
                    uint8_t *storage, size_t capacity);

/* Start UART reception */
HAL_StatusTypeDef uart_ring_start(uart_ring_t *u);

/* Handle received UART data */
void uart_ring_rx_callback(uart_ring_t *u);

/* Read received data from the ring buffer */
size_t uart_ring_read(uart_ring_t *u, uint8_t *dst, size_t max_len);

#endif /* UART_RING_H */
