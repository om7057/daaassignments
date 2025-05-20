#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
const int LOG = 20;
const int MOD = 1000000007;

struct Edge {
    int to, weight;
};

vector<Edge> adj[MAXN];
int depth[MAXN], parent[MAXN][LOG], maxEdge[MAXN][LOG];
int N;

void dfs(int node, int par, int w) {
    parent[node][0] = par;
    maxEdge[node][0] = w;
    for (Edge e : adj[node]) {
        if (e.to != par) {
            depth[e.to] = depth[node] + 1;
            dfs(e.to, node, e.weight);
        }
    }
}

void preprocess() {
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= N; i++) {
            if (parent[i][j - 1] != -1) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
                maxEdge[i][j] = max(maxEdge[i][j - 1], maxEdge[parent[i][j - 1]][j - 1]);
            }
        }
    }
}

int getMaxEdge(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int maxW = 0;
    int diff = depth[u] - depth[v];

    for (int i = LOG - 1; i >= 0; i--) {
        if (diff & (1 << i)) {
            maxW = max(maxW, maxEdge[u][i]);
            u = parent[u][i];
        }
    }

    if (u == v) return maxW;

    for (int i = LOG - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            maxW = max(maxW, max(maxEdge[u][i], maxEdge[v][i]));
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return max(maxW, max(maxEdge[u][0], maxEdge[v][0]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "Enter the number of nodes (N): ";
    cout.flush(); 
    cin >> N;

    cout << "Enter " << N - 1 << " edges in the format (u v w) where:\n";
    cout << "u = node1, v = node2, w = weight of the edge between u and v\n";
    cout.flush();  
    for (int i = 1; i < N; i++) {
        int u, v, w;
        cout << "Edge " << i << ": ";
        cout.flush();  
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dfs(1, -1, 0);

    preprocess();

    long long E = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            int maxW = getMaxEdge(i, j);
            E = (E + 1LL * maxW * i * j) % MOD;
        }
    }

    cout << "The value of E modulo 10^9 + 7 is: " << E << endl;

    return 0;
}
