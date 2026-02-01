class BridgeArticulationFinder {
    
    int n;
    int timer;
    std::vector<std::vector<int>> adj;

    std::vector<bool> visited;
    std::vector<int> tin, low;
    void run() {
        timer = 0;
        std::fill(visited.begin(), visited.end(), false);
        std::fill(is_cutpoint.begin(), is_cutpoint.end(), false);
        bridges.clear();

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i);
            }
        }
    }
    void dfs(int u, int p = -1) {
        visited[u] = true;
        tin[u] = low[u] = timer++;
        int children = 0;
        bool parent_skipped = false;

        for (int v : adj[u]) {

            // skip exactly one edge to parent (important for multigraphs)
            if (v == p && !parent_skipped) {
                parent_skipped = true;
                continue;
            }

            if (visited[v]) {
                // back edge
                low[u] = std::min(low[u], tin[v]);
            } else {
                dfs(v, u);
                low[u] = std::min(low[u], low[v]);

                // bridge condition
                if (low[v] > tin[u]) {
                    bridges.emplace_back(min(v,u), max(v,u));
                }

                // articulation point (non-root)
                if (low[v] >= tin[u] && p != -1) {
                    is_cutpoint[u] = true;
                }

                children++;
            }
        }

        // articulation point (root)
        if (p == -1 && children > 1) {
            is_cutpoint[u] = true;
        }
    }
public:
    std::vector<bool> is_cutpoint;
    std::vector<std::pair<int,int>> bridges;
    
    BridgeArticulationFinder(const std::vector<std::vector<int>>& adjacency)
        : n(adjacency.size()), adj(adjacency)
    {
        visited.assign(n, false);
        tin.assign(n, -1);
        low.assign(n, -1);
        is_cutpoint.assign(n, false);
        timer = 0;
        run();
    }

};
