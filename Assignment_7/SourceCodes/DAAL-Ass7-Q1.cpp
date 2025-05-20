// // Kruskal's Algorithm

// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <unordered_map>

// using namespace std;

// struct Edge {
//     int src, dest, weight;
// };

// struct DisjointSet {
//     vector<int> parent, rank;

//     DisjointSet(int n) {
//         parent.resize(n);
//         rank.resize(n, 0);
//         for (int i = 0; i < n; i++)
//             parent[i] = i;
//     }

//     int find(int u) {
//         if (parent[u] != u)
//             parent[u] = find(parent[u]);
//         return parent[u];
//     }

//     void unionSet(int u, int v) {
//         int rootU = find(u);
//         int rootV = find(v);
//         if (rootU != rootV) {
//             if (rank[rootU] > rank[rootV]) {
//                 parent[rootV] = rootU;
//             } else if (rank[rootU] < rank[rootV]) {
//                 parent[rootU] = rootV;
//             } else {
//                 parent[rootV] = rootU;
//                 rank[rootU]++;
//             }
//         }
//     }
// };

// bool compareEdges(Edge a, Edge b) {
//     return a.weight < b.weight;
// }

// void kruskal(int vertices, vector<Edge>& edges, const vector<char>& vertexChars) {
//     sort(edges.begin(), edges.end(), compareEdges);
//     DisjointSet ds(vertices);
//     vector<Edge> mst;
//     int totalCost = 0; // Variable to store total cost of MST

//     for (const auto& edge : edges) {
//         if (ds.find(edge.src) != ds.find(edge.dest)) {
//             ds.unionSet(edge.src, edge.dest);
//             mst.push_back(edge);
//             totalCost += edge.weight; // Add weight to total cost
//         }
//     }

//     cout << "Kruskal's MST edges:\n";
//     for (const auto& edge : mst) {
//         cout << vertexChars[edge.src] << " -- " << vertexChars[edge.dest] << " == " << edge.weight << endl;
//     }
//     cout << "Total cost of the MST: " << totalCost << endl; // Output the total cost
// }

// int main() {
//     int vertices, edgesCount;
//     cout << "Enter number of vertices: ";
//     cin >> vertices;
//     cout << "Enter number of edges: ";
//     cin >> edgesCount;

//     vector<char> vertexChars(vertices);
//     vector<Edge> edges(edgesCount);

//     cout << "Enter vertices (one at a time):\n";
//     for (int i = 0; i < vertices; i++) {
//         cin >> vertexChars[i]; 
//     }

//     cout << "Enter edges in the format (src dest weight):\n";
//     for (int i = 0; i < edgesCount; i++) {
//         char src, dest;
//         int weight;
//         cin >> src >> dest >> weight;
//         edges[i].src = find(vertexChars.begin(), vertexChars.end(), src) - vertexChars.begin();
//         edges[i].dest = find(vertexChars.begin(), vertexChars.end(), dest) - vertexChars.begin();
//         edges[i].weight = weight;
//     }

//     kruskal(vertices, edges, vertexChars);
//     return 0;
// }



// Prim's Algorithm

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <algorithm>

using namespace std;

void prim(int vertices, vector<vector<pair<int, int>>>& adj, const vector<char>& vertexChars) {
    vector<bool> inMST(vertices, false);
    vector<int> key(vertices, INT_MAX);
    vector<int> parent(vertices, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0; 
    pq.push({0, 0}); 

    int totalCost = 0; 

    while (!pq.empty()) {
        int u = pq.top().second; 
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        totalCost += key[u]; 

        for (const auto& [v, weight] : adj[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight; 
                parent[v] = u; 
                pq.push({key[v], v}); 
            }
        }
    }

    cout << "Prim's MST edges:\n";
    for (int i = 1; i < vertices; i++) {
        if (parent[i] != -1) { 
            cout << vertexChars[parent[i]] << " -- " << vertexChars[i] << " == " << key[i] << endl;
        }
    }
    cout << "Total cost of the MST: " << totalCost << endl;
}

int main() {
    int vertices, edgesCount;
    cout << "Enter number of vertices: ";
    cin >> vertices;
    cout << "Enter number of edges: ";
    cin >> edgesCount;

    vector<char> vertexChars(vertices);
    vector<vector<pair<int, int>>> adj(vertices);

    cout << "Enter vertices (one at a time):\n";
    for (int i = 0; i < vertices; i++) {
        cin >> vertexChars[i]; 
    }

    cout << "Enter edges in the format (src dest weight):\n";
    for (int i = 0; i < edgesCount; i++) {
        char src, dest;
        int weight;
        cin >> src >> dest >> weight;
        int srcIndex = find(vertexChars.begin(), vertexChars.end(), src) - vertexChars.begin();
        int destIndex = find(vertexChars.begin(), vertexChars.end(), dest) - vertexChars.begin();
        adj[srcIndex].emplace_back(destIndex, weight);
        adj[destIndex].emplace_back(srcIndex, weight); 
    }

    prim(vertices, adj, vertexChars);
    return 0;
}


//Sample Input
// Enter number of vertices: 5
// Enter number of edges: 7
// Enter vertices (one at a time):
// A
// B
// C
// D
// E
// Enter edges in the format (src dest weight):
// A B 2
// A C 3
// B C 1
// B D 4
// C E 6
// D E 5
// C D 2


//Sample Output
