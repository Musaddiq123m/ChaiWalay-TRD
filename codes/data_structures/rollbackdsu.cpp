struct RollbackDSU {
    vector<long long> parent;
    vector<pair<int, long long>> history;
    int components;

    RollbackDSU(int n) : parent(n, -1), components(n) {}

    int find(int x) {
        return parent[x] < 0 ? x : find(parent[x]);
    }

    int size(int x) {
        return -parent[find(x)];
    }

    int time() {
        return (int)history.size();
    }

    void rollback(int t) {
        components += (time() - t) / 2;
        for (int i = time(); i-- > t; )
            parent[history[i].first] = history[i].second;
        history.resize(t);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (parent[a] > parent[b]) swap(a, b);
        history.push_back({a, parent[a]});
        history.push_back({b, parent[b]});
        parent[a] += parent[b];
        parent[b] = a;
        components--;
        return true;
    }
};
