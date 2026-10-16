// Split C[1..L] into G non-empty groups, minimize sum cost
// dp[g][i] = min_{j<=i} dp[g-1][j-1] + cost(j, i)
// Valid when opt(g, i) <= opt(g, i+1). O(G * L log L)
const ll INF = 1e18;
int G, L;
vector<ll> pre;           // pre[i] = C[1] + ... + C[i]
vector<vector<ll>> dp;    // dp[G + 1][L + 1]
ll cost(int l, int r) { // EDIT: cost of group [l, r]
  return (pre[r] - pre[l - 1]) * (r - l + 1);
}
void calc(int g, int st, int ed, int optl, int optr) {
  if (st > ed) return;
  int mid = (st + ed) / 2, pos = optl;
  dp[g][mid] = INF;
  for (int i = optl; i <= min(mid, optr); i++) {
    if (dp[g - 1][i - 1] >= INF) continue;
    ll c = dp[g - 1][i - 1] + cost(i, mid);
    if (c < dp[g][mid]) dp[g][mid] = c, pos = i;
  }
  calc(g, st, mid - 1, optl, pos);
  calc(g, mid + 1, ed, pos, optr);
}
ll solve() {
  dp.assign(G + 1, vector<ll>(L + 1, INF));
  dp[0][0] = 0;
  for (int g = 1; g <= G; g++) calc(g, 1, L, 1, L);
  return dp[G][L];
}
