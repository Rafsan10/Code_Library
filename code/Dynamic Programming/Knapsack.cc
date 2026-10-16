// dp[c] = best value with capacity c (W = capacity)
// 0/1: each item once -> iterate c DOWNWARD
for (int i = 0; i < n; i++)
  for (int c = W; c >= w[i]; c--)
    dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
// Unbounded: item many times -> iterate c UPWARD
for (int i = 0; i < n; i++)
  for (int c = w[i]; c <= W; c++)
    dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
// Bounded (item i at most k[i] times): binary split
// into items of 1, 2, 4, ..., rest copies, then 0/1.
for (int i = 0; i < n; i++)
  for (int p = 1, left = k[i]; left > 0; p <<= 1) {
    int take = min(p, left); left -= take;
    W2.push_back(take * w[i]);
    V2.push_back(take * v[i]);
  }
// Count ways to make sum S (coins, order ignored):
// ways[0] = 1; for coin: for s = coin..S:
//   ways[s] += ways[s - coin]
// (order matters: swap the loops -> s outside)
// Subset sum up to 1e5-1e6: bitset b; b[0] = 1;
//   for (x : a) b |= b << x;
