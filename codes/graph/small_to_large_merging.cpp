void dfs(int u, int par, vector<vector<int>>& g, vector<int>& col, vector<int>& ans, vector<map<int, int>>& maps) {
    map<int,int>& big = maps[u];

    for (int v : g[u]) {
        if (v == par) continue;

        dfs(v, u, g, col, ans, maps);
        map<int,int>& cur = maps[v];

        if (cur.size() > big.size()) {
            swap(cur, big);
        }

        for (auto& [color, cnt] : cur) {
            big[color] += cnt;
        }
    }

    big[col[u]]++;

    ans[u] = (int)big.size();
}