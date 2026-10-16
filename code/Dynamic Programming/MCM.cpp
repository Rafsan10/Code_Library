// Matrix i has size v[i-1] x v[i], i = 1..n. O(n^3)
// memset(dp, -1, sizeof dp); MCM(1, n);
// print_order(1, n);
const int N = 505;
vector<ll> v;
ll dp[N][N]; int mark[N][N];
ll MCM(int i, int j) {
  if (i == j) return dp[i][j] = 0;
  if (dp[i][j] != -1) return dp[i][j];
  ll mn = LLONG_MAX;
  for (int k = i; k < j; k++) {
    ll c = MCM(i, k) + MCM(k + 1, j)
         + v[i - 1] * v[k] * v[j];
    if (c < mn) mn = c, mark[i][j] = k;
  }
  return dp[i][j] = mn;
}
void print_order(int i, int j) {
  if (i == j) { cout << "X" << i; return; }
  cout << "(";
  print_order(i, mark[i][j]);
  print_order(mark[i][j] + 1, j);
  cout << ")";
}
