#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> floydWarshall(const vector<vector<pair<int,int>>>& adj) {
    int n = adj.size();
    const int INF = numeric_limits<int>::max() / 4;

    vector<vector<int>> dist(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        for (auto [v, w] : adj[i]) {
            dist[i][v] = min(dist[i][v], w);
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (dist[k][j] == INF) continue;
                int throughK = dist[i][k] + dist[k][j];
                if (throughK < dist[i][j]) {
                    dist[i][j] = throughK;
                }
            }
        }
    }
    return dist;
}