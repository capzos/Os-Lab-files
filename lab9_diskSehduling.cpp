// Write a program for Disk Scheduling Algorithms: SSTF, SCAN, C-Look considering the
//  initial head position moving away from the spindle

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Shortest Seek Time First (SSTF) Algorithm
int SSTF(vector<int> requests, int head){
    vector<int> sequence; // Stores the order of request service
    int seek = 0; // Total seek time

    // Loop until all requests are serviced
    while(!requests.empty()){
        // Find the request nearest to the current head position
        auto nearest = min_element(requests.begin(), requests.end(), [&](int a, int b){
            return abs(a - head) < abs(b - head);
        });

        seek += abs(*nearest - head); // Add seek time for current request
        head = *nearest; // Move head to current request
        sequence.push_back(head); // Add to the service sequence
        requests.erase(nearest); // Remove the serviced request
    }

    // Print the order of request service
    cout << "SSTF Order: ";
    for (int s : sequence) cout << s << " ";
    cout << endl;

    return seek; // Return the total seek time
}

// SCAN (Elevator) Disk Scheduling Algorithm
int SCAN(vector<int> r, int head, int disk_size){
    vector<int> s; // Stores the service sequence

    r.push_back(disk_size - 1); // Add the disk's last position (end of disk)

    vector<int> temp = r; // Copy requests
    sort(temp.begin(), temp.end()); // Sort requests in ascending order

    int index;
    // Add all requests greater than or equal to the head
    for(int i = 0; i < temp.size(); ++i){
        if(temp[i] >= head){
            s.push_back(temp[i]);
        }
        else{
            index = i; // Track the last request smaller than the head
        }
    }

    // Add all requests less than the head in reverse order
    for(int i = index; i >= 0; --i){
        s.push_back(temp[i]);
    }

    // Calculate total seek time
    int seek = abs(s[0] - head); // Seek from head to first request
    for(int i = 1; i < s.size(); ++i){
        seek += abs(s[i] - s[i-1]); // Add seek time between consecutive requests
    }

    // Print the order of request service
    cout << "SCAN Order: ";
    for (int k : s) cout << k << " ";
    cout << endl;

    return seek; // Return the total seek time
}

// C-LOOK Disk Scheduling Algorithm
int CLOOK(vector<int> r, int head, int disk_size){
    vector<int> s; // Stores the service sequence

    vector<int> temp = r; // Copy requests
    sort(temp.begin(), temp.end()); // Sort requests in ascending order

    int index;
    // Add all requests greater than or equal to the head
    for(int i = 0; i < temp.size(); ++i){
        if(temp[i] >= head){
            s.push_back(temp[i]);
        }
        else{
            index = i; // Track the last request smaller than the head
        }
    }

    // Wrap around and add all requests smaller than the head
    for(int i = 0; i <= index && i < temp.size(); ++i){
        s.push_back(temp[i]);
    }

    // Calculate total seek time
    int seek = abs(s[0] - head); // Seek from head to first request
    for(int i = 1; i < s.size(); ++i){
        seek += abs(s[i] - s[i-1]); // Add seek time between consecutive requests
    }

    // Print the order of request service
    cout << "CLOOK Order: ";
    for (int k : s) cout << k << " ";
    cout << endl;

    return seek; // Return the total seek time
}

int main(){
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67}; // Disk requests
    int head = 53; // Initial position of disk head
    int disk_size = 200; // Total disk size

    // Execute SSTF algorithm and print results
    int sstf = SSTF(requests, head);
    cout << "SSTF : " << sstf << endl;

    // Execute SCAN algorithm and print results
    int scan = SCAN(requests, head, disk_size);
    cout << "SCAN : " << scan << endl;

    // Execute CLOOK algorithm and print results
    int clook = CLOOK(requests, head, disk_size);
    cout << "CLOOK : " << clook << endl;

    return 0;
}



/*

Disk Scheduling: Algorithms used to decide the order of servicing I/O requests to reduce seek time.
Seek Time: The time required for the disk arm to move to the required track.

Algorithms Explained:
SSTF (Shortest Seek Time First): Services the request closest to the current head position.
SCAN (Elevator Algorithm): Moves the head in one direction, servicing requests, then reverses direction at the disk's end.
C-LOOK (Circular LOOK): Similar to SCAN but wraps around to the beginning of the request queue without traversing the disk's full length.

*/