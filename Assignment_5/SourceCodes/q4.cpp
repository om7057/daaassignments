#include <iostream>
#include <vector>

using namespace std;

// Union-Find structure to handle connections
class UnionFind {
private:
    vector<int> parent, rank;

public:
    // Constructor to initialize DSU
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; ++i) {
            parent[i] = i; // Every node is its own parent initially
        }
    }

    // Find function with path compression
    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    // Union function with union by rank
    void unionSets(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);

        if (root_u != root_v) {
            if (rank[root_u] > rank[root_v]) {
                parent[root_v] = root_u;
            } else if (rank[root_u] < rank[root_v]) {
                parent[root_u] = root_v;
            } else {
                parent[root_v] = root_u;
                rank[root_u]++;
            }
        }
    }
};

// Function to check if the network is balanced after each query
vector<string> isBalanced(int n, int q, vector<vector<int>>& queries) {
    UnionFind railwayUF(n); // DSU for railway tracks
    UnionFind roadUF(n);    // DSU for roads
    vector<string> result;

    for (const auto& query : queries) {
        int type = query[0], u = query[1] - 1, v = query[2] - 1; // Convert to 0-indexed

        if (type == 1) {
            railwayUF.unionSets(u, v); // Build railway track
        } else if (type == 2) {
            roadUF.unionSets(u, v);    // Build road
        }

        // Check if the network is balanced
        bool balanced = true;
        for (int i = 0; i < n; ++i) {
            if (railwayUF.find(i) != roadUF.find(i)) {
                balanced = false;
                break;
            }
        }

        if (balanced) {
            result.push_back("YES");
        } else {
            result.push_back("NO");
        }
    }

    return result;
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> queries(q, vector<int>(3));
    for (int i = 0; i < q; ++i) {
        cin >> queries[i][0] >> queries[i][1] >> queries[i][2];
    }

    vector<string> result = isBalanced(n, q, queries);

    for (const string& res : result) {
        cout << res << endl;
    }

    return 0;
}
