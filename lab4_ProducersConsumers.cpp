//  Implementation of Classical Process Synchronization problems using Threads and
//  Semaphore, Mutex. Application to demonstrate: producer - consumer problem.


#include<iostream>
#include<thread>
#include<mutex>
#include<queue>
#include<chrono>
#include<semaphore.h>
using namespace std;

// Define the buffer size and other variables
const int buffer_size = 5;  // Maximum size of the buffer
int totalItems = 10;        // Total number of items to be produced
int pCount = 0;             // Counter for items produced
int cCount = 0;             // Counter for items consumed

queue<int> buffer;          // Shared buffer for producer-consumer
sem_t emptySlots;           // Semaphore to track empty slots in the buffer
sem_t filledSlots;          // Semaphore to track filled slots in the buffer

mutex mtx;                  // Mutex to synchronize access to the buffer

// Producer function
void producer(int id) {
    while (1) {
        this_thread::sleep_for(chrono::milliseconds(500));  // Simulate production delay

        if (pCount >= totalItems) break;  // Exit if all items are produced
        pCount++;  // Increment production count

        sem_wait(&emptySlots);  // Wait for an empty slot in the buffer
        {
            lock_guard<mutex> lock(mtx);  // Lock the buffer to ensure mutual exclusion
            buffer.push(pCount);  // Add the produced item to the buffer
            cout << "Producer " << id << " produced item " << pCount << endl;
        }
        sem_post(&filledSlots);  // Signal that a filled slot is available
    }
}

// Consumer function
void consumer(int id) {
    int item;
    while (1) {
        if (cCount >= totalItems) break;  // Exit if all items are consumed
        cCount++;  // Increment consumption count

        sem_wait(&filledSlots);  // Wait for a filled slot in the buffer
        {
            lock_guard<mutex> lock(mtx);  // Lock the buffer to ensure mutual exclusion
            item = buffer.front();  // Retrieve the item from the buffer
            buffer.pop();           // Remove the item from the buffer
            cout << "Consumer " << id << " consumed item " << item << endl;
        }
        sem_post(&emptySlots);  // Signal that an empty slot is available

        this_thread::sleep_for(chrono::milliseconds(1000));  // Simulate consumption delay
    }
}

int main() {
    // Initialize semaphores
    sem_init(&emptySlots, 0, buffer_size);  // Start with all slots empty
    sem_init(&filledSlots, 0, 0);           // Start with no slots filled

    // Create producer and consumer threads
    thread prod1(producer, 1);
    thread prod2(producer, 2);
    thread cons1(consumer, 1);
    thread cons2(consumer, 2);

    // Wait for threads to complete execution
    prod1.join();
    prod2.join();
    cons1.join();
    cons2.join();

    return 0;
}


// Mutex (Mutual Exclusion)
// A mutex is a synchronization primitive used to prevent multiple threads from accessing a shared resource simultaneously.
// Only one thread can lock the mutex at a time; other threads must wait until it is unlocked.
// Ensures mutual exclusion, avoiding data corruption or race conditions.

// Semaphore
// A semaphore is a signaling mechanism that controls access to a shared resource.
// It maintains a counter:
// Increment (sem_post) when a resource is released.
// Decrement (sem_wait) when a resource is acquired.
// Types:
// Binary semaphore: Acts like a mutex (0 or 1 value).
// Counting semaphore: Tracks multiple resources.
// Used for resource management and synchronization.

// Thread
// A thread is the smallest unit of execution within a process.
// Threads within the same process share resources like memory, but each has its own execution context.
// Multithreading allows multiple threads to execute concurrently, improving performance in applications that perform multiple tasks simultaneously.