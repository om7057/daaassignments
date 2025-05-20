#include <iostream>
#include <algorithm>

using namespace std;

// Function to solve knapsack with a given order of weights and profits
double fractionalKnapsack(int w[], int p[], int n, int capacity) {
    double totalValue = 0.0;  // Total value in knapsack
    int currentWeight = 0;    // Current weight in knapsack
    
    for (int i = 0; i < n; i++) {
        if (currentWeight + w[i] <= capacity) {
            // Take the whole item
            currentWeight += w[i];
            totalValue += p[i];
        } else {
            // Take a fraction of the item
            int remainingWeight = capacity - currentWeight;
            totalValue += (p[i] / (double)w[i]) * remainingWeight;
            break;
        }
    }
    
    return totalValue;
}

int main() {
    // Input data
    int w[] = {19, 15, 10};  // Weights
    int p[] = {25, 24, 15};  // Profits
    int n = 3;               // Number of items
    int capacity = 20;       // Knapsack capacity
    
    // a) Largest-profit strategy
    cout << "Largest-profit strategy:\n";
    // Sort items by decreasing profit
    int indices[] = {0, 1, 2};
    sort(indices, indices + n, [&](int i, int j) { return p[i] > p[j]; });
    
    int wp[3], pp[3];  // Weights and profits sorted based on strategy
    for (int i = 0; i < n; i++) {
        wp[i] = w[indices[i]];
        pp[i] = p[indices[i]];
    }
    
    cout << "Maximum value: " << fractionalKnapsack(wp, pp, n, capacity) << "\n\n";
    
    // b) Smallest-weight strategy
    cout << "Smallest-weight strategy:\n";
    // Sort items by increasing weight
    sort(indices, indices + n, [&](int i, int j) { return w[i] < w[j]; });
    
    for (int i = 0; i < n; i++) {
        wp[i] = w[indices[i]];
        pp[i] = p[indices[i]];
    }
    
    cout << "Maximum value: " << fractionalKnapsack(wp, pp, n, capacity) << "\n\n";
    
    // c) Largest profit-weight ratio strategy
    cout << "Largest profit-weight ratio strategy:\n";
    // Sort items by decreasing profit-to-weight ratio
    sort(indices, indices + n, [&](int i, int j) { return (p[i] / (double)w[i]) > (p[j] / (double)w[j]); });
    
    for (int i = 0; i < n; i++) {
        wp[i] = w[indices[i]];
        pp[i] = p[indices[i]];
    }
    
    cout << "Maximum value: " << fractionalKnapsack(wp, pp, n, capacity) << "\n";

    return 0;
}
