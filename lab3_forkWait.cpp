// Process control system calls: The demonstration of FORK and WAIT system calls along
//  with zombie and orphan states. Implement the program in which the main program
//  accepts the integers to be sorted. Main program uses the FORK system call to create a
//  new process called a child process. Parent process sorts the integers using a sorting
//  algorithm and waits for the child process using WAIT system call to sort the integers
//  using any sorting algorithm. Also demonstrate zombie and orphan states


#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <algorithm>

using namespace std;

// Function for bubble sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function for selection sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

int main() {
    vector<int> arr;
    int n;

    // Input array size and elements
    cout << "Enter the number of integers: ";
    cin >> n;
    arr.resize(n);

    cout << "Enter the integers: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Fork a new process
    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed!\n";
        return 1;
    } else if (pid == 0) {
        // Child process
        cout << "\nChild Process Sorting using Selection Sort...\n";
        selectionSort(arr);
        cout << "Sorted array by Child: ";
        for (int num : arr) {
            cout << num << " ";
        }
        cout << endl;

        // Simulate an orphan state (parent dies)
        sleep(2);  // Let the parent exit first
        cout << "Child process exiting.\n";
    } else {
        // Parent process
        cout << "\nParent Process Sorting using Bubble Sort...\n";
        bubbleSort(arr);
        cout << "Sorted array by Parent: ";
        for (int num : arr) {
            cout << num << " ";
        }
        cout << endl;

        // Simulate zombie state
        wait(nullptr);  // Wait for child to finish
        cout << "Parent process exiting after child finishes.\n";
    }

    return 0;
}



/*

Zombie State:
A zombie process occurs when a child process completes execution but its termination status is not read by the parent (using wait()).
The terminated child process remains in the process table as a zombie.
In the code:
The parent uses wait(nullptr) to prevent the child from becoming a zombie.


Orphan State:
An orphan process occurs when a parent process terminates while its child process is still running.
The orphaned child process is adopted by the init (PID 1) process in UNIX-based systems.
In the code:
The child process sleeps (sleep(2)) to simulate the parent process terminating first, creating an orphan state.


*/