struct SparseTable
{
    vector<vector<int>> st;
    vector<int> log;
    SparseTable() {}
    void init(const vector<int> &a)
    {
        int n = a.size();
        if (n == 0)
            return;
        int k = 32 - __builtin_clz(n);
        st.assign(k, vector<int>(n));
        log.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) log[i] = log[i / 2] + 1;
        st[0] = a;
        for (int j = 1; j < k; j++) for (int i = 0; i <= n - (1 << j); i++)
            st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
    int query(int l, int r)
    {
        int j = log[r - l + 1];
        return min(st[j][l], st[j][r - (1 << j) + 1]);
    }
};