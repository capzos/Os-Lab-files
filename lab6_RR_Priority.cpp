#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct proccess {
    int at;   // Arrival Time
    int bt;   // Burst Time
    int ft;   // Finish Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
    int pr;   // Priority (Higher value means higher priority)
    int remainingBT; // Remaining Burst Time (for preemptive scheduling)
};

void printResults(vector<proccess>& processes) {
    cout << "\nAT\tBT\tPR\tFT\tTAT\tWT\n";
    for (auto& p : processes) {
        cout << p.at << "\t" << p.bt << "\t" << p.pr << "\t" << p.ft << "\t" << p.tat << "\t" << p.wt << "\n";
    }
}

// Priority Scheduling (Non-Preemptive)
void priorityNonPreemptive(vector<proccess>& processes) {
    int n = processes.size();
    vector<bool> completed(n, false);
    int currentTime = 0, completedCount = 0;

    while (completedCount < n) {
        int highestPriorityIdx = -1;
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].at <= currentTime) {
                if (highestPriorityIdx == -1 || processes[i].pr > processes[highestPriorityIdx].pr) {
                    highestPriorityIdx = i;
                }
            }
        }

        if (highestPriorityIdx == -1) {
            currentTime++;
            continue;
        }

        proccess& p = processes[highestPriorityIdx];
        currentTime += p.bt;
        p.ft = currentTime;   // Finish Time
        p.tat = p.ft - p.at;
        p.wt = p.tat - p.bt;
        completed[highestPriorityIdx] = true;
        completedCount++;
    }

    printResults(processes);
}

// Priority Scheduling (Preemptive)
void priorityPreemptive(vector<proccess>& processes) {
    int n = processes.size();
    vector<int> remainingBT(n);
    for (int i = 0; i < n; ++i) {
        remainingBT[i] = processes[i].bt;
    }

    int currentTime = 0, completedCount = 0;
    while (completedCount < n) {
        int highestPriorityIdx = -1;
        for (int i = 0; i < n; ++i) {
            if (processes[i].at <= currentTime && remainingBT[i] > 0) {
                if (highestPriorityIdx == -1 || processes[i].pr > processes[highestPriorityIdx].pr) {
                    highestPriorityIdx = i;
                }
            }
        }

        if (highestPriorityIdx == -1) {
            currentTime++;
            continue;
        }

        remainingBT[highestPriorityIdx]--;
        currentTime++;

        if (remainingBT[highestPriorityIdx] == 0) {
            processes[highestPriorityIdx].ft = currentTime;  // Finish Time
            processes[highestPriorityIdx].tat = processes[highestPriorityIdx].ft - processes[highestPriorityIdx].at;
            processes[highestPriorityIdx].wt = processes[highestPriorityIdx].tat - processes[highestPriorityIdx].bt;
            completedCount++;
        }
    }

    printResults(processes);
}

// Round Robin Scheduling
void roundRobin(vector<proccess>& processes, int quantum) {
    int n = processes.size();
    vector<int> remainingBT(n);
    for (int i = 0; i < n; ++i) {
        remainingBT[i] = processes[i].bt;
    }

    queue<int> q;
    int currentTime = 0;
    int completedCount = 0;

    while (completedCount < n) {
        for (int i = 0; i < n; ++i) {
            if (processes[i].at <= currentTime && remainingBT[i] > 0) {
                q.push(i);  // Push the process index to the queue
            }
        }

        if (!q.empty()) {
            int idx = q.front();
            q.pop();

            int timeSlice = min(quantum, remainingBT[idx]);

            remainingBT[idx] -= timeSlice;
            currentTime += timeSlice;

            if (remainingBT[idx] == 0) {
                processes[idx].ft = currentTime;
                processes[idx].tat = processes[idx].ft - processes[idx].at;
                processes[idx].wt = processes[idx].tat - processes[idx].bt;
                completedCount++;
            }
        } else {
            currentTime++;
        }
    }

    printResults(processes);
}

int main() {
    int n;
    cout << "Enter Number of Processes: ";
    cin >> n;

    vector<proccess> processes(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter Arrival Time (AT), Burst Time (BT), and Priority (PR) for Process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt >> processes[i].pr;
        processes[i].remainingBT = processes[i].bt;  // Initialize remaining burst time for preemptive scheduling
    }

    int choice, quantum;
    cout << "\nChoose the Scheduling Algorithm:\n";
    cout << "1. Priority Scheduling (Non-Preemptive)\n";
    cout << "2. Priority Scheduling (Preemptive)\n";
    cout << "3. Round Robin Scheduling\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "\n--- Priority Scheduling (Non-Preemptive) ---\n";
            priorityNonPreemptive(processes);
            break;
        case 2:
            cout << "\n--- Priority Scheduling (Preemptive) ---\n";
            priorityPreemptive(processes);
            break;
        case 3:
            cout << "Enter the Time Quantum for Round Robin: ";
            cin >> quantum;
            cout << "\n--- Round Robin Scheduling ---\n";
            roundRobin(processes, quantum);
            break;
        default:
            cout << "Invalid choice!";
            break;
    }

    return 0;
}
