class Dinic {
public:
    struct Edge { 
        int to; 
        int cap; 
    };

    Dinic(int maxNodes = 0) { 
        n = maxNodes;
        edges.clear();
        adj.assign(n + 1, {});
        ptr.assign(n + 1, 0);
        dist.assign(n + 1, 0);
        vis.assign(n + 1, 0);
        edgeCount = 0;
        iterId = 0;
    }


    void addEdge(int from, int to, int capacity) {
        adj[from].push_back(edgeCount);
        edges.push_back({to, capacity});
        edgeCount++;
        
        adj[to].push_back(edgeCount);   
        edges.push_back({from, 0}); 
        edgeCount++;
    }

    int maxFlow(int source, int sink) {
        s = source; t = sink;
        int flow = 0;
        const int INF = (1LL << 30);
        while (bfs()) {
            // reset per-node pointer for dfs
            fill(ptr.begin(), ptr.end(), 0);
            // find blocking flow
            while (int pushed = dfs(s, INF)) flow += pushed;
        }
        return flow;
    }

    vector<pair<int,int>> minCut() {
        vector<pair<int,int>> cut;
        for (int i = 0; i < edgeCount; i++) {
            if (edges[i].cap == 0 && vis[edges[i].to] < iterId && vis[edges[i ^ 1].to] == iterId) {
                cut.emplace_back(edges[i ^ 1].to, edges[i].to);
            }
        }
        return cut;
    }

private:
    int n = 0;
    int s = 0, t = 0;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> ptr;        // current pointer per node
    vector<int> dist;       
    vector<int> vis; 
    int edgeCount = 0;
    int iterId = 0;        // iteration counter used as marker 

    bool bfs() {
        iterId++;
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        vis[s] = iterId;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            ptr[u] = 0; // reset pointer
            for (int id : adj[u]) {
                int v = edges[id].to;
                if (vis[v] < iterId && edges[id].cap > 0) {
                    vis[v] = iterId;
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return vis[t] == iterId;
    }

    int dfs(int u, int flowLimit) {
        if (u == t) return flowLimit;
        int pushedTotal = 0;
        for (; ptr[u] < (int)adj[u].size() && pushedTotal < flowLimit; ++ptr[u]) {
            int id = adj[u][ptr[u]];
            int v = edges[id].to;
            if (edges[id].cap == 0 || dist[v] != dist[u] + 1) continue;
            int pushed = dfs(v, min(flowLimit - pushedTotal, edges[id].cap));
            if (pushed == 0) continue;
            edges[id].cap -= pushed;
            edges[id ^ 1].cap += pushed;
            pushedTotal += pushed;
        }
        return pushedTotal;
    }
};