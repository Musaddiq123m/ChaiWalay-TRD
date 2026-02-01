#include "dsu.cpp"
#include<bits/stdc++.h>
using namespace std;
struct Edge {
    int u, v, w;
    bool operator<(const Edge& e) const {
        return w < e.w;
    }
};
int kruskal(int n, vector<Edge>& edges, vector<Edge>& mst_edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    int cost = 0;
    for (const Edge& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            cost += e.w;
            mst_edges.push_back(e);
        }
    }
    return cost;
}
