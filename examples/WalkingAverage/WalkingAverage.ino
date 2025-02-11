#include <Arduino.h>
#include "SimpleQueue.h"

// Define queue capacity
#define QUEUE_CAPACITY 10

// Queue buffer storage
float queueBuffer[QUEUE_CAPACITY];

// Create a SimpleQueue instance for float values
SimpleQueue queue(queueBuffer, sizeof(float), QUEUE_CAPACITY);

float runningSum = 0.0;  // Stores the running sum of elements

void setup() {
    Serial.begin(115200);
    queue.reset();  // Initialize the queue
}

void loop() {
    static float value = 1.0;  // Simulated new data input

    // Only subtract the oldest value when the queue is full (oldest gets replaced)
    if (queue.isFull()) {
        float *oldest = (float *)queue.peek(0);
        if (oldest != nullptr) {
            runningSum -= *oldest;
        }
    }

    // Push new value cyclically (overwrites oldest if full)
    queue.pushCyclic(&value);
    runningSum += value;  // Add new value to running sum

    // Compute and print the moving average
    if (!queue.isEmpty()) {
        float average = runningSum / queue.count();
        Serial.print("New Value: ");
        Serial.print(value);
        Serial.print(", Moving Average: ");
        Serial.println(average, 2);  // Print with 2 decimal places
    }

    value += 1.0;  // Simulate increasing input values
    delay(500);    // Simulate sampling delay
}
