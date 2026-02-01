class PersistentSegmentTree {
private:
    struct Node {
        int cnt;
        Node *left, *right;
        Node(int c = 0, Node* l = nullptr, Node* r = nullptr)
            : cnt(c), left(l), right(r) {}
    };

    vector<Node*> roots;
    vector<int> compressed; // coordinate compressed values
    unordered_map<int, int> val_to_idx;
    int n, C;

    Node* build(int l, int r) {
        if (l == r) return new Node();
        int m = (l + r) / 2;
        return new Node(0, build(l, m), build(m + 1, r));
    }

    Node* update(Node* prev, int l, int r, int pos) {
        if (l == r) return new Node(prev->cnt + 1);
        int m = (l + r) / 2;
        if (pos <= m)
            return new Node(prev->cnt + 1, update(prev->left, l, m, pos), prev->right);
        else
            return new Node(prev->cnt + 1, prev->left, update(prev->right, m + 1, r, pos));
    }

    int query(Node* rnode, Node* lnode, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return rnode->cnt - lnode->cnt;
        int m = (l + r) / 2;
        return query(rnode->left, lnode->left, l, m, ql, qr) +
               query(rnode->right, lnode->right, m + 1, r, ql, qr);
    }

    int get_idx_strict(int x) {
        return upper_bound(compressed.begin(), compressed.end(), x) - compressed.begin() + 1;
    }

    int get_idx_loose(int x) {
        return lower_bound(compressed.begin(), compressed.end(), x) - compressed.begin() + 1;
    }

public:
    PersistentSegmentTree(const vector<int>& arr) {
        n = arr.size();
        compressed = arr;
        sort(compressed.begin(), compressed.end());
        compressed.erase(unique(compressed.begin(), compressed.end()), compressed.end());
        C = compressed.size();
        for (int i = 0; i < C; ++i)
            val_to_idx[compressed[i]] = i + 1;

        roots.resize(n + 1);
        roots[0] = build(1, C);
        for (int i = 1; i <= n; ++i) {
            int pos = val_to_idx[arr[i - 1]];
            roots[i] = update(roots[i - 1], 1, C, pos);
        }
    }

    // Count how many in arr[l..r] > x
    int count_greater(int l, int r, int x) {
        int pos = get_idx_strict(x);
        if (pos > C) return 0;
        return query(roots[r], roots[l - 1], 1, C, pos, C);
    }

    // Count how many in arr[l..r] >= x
    int count_greater_equal(int l, int r, int x) {
        int pos = get_idx_loose(x);
        if (pos > C) return 0;
        return query(roots[r], roots[l - 1], 1, C, pos, C);
    }

    // Count how many in arr[l..r] < x
    int count_less(int l, int r, int x) {
        int pos = get_idx_loose(x);
        if (pos <= 1) return 0;
        return query(roots[r], roots[l - 1], 1, C, 1, pos - 1);
    }

    // Count how many in arr[l..r] <= x
    int count_less_equal(int l, int r, int x) {
        int pos = get_idx_strict(x);
        if (pos <= 1) return 0;
        return query(roots[r], roots[l - 1], 1, C, 1, pos - 1);
    }
};