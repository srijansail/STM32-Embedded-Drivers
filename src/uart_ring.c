C
#include "uart_ring.h"
 
// Initialize UART ring buffer structure
void uart_ring_init(uart_ring_t *u, UART_HandleTypeDef *huart,
uint8_t *storage, size_t capacity)
{
u->huart = huart; // UART handle
u->rx_byte = 0; // Temporary receive byte
u->overflow_count = 0; // Reset overflow counter
 
rb_init(&u->rx, storage, capacity); // Initialize ring buffer
}
 
// Start UART interrupt reception
HAL_StatusTypeDef uart_ring_start(uart_ring_t *u)
{
// Receive 1 byte using interrupt mode
return HAL_UART_Receive_IT(u->huart, &u->rx_byte, 1);
}
 
// Called when a UART byte is received
void uart_ring_rx_callback(uart_ring_t *u)
{
// Store received byte in ring buffer
if (!rb_push(&u->rx, u->rx_byte))
u->overflow_count++; // Buffer full, count overflow
 
// Start receiving the next byte
(void)HAL_UART_Receive_IT(u->huart, &u->rx_byte, 1);
}
 
// Read data from the ring buffer
size_t uart_ring_read(uart_ring_t *u, uint8_t *dst, size_t max_len)
{
size_t n = 0;
 
// Copy bytes from ring buffer to destination
while (n < max_len && rb_pop(&u->rx, &dst[n]))
n++;
 
return n; // Number of bytes read
}
