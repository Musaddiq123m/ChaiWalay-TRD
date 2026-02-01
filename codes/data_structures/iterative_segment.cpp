class SegmentTree {
public:
    int n;
    vector<long long> t;

    SegmentTree() : n(0) {}
    SegmentTree(const vector<long long>& a) { init(a); }

    static inline long long neutral() { return LLONG_MIN; }
    static inline long long merge(long long a, long long b) { return a > b ? a : b; }

    void init(const vector<long long>& a) {
        int m = (int)a.size();
        n = 1;
        while (n < m) n <<= 1;
        t.assign(2 * n, neutral());
        for (int i = 0; i < m; ++i) t[n + i] = a[i];
        for (int i = n - 1; i >= 1; --i) t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }

    long long query(int l, int r) const {
        if (l > r) return neutral();
        l += n; r += n;
        long long resL = neutral(), resR = neutral();
        while (l <= r) {
            if (l & 1) resL = merge(resL, t[l++]);
            if (!(r & 1)) resR = merge(t[r--], resR);
            l >>= 1; r >>= 1;
        }
        return merge(resL, resR);
    }

    long long point_query(int pos) const {
        return t[n + pos];
    }

    void point_set(int pos, long long val) {
        int p = pos + n;
        t[p] = val;
        for (p >>= 1; p; p >>= 1) t[p] = merge(t[p << 1], t[p << 1 | 1]);
    }

    void point_update(int pos, long long delta) {
        int p = pos + n;
        t[p] += delta;
        for (p >>= 1; p; p >>= 1) t[p] = merge(t[p << 1], t[p << 1 | 1]);
    }
    
};