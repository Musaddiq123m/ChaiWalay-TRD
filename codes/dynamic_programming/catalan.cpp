//  C_n = (1/(n+1)) * (2n choose n)
long long catalan(int n) {
    vector<long long> dp(n+1);
    dp[0] = 1;
    for(int i = 1; i <= n; ++i){
        dp[i] = dp[i-1] * 2LL * (2*(i-1)+1) / (i+1);
    }
    return dp[n];
}