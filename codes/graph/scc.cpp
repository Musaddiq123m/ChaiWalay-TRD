#include<bits/stdc++.h>
using namespace std;
class SCC{
    vector<bool> vis;
    vector<int> order;

    void dfs1(int u) {
        vis[u] = true;
        for (int v : g[u])
            if (!vis[v])
                dfs1(v);
        order.push_back(u);
    }

    void dfs2(int u, vector<int>& comp) {
        vis[u] = true;
        comp.push_back(u);
        for (int v : rg[u])
            if (!vis[v])
                dfs2(v, comp);
    }

    void find_scc(int n) {
        vis.assign(n, false);
        order.clear();
        for (int i = 0; i < n; ++i)
            if (!vis[i])
                dfs1(i);

        vis.assign(n, false);
        reverse(order.begin(), order.end());
        scc.clear();
        component_id.assign(n, -1); 
        int id = 0; 
        for (int u : order)
            if (!vis[u]) {
                vector<int> comp;
                dfs2(u, comp);
                for (int v : comp) {
                    component_id[v] = id; 
                }
                scc.push_back(comp);
                id++; 
            }
    }
    void build_condened_graph(vector<pair<int,int>>& edges){
        int k = scc.size();
        dag.assign(k, {});
        for(auto [u,v]: edges){
            int cu = component_id[u];
            int cv = component_id[v];
            if(cu != cv){
                dag[cu].push_back(cv);
            }
        }
    }
    public:
    vector<int> component_id;
    vector<vector<int>> dag;
    vector<vector<int>> g, rg, scc;
    SCC(int n, vector<pair<int,int>>& edges){
        g.assign(n, {});
        rg.assign(n, {});
        for(auto& e: edges){
            int u = e.first;
            int v = e.second;
            g[u].push_back(v);
            rg[v].push_back(u);
        }
        find_scc(n);
        build_condened_graph(edges);
    }

};