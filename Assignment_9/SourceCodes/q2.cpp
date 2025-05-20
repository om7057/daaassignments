#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
using namespace std;

const int MAX_N = 2e5 + 5;

vector<pair<int, int>> adj[MAX_N];
int dist[MAX_N];
bool isPrime[MAX_N];

void sieve() {
    fill(isPrime, isPrime + MAX_N, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i < MAX_N; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < MAX_N; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

void dijkstra(int n) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    fill(dist, dist + n + 1, INT_MAX);

    for (int i = 1; i <= n; i++) {
        if (isPrime[i]) {
            dist[i] = 0;
            pq.push({0, i});
        }
    }

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, m;
    cout << "Enter the number of villages (N) and roads (M): ";
    cin >> n >> m;

    sieve();

    cout << "Enter " << m << " roads (u v):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        int w = max(u, v);
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dijkstra(n);

    cout << "Minimum time for vaccine to arrive at each village:" << endl;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) {
            cout << "-1 ";
        } else {
            cout << dist[i] << " ";
        }
    }
    cout << endl;

    return 0;
}