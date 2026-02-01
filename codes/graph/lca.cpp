#include <bits/stdc++.h>
using namespace std; 
class LCA {
public:
    int n, LOG;
    vector<int> depth;
    vector<vector<int>> up;
 
    LCA(const vector<int>& parent) {
        n = parent.size();
        LOG = 32;
        depth.assign(n, 0);
        up.assign(LOG, vector<int>(n));
        // sum.assign(LOG, vector<int>(n, 0));
        for (int v = 0; v < n; v++) {
            up[0][v] = parent[v];
            // sum[0][v] = weight[v];
        }
        for (int i = 1; i < LOG; i++) {
            for (int v = 0; v < n; v++) {
                int mid = up[i-1][v];
                if(mid == -1) {
                    up[i][v] = -1;
                    // sum[i][v] = sum[i-1][v];
                }
                else {
                    up[i][v] = up[i-1][mid];
                    // sum[i][v] = sum[i-1][v] + sum[i-1][mid];
                }
            }
        }
        for (int v = 0; v < n; v++) {
            if(parent[v] == -1) depth[v] = 0;
            else depth[v] = depth[parent[v]] + 1;
        }
    }
 
    int kthAncestor(int u, long long k) {
        int total = 0;
        for (int i = 0; i < LOG; i++) {
            if(u == -1) break;
            if(k & (1LL << i)) {
                u = up[i][u];
                // total += sum[i][u];
            }
        }
        return u;
    }
 
    int query(int u, int v) {
        if(depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        u = kthAncestor(u, diff);
        if(u == v) return u;
        for(int i = LOG-1; i >= 0; i--) {
            if(up[i][u] != -1 && up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        }
        return up[0][u];
    }
};
