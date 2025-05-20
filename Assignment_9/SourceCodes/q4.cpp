#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DisjointSet {
public:
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    bool unite(int u, int v) {
        int rootU = find(u), rootV = find(v);
        if (rootU == rootV) return false; 
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return true;
    }
};

int main() {
    int N, M;
    cout << "Enter the number of cities (N) and roads (M): ";
    cin >> N >> M;

    vector<tuple<int, int, int>> edges;
    cout << "Enter the roads (a, b, type):" << endl;
    for (int i = 0; i < M; i++) {
        int u, v, type;
        cin >> u >> v >> type;
        edges.push_back(make_tuple(u, v, type));
    }

    DisjointSet men(N), women(N);
    
    int totalEdges = 0;
    int usedEdgesMen = 0, usedEdgesWomen = 0;
    
    for (auto [u, v, type] : edges) {
        if (type == 3) {
            bool connectedMen = men.unite(u, v);
            bool connectedWomen = women.unite(u, v);
            if (connectedMen || connectedWomen) {
                totalEdges++;
                if (connectedMen) usedEdgesMen++;
                if (connectedWomen) usedEdgesWomen++;
            }
        }
    }

    for (auto [u, v, type] : edges) {
        if (type == 1) {  
            if (men.unite(u, v)) {
                totalEdges++;
                usedEdgesMen++;
            }
        } else if (type == 2) {  
            if (women.unite(u, v)) {
                totalEdges++;
                usedEdgesWomen++;
            }
        }
    }

    bool fullyConnectedMen = true, fullyConnectedWomen = true;
    for (int i = 1; i <= N; i++) {
        if (men.find(i) != men.find(1)) fullyConnectedMen = false;
        if (women.find(i) != women.find(1)) fullyConnectedWomen = false;
    }

    if (fullyConnectedMen && fullyConnectedWomen) {
        cout << "Maximum number of roads that can be destroyed: " << M - totalEdges << endl;
    } else {
        cout << "-1" << endl;  
    }

    return 0;
}
