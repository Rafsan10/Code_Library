// z[i] = longest common prefix of s and s[i..], z[0]=0
// search: z of (p + '#' + t), match where z == |p|
vector<int> zfunc(const string& s) {
  int n = s.size();
  vector<int> z(n, 0);
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      z[i]++;
    if (i + z[i] > r) l = i, r = i + z[i];
  }
  return z;
}
// Manacher: d1[i] = # odd palindromes centered at i
// (longest = 2*d1[i]-1), d2[i] = # even palindromes
// centered between i-1 and i (longest = 2*d2[i]). O(n)
pair<vector<int>, vector<int>> manacher(string& s) {
  int n = s.size();
  vector<int> d1(n), d2(n);
  for (int i = 0, l = 0, r = -1; i < n; i++) {
    int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
    while (i - k >= 0 && i + k < n &&
           s[i - k] == s[i + k]) k++;
    d1[i] = k--;
    if (i + k > r) l = i - k, r = i + k;
  }
  for (int i = 0, l = 0, r = -1; i < n; i++) {
    int k = (i > r) ? 0
                    : min(d2[l + r - i + 1], r - i + 1);
    while (i - k - 1 >= 0 && i + k < n &&
           s[i - k - 1] == s[i + k]) k++;
    d2[i] = k--;
    if (i + k > r) l = i - k - 1, r = i + k;
  }
  return {d1, d2};
}
