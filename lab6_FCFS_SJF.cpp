#include <iostream>
#include <vector>
using namespace std;

struct proccess {
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ft;  // Finish Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

// Function to print results
void printResults(vector<proccess>& processes) {
    cout << "\nAT\tBT\tFT\tTAT\tWT\n";
    for (auto& p : processes) {
        cout << p.at << "\t" << p.bt << "\t" << p.ft << "\t" << p.tat << "\t" << p.wt << "\n";
    }
}

// FCFS Algorithm
void FCFS(vector<proccess>& processes) {
    int ct = 0; // Completion time
    for (auto& p : processes) {
        ct += p.bt;
        p.ft = ct;   // Finish Time = Completion Time
        p.tat = p.ft - p.at;
        p.wt = p.tat - p.bt;
    }
    printResults(processes);
}

// SJF Non-Preemptive Algorithm
void sjfNonPreemptive(vector<proccess>& processes) {
    int n = processes.size();
    vector<bool> completed(n, false);
    int currentTime = 0, completedCount = 0;

    while (completedCount < n) {
        int shortestIdx = -1;
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].at <= currentTime) {
                if (shortestIdx == -1 || processes[i].bt < processes[shortestIdx].bt) {
                    shortestIdx = i;
                }
            }
        }

        if (shortestIdx == -1) {
            currentTime++;
            continue;
        }

        proccess& p = processes[shortestIdx];
        currentTime = currentTime + p.bt;
        p.ft = currentTime;  // Finish Time
        p.tat = p.ft - p.at;
        p.wt = p.tat - p.bt;
        completed[shortestIdx] = true;
        completedCount++;
    }

    printResults(processes);
}

// SJF Preemptive Algorithm
void sjfPreemptive(vector<proccess>& processes) {
    int n = processes.size();
    vector<int> remainingBT(n); // Remaining burst time for each process
    for (int i = 0; i < n; ++i) {
        remainingBT[i] = processes[i].bt;
    }

    int currentTime = 0, completedCount = 0;

    while (completedCount < n) {
        int shortestIdx = -1;
        for (int i = 0; i < n; ++i) {
            if (processes[i].at <= currentTime && remainingBT[i] > 0) {
                if (shortestIdx == -1 || remainingBT[i] < remainingBT[shortestIdx]) {
                    shortestIdx = i;
                }
            }
        }

        if (shortestIdx == -1) {
            currentTime++;
            continue;
        }

        remainingBT[shortestIdx]--;
        currentTime++;

        if (remainingBT[shortestIdx] == 0) {
            processes[shortestIdx].ft = currentTime;  // Finish Time
            processes[shortestIdx].tat = processes[shortestIdx].ft - processes[shortestIdx].at;
            processes[shortestIdx].wt = processes[shortestIdx].tat - processes[shortestIdx].bt;
            completedCount++;
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
        cout << "Enter Arrival Time (AT), Burst Time (BT) for Process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt;
    }

    cout << "\n--- SJF Preemptive ---";
    sjfPreemptive(processes);

    cout << "\n--- SJF Non-Preemptive ---";
    sjfNonPreemptive(processes);

    cout << "\n--- FCFS ---";
    FCFS(processes);

    return 0;
}
