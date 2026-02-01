pair<vector<int>, pair<vector<bool>, vector<int>>> bellmanFord(
    int n, const vector<pair<pair<int,int>,int>>& edges, int src
) {
    vector<int> dist(n, INF), parent(n, -1);
    dist[src] = 0;

    for (int it = 0; it < n - 1; ++it) {
        bool any = false;
        for (auto &e : edges) {
            int u = e.first.first;
            int v = e.first.second;
            int w = e.second;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                any = true;
            }
        }
        if (!any) break;
    }

    int cycleStart = -1;
    for (auto &e : edges) {
        int u = e.first.first;
        int v = e.first.second;
        int w = e.second;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            parent[v] = u;
            cycleStart = v;
            break;
        }
    }

    vector<int> cycle;
    if (cycleStart != -1) {
        int x = cycleStart;
        for (int i = 0; i < n; ++i) x = parent[x];
        int cur = x;
        do {
            cycle.push_back(cur);
            cur = parent[cur];
        } while (cur != x && cur != -1);
        cycle.push_back(x);
        reverse(cycle.begin(), cycle.end());
    }

    vector<bool> bad(n, false);
    for (auto &e : edges) {
        int u = e.first.first;
        int v = e.first.second;
        int w = e.second;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            bad[v] = true;
        }
    }
    for (int it = 0; it < n; ++it) {
        for (auto &e : edges) {
            int u = e.first.first;
            int v = e.first.second;
            if (bad[u]) bad[v] = true;
        }
    }

    return {dist, {bad, cycle}};
}
