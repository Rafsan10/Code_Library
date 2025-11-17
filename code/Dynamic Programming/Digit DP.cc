int f(int pos, int up, int under, int nz) {
  if (pos == n) return 0;
  int& ans = dp[pos][under][up][nz];
  if (ans != -1) return ans;
  int ans = 0;
  int start = up ? 0 : s[pos] - '0';
  int end = under ? 9 : t[pos] - '0';
  for (int d = start; d <= end; d++) {
    int n_up = up || (d > s[pos] - '0');
    int n_under = under || (d < t[pos] - '0');
    int n_nz = nz || (d != 0);
    ans += f(pos + 1, n_under, n_up, n_nz);
  }
  return ans;
}
