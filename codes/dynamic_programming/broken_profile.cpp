int n, m;
long long dp[105][1 << 10];

void dfs(int col, int cur_mask, int next_mask, int row) {
    // If finished processing all columns
    if (col == m) {
        dp[row + 1][next_mask] += dp[row][cur_mask];
        return;
    }

    // If this cell is already filled, skip
    if (cur_mask & (1 << col)) {
        dfs(col + 1, cur_mask, next_mask, row);
    }
    else {
        //vertical domino occupies (row, col) and (row+1, col)
        dfs(col + 1,
            cur_mask | (1 << col),
            next_mask | (1 << col),
            row);

        // horizontal domino occupies (row, col) and (row, col+1)
        if (col + 1 < m && !(cur_mask & (1 << (col + 1)))) {
            dfs(col + 2,
                cur_mask | (1 << col) | (1 << (col + 1)),
                next_mask,
                row);
        }
    }
}
dp[0][0] = 1;
for (int row = 0; row < n; row++) {
    for (int mask = 0; mask < (1 << m); mask++) {
        if (dp[row][mask] == 0) continue;
        dfs(0, mask, 0, row);
    }
}
cout << dp[n][0] << "\n";