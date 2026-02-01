#include<bits/stdc++.h>
using namespace std;

class HopcroftKarp {
public:
    HopcroftKarp(int n, int m)
        : n(n), m(m), adj(n+1), dist(n+1), pairU(n+1, 0), pairV(m+1, 0) {}
 
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
 
    int maxMatching() {
        int result = 0;
        while (bfs()) {
            for (int u = 1; u <= n; u++) {
                if (pairU[u] == 0 && dfs(u))
                    result++;
            }
        }
        return result;
    }
 
    vector<pair<int,int>> getMatchingPairs() const {
        vector<pair<int,int>> matches;
        for (int u = 1; u <= n; ++u) {
            if (pairU[u] != 0) {
                matches.emplace_back(u, pairU[u]);
            }
        }
        return matches;
    }
 
private:
    int n, m;                
    vector<vector<int>> adj; 
    vector<int> dist;        
    vector<int> pairU, pairV;// U->V and V->
 
    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; u++) {
            if (pairU[u] == 0) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INT_MAX;
            }
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (pairV[v] == 0) {
                    found = true;
                } else if (dist[pairV[v]] == INT_MAX) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
        return found;
    }
 
    bool dfs(int u) {
        for (int v : adj[u]) {
            if (pairV[v] == 0 || (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))) {
                // match u-v
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = INT_MAX; 
        return false;
    }
};