#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int longestSubarray(vector<int>& arr, int N, int X, int Y) {
    unordered_map<int, int> freq;  // To store frequency of elements
    int left = 0, right = 0, maxLength = 0, distinctCount = 0;
    bool containsY = false;

    for (right = 0; right < N; ++right) {
        int current = arr[right];
        
        // Add the current element to the frequency map
        if (freq[current] == 0) {
            distinctCount++;
        }
        freq[current]++;
        
        // Check if Y exists in the subarray
        if (current == Y) {
            containsY = true;
        }
        
        // Shrink the window if distinct elements exceed X
        while (distinctCount > X) {
            freq[arr[left]]--;
            if (freq[arr[left]] == 0) {
                distinctCount--;
            }
            if (arr[left] == Y && freq[arr[left]] == 0) {
                containsY = false; // Y is no longer in the window
            }
            left++;
        }
        
        // Update the maxLength if the window contains exactly X distinct elements and Y is present
        if (distinctCount == X && containsY) {
            maxLength = max(maxLength, right - left + 1);
        }
    }
    
    return maxLength;
}

int main() {
    
        int N, X, Y;
        cin >> N >> X >> Y;  // Size of array, value of X, and value of Y
        
        vector<int> arr(N);
        for (int i = 0; i < N; i++) {
            cin >> arr[i];  // Array elements
        }
        
        int result = longestSubarray(arr, N, X, Y);
        cout << result << endl;  // Print the result for each test case

    return 0;
}
