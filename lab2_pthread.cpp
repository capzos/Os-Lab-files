//  Write a Program to implement multithreading for Matrix Operations using Pthreads


#include <iostream>
#include <thread>
#include <vector>

using namespace std;

// Matrix size
const int SIZE = 3;

// Matrices
int matrixA[SIZE][SIZE];
int matrixB[SIZE][SIZE];
int result[SIZE][SIZE] = {0};

// Function to multiply a row of matrixA with all columns of matrixB
void multiplyRow(int row) {
    for (int col = 0; col < SIZE; ++col) {
        for (int k = 0; k < SIZE; ++k) {
            result[row][col] += matrixA[row][k] * matrixB[k][col];
        }
    }
}

int main() {
    // Input matrices
    cout << "Enter elements of Matrix A (" << SIZE << "x" << SIZE << "):\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cin >> matrixA[i][j];
        }
    }

    cout << "Enter elements of Matrix B (" << SIZE << "x" << SIZE << "):\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cin >> matrixB[i][j];
        }
    }

    // Create threads to compute each row of the result matrix
    vector<thread> threads;
    for (int i = 0; i < SIZE; ++i) {
        threads.push_back(thread(multiplyRow, i));
    }

    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }

    // Print the result matrix
    cout << "Resultant Matrix:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}




/*

Multithreading:
Each thread works on a single row of the resultant matrix, reducing overall computation time for large matrices.

Thread Safety:
Each thread writes only to its assigned row (result[row][col]), so there's no conflict or data race.

*/