#include<bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, size;

    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        return (parent[x] == x) ? x : parent[x] = find(parent[x]);
    }

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        return true;
    }

//if two nodes in same component
    bool same(int x, int y) {
        return find(x) == find(y);
    }

//size of x's component
    int get_size(int x) {
        return size[find(x)];
    }

    void reset() {
        iota(parent.begin(), parent.end(), 0);
        fill(size.begin(), size.end(), 1);
    }
};