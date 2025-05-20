#include <iostream>
#include <algorithm>

using namespace std;

// Function to find the maximum profit sequence of jobs
void jobSequencing(char jobID[], int deadlines[], int profits[], int n) {
    // Arrays to keep track of used time slots and job sequence
    bool slot[n] = {false};  // Keep track of filled time slots
    char jobSequence[n];     // Store job sequence

    // Initialize total profit
    int totalProfit = 0;

    // Sort jobs based on profits in descending order using a simple bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (profits[j] < profits[j + 1]) {
                swap(profits[j], profits[j + 1]);
                swap(deadlines[j], deadlines[j + 1]);
                swap(jobID[j], jobID[j + 1]);
            }
        }
    }

    // Iterate over all jobs
    for (int i = 0; i < n; i++) {
        // Find the latest available time slot for the job
        for (int j = min(n, deadlines[i]) - 1; j >= 0; j--) {
            if (!slot[j]) {  // If slot is free
                slot[j] = true;       // Mark the slot as filled
                jobSequence[j] = jobID[i];  // Assign the job to this slot
                totalProfit += profits[i];  // Add profit to total
                break;
            }
        }
    }

    // Display the job sequence and total profit
    cout << "Job Sequence: ";
    for (int i = 0; i < n; i++) {
        if (slot[i]) {
            cout << jobSequence[i] << " ";
        }
    }
    cout << "\nTotal Profit: " << totalProfit << endl;
}

int main() {
    // Example 1: 7 Jobs with deadlines and profits
    char jobID1[] = {'1', '2', '3', '4', '5', '6', '7'};
    int deadlines1[] = {1, 3, 4, 3, 2, 1, 2};
    int profits1[] = {3, 5, 20, 18, 1, 6, 30};
    int n1 = sizeof(jobID1) / sizeof(jobID1[0]);
    cout << "Test Case 1:\n";
    jobSequencing(jobID1, deadlines1, profits1, n1);

    // Example 2: 5 Jobs with deadlines and profits
    char jobID2[] = {'a', 'b', 'c', 'd', 'e'};
    int deadlines2[] = {2, 1, 2, 1, 3};
    int profits2[] = {90, 19, 27, 25, 15};
    int n2 = sizeof(jobID2) / sizeof(jobID2[0]);
    cout << "\nTest Case 2:\n";
    jobSequencing(jobID2, deadlines2, profits2, n2);

    return 0;
}
