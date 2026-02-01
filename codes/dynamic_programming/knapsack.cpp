int knapsack(const vector<int>& wt, const vector<int>& val, int W) {
    vector<long long> dp(W+1, 0);
    for(int i = 0; i < (int)wt.size(); ++i) {
        for(int w = W; w >= wt[i]; --w) {
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }
    return dp[W];
}