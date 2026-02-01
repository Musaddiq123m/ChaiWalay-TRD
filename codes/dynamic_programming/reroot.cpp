vector<int> dp(n), res(n),sz(n);

function<void(int,int)> dfs1 = [&](int u, int p){
    sz[u] = 1;
    dp[u] = 0;
    for(int v : adj[u]){
        if(v == p) continue;
        dfs1(v, u);
        dp[u] += dp[v] + sz[v];
        sz[u] += sz[v];
    }
};

function<void(int,int)> dfs2 = [&](int u, int p){
    res[u] = dp[u];
    for(int v : adj[u]){
        if(v == p) continue;
        // pichla save
        int pu = dp[u], pv = dp[v];
        int su = sz[u], sv = sz[v];
        // remove v contri from u
        dp[u] -= dp[v] + sz[v]; sz[u] -= sz[v];
        // add u contri to v
        dp[v] += dp[u] + sz[u]; sz[v] += sz[u];
        dfs2(v, u);
        // restore
        dp[u] = pu; dp[v] = pv;
        sz[u] = su; sz[v] = sv;
    }
};
dfs1(0, -1);dfs2(0, -1);