#include <iostream>
#include <vector>
#include <cmath>  // For abs function
using namespace std;

int maxSeparations(int N, vector<int>& arr, int K) {
    int oddCount = 0, evenCount = 0;
    int totalCost = 0;
    int separations = 0;

    // Traverse the array and track odd/even count
    for (int i = 0; i < N - 1; i++) {
        if (arr[i] % 2 == 0)
            evenCount++;
        else
            oddCount++;

        // If odd and even counts are equal, check if we can make a separation
        if (oddCount == evenCount) {
            int cost = abs(arr[i] - arr[i+1]);

            if (totalCost + cost <= K) {
                totalCost += cost;
                separations++;
            } else {
                break;  // If adding the cost exceeds K, stop
            }
        }
    }

    return separations;
}

int main() {
    int N, K;
    cout << "Enter the size of the array: ";
    cin >> N;

    vector<int> arr(N);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    cout << "Enter the maximum cost K: ";
    cin >> K;

    int result = maxSeparations(N, arr, K);
    cout << "Maximum number of separations: " << result << endl;

    return 0;
}
