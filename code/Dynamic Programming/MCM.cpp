const int N = 1005;
vector<int> v;
int dp[N][N], mark[N][N];
int MCM(int i, int j) {
  if (i == j) return dp[i][j] = 0;
  if (dp[i][j] != -1) return dp[i][j];
  int mn = INT_MAX;
  for (int k = i; k < j; k++) {
    int x = mn;
    mn = min(mn, MCM(i, k) + MCM(k + 1, j) + v[i - 1] * v[k] * v[j]);
    if (x != mn) mark[i][j] = k;
  }
  return dp[i][j] = mn;
}
void print_order(int i, int j) {
  if (i == j)
    cout << "X" << i;
  else {
    cout << "(";
    print_order(i, mark[i][j]);
    print_order(mark[i][j] + 1, j);
    cout << ")";
  }
}
// memset(dp, -1, sizeof dp);
// print_order(1, n);
