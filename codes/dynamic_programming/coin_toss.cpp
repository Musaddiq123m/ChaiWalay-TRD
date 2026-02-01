int m = (n + 1) / 2;
vector<vector<double>> dp(n + 5,vector<double> (n + 5));
// dp[i][j] represent possiblity of j heads using i coins
dp[0][0] = 1;
forn(i, 1, n + 1){
    // choose ith coin
    double head = a[i - 1], tail = 1 - a[i - 1];
    forn(j, 0 ,n + 1){
        // coming from jth heads in the previous round
        // if this round is tail then the number of heads don't change
        dp[i][j] += dp[i - 1][j] * tail;
        // if head comes the number of heads is 1 more
        dp[i][j + 1] += dp[i - 1][j] * head;
    }
}
double ans = 0;
for(int j = m; j <= n; j++){
    ans += dp[n][j];
}