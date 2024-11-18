// Implementation of Classical Process Synchronization problems using mutex. Application
//  to demonstrate: Reader - Writer problem.


#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

// Shared variables
int shared_data = 0;   // Simulates a shared resource (e.g., database)
int reader_count = 0;  // Number of readers currently accessing the resource

// Mutexes for synchronization
mutex resource_mutex;      // Protects the shared resource
mutex reader_count_mutex;  // Protects the reader_count variable

// Reader function
void reader(int id, int num_operations) {
    for (int i = 0; i < num_operations; ++i) {
        // Lock reader_count_mutex to update reader_count
        reader_count_mutex.lock();
        reader_count++;
        if (reader_count == 1) {
            // If this is the first reader, lock the resource
            resource_mutex.lock();
        }
        reader_count_mutex.unlock();

        // Simulate reading
        cout << "Reader " << id << " is reading the shared data: " << shared_data << endl;
        this_thread::sleep_for(chrono::milliseconds(300)); // Simulate some work

        // Unlock reader_count_mutex to update reader_count
        reader_count_mutex.lock();
        reader_count--;
        if (reader_count == 0) {
            // If this is the last reader, unlock the resource
            resource_mutex.unlock();
        }
        reader_count_mutex.unlock();

        // Simulate a delay before the reader reads again
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

// Writer function
void writer(int id, int num_operations) {
    for (int i = 0; i < num_operations; ++i) {
        // Lock the resource for exclusive access
        resource_mutex.lock();

        // Simulate writing
        shared_data++;
        cout << "Writer " << id << " is writing to the shared data: " << shared_data << endl;
        this_thread::sleep_for(chrono::milliseconds(150)); // Simulate some work

        // Unlock the resource
        resource_mutex.unlock();

        // Simulate a delay before the writer writes again
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int main() {
    // Number of readers, writers, and operations per thread
    int num_readers = 3, num_writers = 2;
    int num_operations = 5; // Number of operations per reader/writer

    // Create reader and writer threads
    vector<thread> readers, writers;

    for (int i = 1; i <= num_readers; ++i) {
        readers.push_back(thread(reader, i, num_operations));
    }
    for (int i = 1; i <= num_writers; ++i) {
        writers.push_back(thread(writer, i, num_operations));
    }

    // Join all threads
    for (auto& t : readers) {
        t.join();
    }
    for (auto& t : writers) {
        t.join();
    }

    cout << "\n\nAll readers and writers have finished their operations." << endl;

    return 0;
}


// This program demonstrates the Reader-Writer Problem using mutex to synchronize access to a 
// shared resource (shared_data). The objective is to allow multiple readers to access the resource 
// simultaneously while ensuring writers get exclusive access.

