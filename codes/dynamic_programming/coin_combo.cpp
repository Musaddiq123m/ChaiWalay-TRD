for (int i = 1; i <= m; i++) {    
    // distinct = loop order switch, i = coin
    for (int coin : a) {        
        if (i - coin >= 0) {
            dp[i] = (dp[i] + dp[i - coin]) % MOD;
        }
    }
}
