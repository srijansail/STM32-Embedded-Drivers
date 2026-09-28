#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>     // size_t
#include <stdint.h>     // uint8_t
#include <stdbool.h>    // bool, true, false

/* Ring buffer structure */
typedef struct {
    uint8_t *buf;           // Buffer storage
    size_t cap;             // Buffer capacity
    volatile size_t head;   // Write position
    volatile size_t tail;   // Read position
} ring_buffer_t;

/* Initialize the ring buffer */
void rb_init(ring_buffer_t *rb, uint8_t *storage, size_t capacity);

/* Add a byte to the buffer */
bool rb_push(ring_buffer_t *rb, uint8_t value);

/* Remove a byte from the buffer */
bool rb_pop(ring_buffer_t *rb, uint8_t *value);

/* Return the number of available bytes */
size_t rb_available(const ring_buffer_t *rb);

#endif /* RING_BUFFER_H */
