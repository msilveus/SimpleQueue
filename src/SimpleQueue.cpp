// SimpleQueue.cpp
#include "SimpleQueue.h"

SimpleQueue::SimpleQueue(volatile void *buffer, size_t element_size, size_t capacity)
    : head(-1), tail(-1), size(0), capacity(capacity), queue(buffer), element_size(element_size) {}

void SimpleQueue::reset() {
    head = -1;
    tail = -1;
    size = 0;
}

size_t SimpleQueue::count() const {
    return size;
}

bool SimpleQueue::isEmpty() const {
    return size == 0;
}

bool SimpleQueue::isFull() const {
    return size == capacity;
}

bool SimpleQueue::push(const void *element) {
    if (isFull()) return false;
    
    noInterrupts();  // Disable interrupts
    tail = (tail + 1) % capacity;
    if (head == -1) head = 0;
    void *dest = (char *)queue + (tail * element_size);
    memcpy(dest, element, element_size);
    size++;
    interrupts();  // Enable interrupts

    return true;
}

bool SimpleQueue::pushCyclic(const void *element) {
    if (isFull()) {
        // Overwrite the oldest element
        head = (head + 1) % capacity;
    } else if (head == -1) {
        // First element case
        head = 0;
    }

    // Standard push operation
    noInterrupts();  // Disable interrupts
    tail = (tail + 1) % capacity;
    void *dest = (char *)queue + (tail * element_size);
    memcpy(dest, element, element_size);
    
    if (!isFull()) size++;  // Only increase size if not overwriting
    interrupts();  // Enable interrupts

    return true;
}

bool SimpleQueue::pop(void *element) {
    if (isEmpty()) return false;

    noInterrupts();  // Disable interrupts
    void *src = (char *)queue + (head * element_size);
    memcpy(element, src, element_size);
    head = (head + 1) % capacity;
    size--;
    if (size == 0) {
        head = -1;
        tail = -1;
    }
    interrupts();  // Enable interrupts

    return true;
}

void *SimpleQueue::peek(size_t index) const {
    if (index >= size) {
        return NULL;
    }
    size_t pos = (head + index) % capacity;
    return (char *)queue + (pos * element_size);
}
