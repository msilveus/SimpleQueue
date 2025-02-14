// SimpleQueue.h
#ifndef SIMPLE_QUEUE_H
#define SIMPLE_QUEUE_H

#include <Arduino.h>

class SimpleQueue {
public:
    SimpleQueue(volatile void *buffer, size_t element_size, size_t capacity);
    void reset();
    size_t count() const;
    bool isEmpty() const;
    bool isFull() const;
    bool push(const void *element);
    bool pushCyclic(const void *element);
    bool pop(void *element);
    void *peek(size_t index) const;

private:
    volatile int head;
    volatile int tail;
    volatile size_t size;
    size_t capacity;
    volatile void *queue;
    size_t element_size;
};

#endif /* SIMPLE_QUEUE_H */
