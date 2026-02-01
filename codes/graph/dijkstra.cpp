#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> dijkstra(vector<vector<pair<int,int>>> &a, int start){
    int n = a.size();
    vector<int> parent(n, -1);
    vector<int> distance(n, LLONG_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    distance[start] = 0;
    pq.push({0, start});

    while(!pq.empty()){
        int u = pq.top().second;
        int w = pq.top().first;
        pq.pop();

        if(w > distance[u]) continue;

        for(auto &neighbour : a[u]){
            int v = neighbour.first;
            int weight = neighbour.second;
            if(distance[u] + weight < distance[v]){
                distance[v] = distance[u] + weight;
                parent[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}
