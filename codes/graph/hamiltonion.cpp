#include<bits/stdc++.h>
using namespace std;

vector<int> hamiltonianPath(int n, const vector<vector<int>>& adj) {
    int FULL = 1 << n;
    vector<vector<bool>> dp(FULL, vector<bool>(n, false));
    vector<vector<int>> par(FULL, vector<int>(n, -1));

    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = true;
    }

    for (int mask = 0; mask < FULL; mask++) {
        for (int u = 0; u < n; u++) {
            if (!dp[mask][u]) continue;
            for (int v : adj[u]) {
                if (mask & (1 << v)) continue;      
                int nextMask = mask | (1 << v);
                if (!dp[nextMask][v]) {
                    dp[nextMask][v] = true;
                    par[nextMask][v] = u;
                }
            }
        }
    }

    int end = -1, fullMask = FULL - 1;
    for (int u = 0; u < n; u++) {
        if (dp[fullMask][u]) {
            end = u;
            break;
        }
    }
    if (end == -1) {
        return {};
    }

    vector<int> path;
    int mask = fullMask, cur = end;
    while (cur != -1) {
        path.push_back(cur);
        int p = par[mask][cur];
        mask ^= 1 << cur;
        cur = p;
    }
    reverse(path.begin(), path.end());
    return path;
}

