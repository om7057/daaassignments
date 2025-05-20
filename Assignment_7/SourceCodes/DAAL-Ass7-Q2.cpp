// #include <iostream>
// #include <vector>
// #include <queue>
// #include <limits>
// #include <unordered_map>

// using namespace std;

// struct Edge {
//     int destination;
//     int weight;
// };

// void dijkstra(const unordered_map<string, int>& vertexMap, const vector<vector<Edge>>& graph, const string& startVertex) {
//     int vertices = graph.size();
//     vector<int> distances(vertices, numeric_limits<int>::max()); 
//     distances[vertexMap.at(startVertex)] = 0; 
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
//     pq.push({0, vertexMap.at(startVertex)}); 

//     while (!pq.empty()) {
//         int currentDistance = pq.top().first; 
//         int currentVertex = pq.top().second; 
//         pq.pop();

//         if (currentDistance > distances[currentVertex]) {
//             continue;
//         }

//         for (const auto& edge : graph[currentVertex]) {
//             int neighbor = edge.destination;
//             int weight = edge.weight;

//             int newDistance = currentDistance + weight;

//             if (newDistance < distances[neighbor]) {
//                 distances[neighbor] = newDistance; 
//                 pq.push({newDistance, neighbor}); 
//             }
//         }
//     }

//     cout << "Shortest distances from vertex " << startVertex << ":\n";
//     for (const auto& [vertex, index] : vertexMap) {
//         if (distances[index] == numeric_limits<int>::max()) {
//             cout << "Vertex " << vertex << " is unreachable." << endl;
//         } else {
//             cout << "Distance to vertex " << vertex << " is " << distances[index] << endl;
//         }
//     }
// }

// int main() {
//     int vertices, edgesCount;
//     cout << "Enter number of vertices: ";
//     cin >> vertices;

//     vector<vector<Edge>> graph(vertices);
//     unordered_map<string, int> vertexMap; 

//     cout << "Enter vertices (numbers or single-letter characters):\n";
//     for (int i = 0; i < vertices; i++) {
//         string vertex;
//         cin >> vertex;
//         vertexMap[vertex] = i; 
//     }

//     cout << "Enter number of edges: ";
//     cin >> edgesCount;

//     cout << "Enter edges in the format (src dest weight):\n";
//     for (int i = 0; i < edgesCount; i++) {
//         string src, dest;
//         int weight;
//         cin >> src >> dest >> weight;
//         graph[vertexMap[src]].push_back({vertexMap[dest], weight});
//         graph[vertexMap[dest]].push_back({vertexMap[src], weight}); 
//     }

//     string startVertex;
//     cout << "Enter starting vertex: ";
//     cin >> startVertex;

//     dijkstra(vertexMap, graph, startVertex);

//     return 0;
// }





// Shortest Path

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <string>
#include <algorithm> 

using namespace std;

struct Edge {
    int destination;
    int weight;
};

void dijkstra(const unordered_map<string, int>& vertexMap, const vector<vector<Edge>>& graph, const string& startVertex) {
    int vertices = graph.size();
    vector<int> distances(vertices, numeric_limits<int>::max()); 
    vector<int> predecessors(vertices, -1); 
    distances[vertexMap.at(startVertex)] = 0; 

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, vertexMap.at(startVertex)}); 

    while (!pq.empty()) {
        int currentDistance = pq.top().first; 
        int currentVertex = pq.top().second; 
        pq.pop();

        if (currentDistance > distances[currentVertex]) {
            continue;
        }

        for (const auto& edge : graph[currentVertex]) {
            int neighbor = edge.destination;
            int weight = edge.weight;

            int newDistance = currentDistance + weight;

            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance; 
                predecessors[neighbor] = currentVertex; 
                pq.push({newDistance, neighbor}); 
            }
        }
    }

    cout << "Shortest distances from vertex " << startVertex << ":\n";
    for (const auto& [vertex, index] : vertexMap) {
        if (distances[index] == numeric_limits<int>::max()) {
            cout << "Vertex " << vertex << " is unreachable." << endl;
        } else {
            cout << "Distance to vertex " << vertex << " is " << distances[index] << ". Path: ";

            vector<string> path;
            for (int v = index; v != -1; v = predecessors[v]) {
                for (const auto& pair : vertexMap) {
                    if (pair.second == v) {
                        path.push_back(pair.first);
                        break;
                    }
                }
            }
            reverse(path.begin(), path.end()); 
            for (const string& p : path) {
                cout << p << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    int vertices, edgesCount;
    cout << "Enter number of vertices: ";
    cin >> vertices;

    vector<vector<Edge>> graph(vertices);
    unordered_map<string, int> vertexMap; 

    cout << "Enter vertices (numbers or single-letter characters):\n";
    for (int i = 0; i < vertices; i++) {
        string vertex;
        cin >> vertex;
        vertexMap[vertex] = i;
    }

    cout << "Enter number of edges: ";
    cin >> edgesCount;

    cout << "Enter edges in the format (src dest weight):\n";
    for (int i = 0; i < edgesCount; i++) {
        string src, dest;
        int weight;
        cin >> src >> dest >> weight;
        graph[vertexMap[src]].push_back({vertexMap[dest], weight});
        graph[vertexMap[dest]].push_back({vertexMap[src], weight}); 
    }

    string startVertex;
    cout << "Enter starting vertex: ";
    cin >> startVertex;

    dijkstra(vertexMap, graph, startVertex);

    return 0;
}



//Sample Input 
// Enter number of vertices: 5
// Enter vertices (numbers or single-letter characters):
// A
// B
// C
// D
// E
// Enter number of edges: 7
// Enter edges in the format (src dest weight):
// A B 2
// A C 4
// B C 1
// B D 7
// C E 3
// D E 2
// A D 6
// Enter starting vertex: A
