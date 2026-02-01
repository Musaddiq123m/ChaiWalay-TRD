#include<bits/stdc++.h>
using namespace std;
class SegmentTree {
private:
    struct Node {
        long long sum;
        Node(long long v = 0) : sum(v) {}
    };

    int n;
    vector<Node> tree;
    vector<long long> lazy;

    Node merge(const Node &a, const Node &b) {
        return Node(a.sum + b.sum); // change for max/min/gcd if needed
    }
    Node neutral() {
        return Node(0); // 0 for sum/gcd, INT_MIN for max , INT_MAX for min
    }

    void build(int node, int l, int r, const vector<long long>& arr) {
        if (l == r) {
            tree[node] = Node(arr[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid, arr);
        build(2 * node + 1, mid + 1, r, arr);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void push(int node, int l, int r) {
        if (lazy[node]) {
            tree[node].sum += lazy[node] * (r - l + 1);
            if (l != r) {
                lazy[2 * node]     += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update(int node, int l, int r, int ql, int qr, long long val) {
        push(node, l, r);
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            lazy[node] += val;
            push(node, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(2 * node, l, mid, ql, qr, val);
        update(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {
        push(node, l, r);
        if (qr < l || r < ql) return neutral();
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return merge(query(2 * node, l, mid, ql, qr),
                     query(2 * node + 1, mid + 1, r, ql, qr));
    }

    void point_update(int node, int l, int r, int idx, long long val) {
        push(node, l, r);
        if (l == r) {
            tree[node].sum += val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) point_update(2 * node, l, mid, idx, val);
        else            point_update(2 * node + 1, mid + 1, r, idx, val);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    long long point_query(int node, int l, int r, int idx) {
        push(node, l, r);
        if (l == r) return tree[node].sum;
        int mid = (l + r) / 2;
        if (idx <= mid) return point_query(2 * node, l, mid, idx);
        else            return point_query(2 * node + 1, mid + 1, r, idx);
    }

public:
    SegmentTree(const vector<long long>& arr) {
        n = arr.size();
        tree.assign(4 * n, Node());
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1, arr);
    }

    void update(int l, int r, long long val) {
        update(1, 0, n - 1, l, r, val);
    }

    long long query(int l, int r) {
        return query(1, 0, n - 1, l, r).sum;
    }

    void point_update(int idx, long long val) {
        point_update(1, 0, n - 1, idx, val);
    }

    long long point_query(int idx) {
        return point_query(1, 0, n - 1, idx);
    }
};