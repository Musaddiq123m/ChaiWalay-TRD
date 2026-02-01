template <bool EDGE_VALUES>
struct HLD {
    int n, timer;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, inPos, subSize;
    SegmentTree seg;

    HLD(int _n = 0) { init(_n); }
    void init(int _n) {
        n = _n;
        timer = 0;
        adj.assign(n, {});
        parent.assign(n, -1);
        depth.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        inPos.assign(n, 0);
        subSize.assign(n, 0);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    long long neutral() {return 0;}

    long long merge(long long a, long long b) {return a + b;}

    int dfs(int u, int p) {
        parent[u] = p;
        subSize[u] = 1;
        int maxSub = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            int sz = dfs(v, u);
            subSize[u] += sz;
            if (sz > maxSub) { maxSub = sz; heavy[u] = v; }
        }
        return subSize[u];
    }

    void decompose(int u, int h) {
        head[u] = h;
        inPos[u] = timer++;
        if (heavy[u] != -1) decompose(heavy[u], h);
        for (int v : adj[u]) {
            if (v == parent[u] || v == heavy[u]) continue;
            decompose(v, v);
        }
    }

    void build(const vector<long long>& values, int root = 0) {
        depth[root] = 0;
        timer = 0;
        dfs(root, -1);
        decompose(root, root);

        vector<long long> base(n);
        for (int u = 0; u < n; ++u) {
            base[inPos[u]] = EDGE_VALUES ? 0LL : values[u];
        }
        seg = SegmentTree(base);
    }

    long long queryPath(int u, int v) {
        long long res = neutral();
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            int L = inPos[head[u]], R = inPos[u];
            res = merge(res, seg.query(L, R));
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        int L = inPos[u] + (EDGE_VALUES?1:0), R = inPos[v];
        if (L <= R) res = merge(res, seg.query(L, R));
        return res;
    }

    void updatePath_add(int u, int v, long long delta) {
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            int L = inPos[head[u]], R = inPos[u];
            seg.update(L, R, delta);
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        int L = inPos[u] + (EDGE_VALUES?1:0), R = inPos[v];
        if (L <= R) seg.update(L, R, delta);
    }

    long long querySubtree(int u) {
        return seg.query(inPos[u] + (EDGE_VALUES?1:0), inPos[u] + subSize[u] - 1);
    }

    // void updateSubtree_add(int u, long long delta) {
    //     seg.update(inPos[u] + (EDGE_VALUES ? 1 : 0),
    //                inPos[u] + subSize[u] - 1, delta);
    // }

    void pointSet(int u, long long val) {
        long long cur = seg.point_query(inPos[u]);
        seg.point_update(inPos[u], val - cur);
    }
};
