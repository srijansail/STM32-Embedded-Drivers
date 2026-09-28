#include "ring_buffer.h"
 
// Initialize the ring buffer
void rb_init(ring_buffer_t *rb, uint8_t *storage, size_t capacity) {
rb->buf = storage; // Buffer memory
rb->cap = capacity; // Buffer size
rb->head = 0; // Write position
rb->tail = 0; // Read position
}
 
// Add a byte to the buffer
bool rb_push(ring_buffer_t *rb, uint8_t value) {
size_t next = (rb->head + 1U) % rb->cap; // Next write position
 
if (next == rb->tail) // Buffer is full
return false;
 
rb->buf[rb->head] = value; // Store data
rb->head = next; // Move write position
 
return true;
}
 
// Remove a byte from the buffer
bool rb_pop(ring_buffer_t *rb, uint8_t *value) {
if (rb->head == rb->tail) // Buffer is empty
return false;
 
*value = rb->buf[rb->tail]; // Read data
rb->tail = (rb->tail + 1U) % rb->cap; // Move read position
 
return true;
}
 
// Return number of bytes currently in the buffer
size_t rb_available(const ring_buffer_t *rb) {
return (rb->head >= rb->tail)
? (rb->head - rb->tail) // No wrap-around
: (rb->cap - rb->tail + rb->head); // Wrap-around
}
