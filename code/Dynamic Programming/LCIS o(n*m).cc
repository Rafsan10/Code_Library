// Longest Common Increasing Subsequence, O(n * m)
// f[j] = LCIS of a[0..i] and b[0..j] that ends at b[j]
int LCIS(vector<int>& a, vector<int>& b) {
  int m = b.size(), ans = 0;
  vector<int> f(m, 0);
  for (int x : a) {
    int best = 0; // best f[j] with b[j] < x so far
    for (int j = 0; j < m; j++) {
      if (b[j] < x) best = max(best, f[j]);
      else if (b[j] == x) f[j] = max(f[j], best + 1);
    }
  }
  for (int j = 0; j < m; j++) ans = max(ans, f[j]);
  return ans;
}
