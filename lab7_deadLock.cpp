// Write a program to check whether a given system is in safe state or not using Banker’s
//  Deadlock Avoidance algorithm


#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>> &allocation, vector<vector<int>> &max, vector<int> &available, int p, int r) {
    // Calculate the Need matrix
    vector<vector<int>> need(p, vector<int>(r));
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < r; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Mark all processes as unfinished initially
    vector<bool> finish(p, false);
    vector<int> safeSequence;

    // Copy the available vector to work
    vector<int> work = available;

    for (int count = 0; count < p; ++count) {
        // Find a process whose needs can be satisfied
        for (int i = 0; i < p; ++i) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < r; ++j) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                // If the process can be satisfied
                if (canAllocate) {
                    for (int j = 0; j < r; ++j) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence.push_back(i);
                    finish[i] = true;
                }
            }
        }
    }

    for(int j=0; j<p; ++j){
        if (!finish[j]) {
            cout << "System is in an unsafe state. Deadlock may occur." << endl;
            return false;            
        }
    }

    // If all processes are finished, the system is in a safe state
    cout << "The system is in a safe state.\nSafe sequence: ";
    for (int i = 0; i < safeSequence.size(); ++i) {
        cout << "P" << safeSequence[i];
        if (i != safeSequence.size() - 1) cout << " -> ";
    }
    cout << endl;
    return true;
}

int main() {
    int numProcesses, numResources;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    cout << "Enter the number of resource types: ";
    cin >> numResources;

    vector<vector<int>> allocation(numProcesses, vector<int>(numResources));
    vector<vector<int>> max(numProcesses, vector<int>(numResources));
    vector<int> available(numResources);

    cout << "Enter the allocation matrix (current resource allocation for each process):" << endl;
    for (int i = 0; i < numProcesses; ++i) {
        for (int j = 0; j < numResources; ++j) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter the max matrix (maximum resource requirement for each process):" << endl;
    for (int i = 0; i < numProcesses; ++i) {
        for (int j = 0; j < numResources; ++j) {
            cin >> max[i][j];
        }
    }

    cout << "Enter the available resources (initial resources available in the system):" << endl;
    for (int i = 0; i < numResources; ++i) {
        cin >> available[i];
    }

    // Check if the system is in a safe state
    isSafe(allocation, max, available, numProcesses, numResources);

    return 0;
}



/*

Enter the number of processes: 5
Enter the number of resource types: 3
Enter the allocation matrix:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
Enter the max matrix:
7 5 3
3 2 2
9 0 2
4 2 2
5 3 3
Enter the available resources:
3 3 2


The system is in a safe state.
Safe sequence: P1 -> P3 -> P4 -> P0 -> P2


*/


/*

Safe state: System has enough resources and an execution order to avoid deadlock.
Unsafe state: Resources are not sufficient to guarantee completion for all processes, risking deadlock.
Deadlock: Processes are permanently stuck, and no progress is possible.

*/