// Count x in [0, X] with a digit property. Answer for
// [L, R] = solve(R) - solve(L-1). Example: digit sum K
// tight: prefix equals X so far; started: non-zero seen
// (use `started` when leading zeros matter)
string s; int K;
ll dp[20][2][2][200]; // pos, tight, started, sum
ll f(int pos, bool tight, bool started, int sum) {
  if (pos == (int)s.size()) return sum == K; // EDIT
  ll &res = dp[pos][tight][started][sum];
  if (res != -1) return res;
  res = 0;
  int lim = tight ? s[pos] - '0' : 9;
  for (int d = 0; d <= lim; d++)
    res += f(pos + 1, tight && d == lim, started || d,
             sum + d);
  return res;
}
ll solve(ll X) {
  if (X < 0) return 0;
  s = to_string(X);
  memset(dp, -1, sizeof dp);
  return f(0, 1, 0, 0);
}
