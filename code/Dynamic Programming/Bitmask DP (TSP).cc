// TSP: shortest cycle through all n nodes, O(2^n n^2)
// dp[mask][v]: start 0, visited = mask, now at v
ll tsp(vector<vector<ll>>& d) {
  int n = d.size();
  const ll INF = 1e18;
  vector<vector<ll>> dp(1 << n, vector<ll>(n, INF));
  dp[1][0] = 0;
  for (int mask = 1; mask < (1 << n); mask++)
    for (int v = 0; v < n; v++) {
      if (!(mask >> v & 1) || dp[mask][v] >= INF)
        continue;
      for (int u = 0; u < n; u++)
        if (!(mask >> u & 1)) {
          int nm = mask | 1 << u;
          dp[nm][u] =
              min(dp[nm][u], dp[mask][v] + d[v][u]);
        }
    }
  ll ans = INF; // for a path: min of dp[full][v]
  for (int v = 0; v < n; v++)
    ans = min(ans, dp[(1 << n) - 1][v] + d[v][0]);
  return ans;
}
