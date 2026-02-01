string lcs(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            dp[i+1][j+1] = (a[i] == b[j] ? dp[i][j]+1 : max(dp[i][j+1], dp[i+1][j]));
    
    string res;
    for (int i = n, j = m; i > 0 && j > 0; ) {
        if (a[i-1] == b[j-1]) res += a[i-1], --i, --j;
        else if (dp[i-1][j] > dp[i][j-1]) --i;
        else --j;
    }
    reverse(res.begin(), res.end());
    return res;
}
