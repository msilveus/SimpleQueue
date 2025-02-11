#include <SimpleQueue.h>

#define QUEUE_CAPACITY 5
int queueBuffer[QUEUE_CAPACITY];
SimpleQueue myQueue(queueBuffer, sizeof(int), QUEUE_CAPACITY);

void setup() {
    Serial.begin(115200);
    myQueue.reset();
    
    int value = 10;
    Serial.println("Pushing values:");
    for (int i = 0; i < QUEUE_CAPACITY; i++) {
        if (myQueue.push(&value)) {
            Serial.print("Pushed: ");
            Serial.println(value);
        }
        value += 10;
    }
    
    Serial.println("\nPopping values:");
    while (!myQueue.isEmpty()) {
        int poppedValue;
        myQueue.pop(&poppedValue);
        Serial.print("Popped: ");
        Serial.println(poppedValue);
    }
}

void loop() {
    // Do nothing
}
