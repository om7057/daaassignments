#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Function to find the minimum handshake time using Kahn's Algorithm
int find_minimum_handshake_time(int n, vector<vector<int>>& handshake_order) {
    vector<vector<int>> graph(n + 1); 
    vector<int> in_degree(n + 1, 0);  
    vector<int> time(n + 1, 0);       
    
    // Build the graph and calculate in-degrees
    for (int i = 0; i < n; ++i) {
        int guest = i + 1;  
        for (int j : handshake_order[i]) {
            graph[guest].push_back(j);  
            in_degree[j]++;  
        }
    }
    
    // Print graph structure and in-degrees for debugging
    cout << "Graph Structure:\n";
    for (int i = 1; i <= n; ++i) {
        cout << "Guest " << i << " -> ";
        for (int j : graph[i]) {
            cout << j << " ";
        }
        cout << endl;
    }

    cout << "In-degrees:\n";
    for (int i = 1; i <= n; ++i) {
        cout << "Guest " << i << ": " << in_degree[i] << endl;
    }
    
    // Step 1: Initialize the queue with nodes having zero in-degree
    queue<int> q;
    for (int guest = 1; guest <= n; ++guest) {
        if (in_degree[guest] == 0) {
            q.push(guest);  
        }
    }
    
    // Step 2: Process the graph using Kahn's Algorithm (topological sorting)
    int processed_count = 0;
    int max_time = 0;
    
    while (!q.empty()) {
        int guest = q.front();
        q.pop();
        processed_count++;
        
        // Process all the neighbors (other guests the current guest wants to meet)
        for (int neighbor : graph[guest]) {
            in_degree[neighbor]--;
            time[neighbor] = max(time[neighbor], time[guest] + 3);  
            if (in_degree[neighbor] == 0) {
                q.push(neighbor);  
            }
        }
        max_time = max(max_time, time[guest]);
    }
    
    // Step 3: Check if we processed all guests (if there's no cycle)
    if (processed_count == n) {
        return max_time;
    } else {
        return -1;  
    }
}

int main() {
    int n;
    cin >> n;
    
    vector<vector<int>> handshake_order(n);
    
    // Reading input: N-1 sequences of handshakes for each guest
    for (int i = 0; i < n; ++i) {
        handshake_order[i].resize(n - 1);
        for (int j = 0; j < n - 1; ++j) {
            cin >> handshake_order[i][j];
        }
    }

    // Debugging print for input
    cout << "Handshake Order Input:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Guest " << i + 1 << ": ";
        for (int j : handshake_order[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
    
    // Find and output the minimum time for handshakes or -1 if inconsistent
    int result = find_minimum_handshake_time(n, handshake_order);
    cout << result << endl;
    
    return 0;
}
