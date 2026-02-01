int digit(int x){
    
    int dp[20][2][200];//digit, tight, sum
    for(int i = 0; i < 20; i++) 
        for(int j = 0; j < 2; j++) 
            for(int k = 0; k < 200; k++) 
                dp[i][j][k] = 0;
                
    string ss = to_string(x);
    int n = ss.size();
 
    dp[n][0][0] = 1;
    dp[n][1][0] = 1;
 
    for(int i = n-1; i >=0 ; i--) {
        for(int tight = 0; tight < 2 ; tight++) {
            for(int sum = 0; sum < 200 ; sum++) {
                if(tight) {
                    for(int d = 0; d <= ss[i] - '0' ; d++) {
                        if (sum - d < 0) continue;
                        dp[i][1][sum] += (d == ss[i]-'0') ? dp[i+1][1][sum-d] : dp[i+1][0][sum-d];
                    }
                }
                else {
                    for(int d = 0; d < 10 ; d++) {
                        if (sum - d < 0) continue;
                        dp[i][0][sum] += dp[i+1][0][sum-d];
                    }
                }
            }
        }
    }
    auto isPrime = [&](int p) -> bool {
        for(int i = 2;i * i <= p ; i++)if(p % i == 0)return false;
        return p > 1;
    };
    int ans = 0;
    for(int i = 0; i < 200; i++) {
        if(isPrime(i))
        ans += dp[0][1][i];
    }
    return ans;
}