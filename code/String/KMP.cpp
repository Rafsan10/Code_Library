vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}
vector<int> find_matches(string text, string pat) {
  int n = pat.length(), m = text.length();
  string s = pat + "$" + text;
  vector<int> pi = prefix_function(s), ans;
  for (int i = n; i <= n + m; i++) {
    if (pi[i] == n) {
      ans.push_back(i - 2 * n);
    }
  }
  return ans;
}
