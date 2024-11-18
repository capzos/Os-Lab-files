// Write a program to calculate the number of page faults for a reference string for the
//  following page replacement algorithms:
//  a. FIFO b)LRU c)Optimal



#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Function to calculate page faults using FIFO
int FIFO(vector<int> ref_string, int capacity) {
    vector<int> frames;
    int page_faults = 0;

    for (int page : ref_string) {
        // Check if the page is not in the current frame
        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            if (frames.size() == capacity) {
                frames.erase(frames.begin()); // Remove the oldest page
            }
            frames.push_back(page); // Add the new page
            page_faults++; // Increment page faults
        }
    }
    return page_faults;
}

// Function to calculate page faults using LRU
int LRU(vector<int> ref_string, int capacity) {
    vector<int> frames;
    int page_faults = 0;

    for (int page : ref_string) {
        auto it = find(frames.begin(), frames.end(), page);

        if (it == frames.end()) {
            if (frames.size() == capacity) {
                frames.erase(frames.begin()); // Remove the least recently used page
            }
            page_faults++;
        } else {
            frames.erase(it); // Move the page to the most recently used position
        }
        frames.push_back(page); // Add the page to the frame
    }
    return page_faults;
}

// Function to calculate page faults using Optimal
int Optimal(vector<int> ref_string, int capacity) {
    vector<int> frames;
    int page_faults = 0;

    for (int i = 0; i < ref_string.size(); i++) {
        int page = ref_string[i];
        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            if (frames.size() == capacity) {
                // Find the page to replace
                int farthest = i + 1, replace_index = 0;
                for (int j = 0; j < frames.size(); j++) {
                    auto it = find(ref_string.begin() + i + 1, ref_string.end(), frames[j]);
                    if (it == ref_string.end()) {
                        replace_index = j;
                        break;
                    } else if (it - ref_string.begin() > farthest) {
                        farthest = it - ref_string.begin();
                        replace_index = j;
                    }
                }
                frames[replace_index] = page; // Replace the farthest page
            } else {
                frames.push_back(page);
            }
            page_faults++;
        }
    }
    return page_faults;
}

int main() {
    vector<int> ref_string = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int capacity = 3;

    cout << "FIFO Page Faults: " << FIFO(ref_string, capacity) << endl;
    cout << "LRU Page Faults: " << LRU(ref_string, capacity) << endl;
    cout << "Optimal Page Faults: " << Optimal(ref_string, capacity) << endl;

    return 0;
}



/*

Page Fault: Happens when the required page isn’t in RAM, and the system must load it from storage.
Frame: A small, fixed-sized portion of RAM used to store pages.
Reference String: A sequence of page numbers requested by the program.
Page Replacement: Deciding which page to remove from RAM when there’s no free space.

*/