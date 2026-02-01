// Usage : cd. init (n, k); cd. add(u, v); cd. decompose (0);
struct CentroidDecomp
{
    int n, k;
    vector<vi> adj;
    vector<bool> vis;
    vi sz, cnt;
    ll ans = 0;
    void init(int _n, int _k){
        n = _n;
        k = _k;
        adj.assign(n, {});
        vis.assign(n, 0);
        sz.resize(n);
        cnt.assign(n + 1, 0);
    }
    void add(int u, int v){
        adj[u].pb(v);
        adj[v].pb(u);
    }
    int dfsSz(int u, int p){
        sz[u] = 1;
        for (int v : adj[u])
            if (v != p && !vis[v])
                sz[u] += dfsSz(v, u);
        return sz[u];
    }
    int findCentroid(int u, int p = -1, int total = -1){
        if (total == -1) total = dfsSz(u, p);
        for (int v : adj[u])
            if (v != p && !vis[v] && sz[v] > total / 2)
                return findCentroid(v, u, total);
        return u;
    }
    void getDists(int u, int p, int d, vi &nodes){
        if (d > k)
            return;
        nodes.pb(d);
        for (int v : adj[u])
            if (v != p && !vis[v])
                getDists(v, u, d + 1,
                         nodes);
    }
    void decompose(int u = 0){
        int centroid = findCentroid(u, -1, dfsSz(u, -1));
        vis[centroid] = true;
        cnt[0] = 1;
        vector<int> nodes_to_clear;
        for (int v : adj[centroid])
            if (!vis[v])
            {
                vi nodes;
                getDists(v, centroid, 1, nodes);
                for (int d : nodes)
                {
                    if (k - d >= 0)
                        ans += cnt[k - d];
                }
                for (int d : nodes)
                {
                    if (k - d >= 0)
                    {
                        cnt[d]++;
                        nodes_to_clear.pb(d);
                    }
                }
            }
        for (int d : nodes_to_clear)
            cnt[d]--;
        cnt[0] = 0;
        for (int v : adj[centroid])
            if (!vis[v])
                decompose(v);
    }
};