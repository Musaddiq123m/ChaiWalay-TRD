template <class T>
struct BIT {
    int n;
    vector<T> b, a;
    BIT() {}
    BIT(int _n) : n(_n), b(n + 1), a(n) {}
    void add(int i, T v) {
        if (i < 0) return;
        a[i] += v;
        for (++i; i <= n; i += i & -i) b[i] += v;
    }
    T sum_idx(int i) {
        if (i < 0) return 0;
        if (i >= n) i = n - 1;
        T r = 0;
        for (++i; i; i -= i & -i) r += b[i];
        return r;
    }
    T sum(int l, int r) {
        if (r < 0) return 0;
        if (l < 0) l = 0;
        return sum_idx(r) - (l ? sum_idx(l - 1) : 0);
    }
    void set(int i, T v) { add(i, v - a[i]); }
};
 
struct CentroidDecomp {
    int n;
    int k1, k2; 
    vector<vector<int>> adj;
    vector<char> vis;
    vector<int> sub;
    BIT<int> ft;
    ll ans = 0;
    vector<int> cnt; 
    vector<int> usedDepths;
 
    void init(int _n, int _A, int _B) {
        n = _n; k1 = _A; k2 = _B;
        adj.assign(n + 1, {});
        vis.assign(n + 1, 0);
        sub.assign(n + 1, 0);
        ft = BIT<int>(k2 + 5); 
        ans = 0;
        cnt.assign(k2 + 5, 0);
        usedDepths.reserve(256);
    }
 
    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    int dfsSz(int u, int p) {
        sub[u] = 1;
        for (int v : adj[u])
            if (v != p && !vis[v]) sub[u] += dfsSz(v, u);
        return sub[u];
    }
 
    int findCentroid(int u, int p = -1, int total = -1) {
        if (total == -1) total = dfsSz(u, p); 
        for (int v : adj[u]) {
            if (v != p && !vis[v] && sub[v] > total / 2)
                return findCentroid(v, u, total);
        }
        return u;
    }

 
    int get_cnt(int u, int p, int depth) {
        if (depth > k2) return 0;
        cnt[depth]++;
        int maxd = depth;
        for (int v : adj[u])
            if (v != p && !vis[v]) {
                int d = get_cnt(v, u, depth + 1);
                if (d > maxd) maxd = d;
            }
        return maxd;
    }
 
    void decompose(int entry = 1) {
        int total = dfsSz(entry, 0);
        int c = findCentroid(entry, 0, total);
        vis[c] = 1;
 
        ft.add(0, 1);
 
        for (int v : adj[c]) {
            if (vis[v]) continue;
 
            int maxd = get_cnt(v, c, 1); 

            for (int d = 1; d <= maxd; ++d) {
                if (cnt[d] == 0) continue;
                int L = k1 - d;
                int R = k2 - d;
                if (R < 0) continue;
                ll ways = ft.sum(max(0, L), R);
                ans += ways * (ll)cnt[d];
            }
 
            for (int d = 1; d <= maxd; ++d) {
                if (cnt[d] == 0) continue;
                ft.add(d, cnt[d]);
                usedDepths.push_back(d);
            }
 
            for (int d = 1; d <= maxd; ++d) cnt[d] = 0;
        }
 
        for (int d : usedDepths) {
            ft.set(d, 0);
        }
        usedDepths.clear();
 
        ft.set(0, 0);
 
        for (int v : adj[c]) if (!vis[v]) decompose(v);
    }
};
 