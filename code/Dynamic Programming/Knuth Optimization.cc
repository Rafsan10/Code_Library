// dp[i][j] = min_{i<=k<j} dp[i][k]+dp[k+1][j]+C(i,j)
// valid if opt[i][j-1] <= opt[i][j] <= opt[i+1][j]
// (C quadrangle inequality, e.g. merging stones /
// optimal BST). O(n^2) instead of O(n^3). 0-indexed
ll knuth(int n, function<ll(int, int)> C) {
  vector<vector<ll>> dp(n, vector<ll>(n, 0));
  vector<vector<int>> opt(n, vector<int>(n));
  for (int i = 0; i < n; i++) opt[i][i] = i;
  for (int len = 2; len <= n; len++)
    for (int i = 0; i + len - 1 < n; i++) {
      int j = i + len - 1;
      dp[i][j] = LLONG_MAX;
      int lo = opt[i][j - 1];
      int hi = min(j - 1, opt[i + 1][j]);
      for (int k = lo; k <= hi; k++) {
        ll c = dp[i][k] + dp[k + 1][j] + C(i, j);
        if (c < dp[i][j]) dp[i][j] = c, opt[i][j] = k;
      }
    }
  return dp[0][n - 1];
}
