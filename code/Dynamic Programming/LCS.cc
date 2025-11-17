// LCS DP Table and LCS Length
vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1));
for (int i = 1; i <= s.size(); i++) {
  for (int j = 1; j <= t.size(); j++) {
    if (s[i - 1] == t[j - 1])
      dp[i][j] = dp[i - 1][j - 1] + 1;
    else
      dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
  }
}
cout << dp[s.size()][t.size()] << "\n";

// Any LCS String
string a;
int i = s.size();
int j = t.size();
while (i > 0 && j > 0) {
  if (s[i - 1] == t[j - 1]) {
    a += s[i - 1];
    i--, j--;
  } else if (dp[i][j - 1] > dp[i - 1][j])
    j--;
  else
    i--;
}
reverse(a.begin(), a.end());
cout << a << "\n";

// Lexicographically smallest LCS
vector<vector<string>> dpp(s.size() + 1, vector<string>(t.size() + 1));
for (int i = 1; i <= s.size(); i++) {
  for (int j = 1; j <= t.size(); j++) {
    if (s[i - 1] == t[j - 1])
      dpp[i][j] = dpp[i - 1][j - 1] + s[i - 1];
    else if (dp[i][j - 1] < dp[i - 1][j])
      dpp[i][j] = dpp[i - 1][j];
    else if (dp[i][j - 1] > dp[i - 1][j])
      dpp[i][j] = dpp[i][j - 1];
    else
      dpp[i][j] = min(dpp[i][j - 1], dpp[i - 1][j]);
  }
}
cout << dpp[s.size()][t.size()] << "\n";

// number of distinct LCS sequences
int MOD = 1e9 + 7;
vector<vector<int>> cnt(s.size() + 1, vector<int>(t.size() + 1, 1));
for (int i = 1; i <= s.size(); i++) {
  for (int j = 1; j <= t.size(); j++) {
    if (s[i - 1] == t[j - 1])
      cnt[i][j] = cnt[i - 1][j - 1];
    else if (dp[i][j - 1] < dp[i - 1][j])
      cnt[i][j] = cnt[i - 1][j];
    else if (dp[i][j - 1] > dp[i - 1][j])
      cnt[i][j] = cnt[i][j - 1];
    else {
      cnt[i][j] = cnt[i - 1][j] + cnt[i][j - 1];
      if (dp[i][j] == dp[i - 1][j - 1]) cnt[i][j] -= cnt[i - 1][j - 1];
      cnt[i][j] = (cnt[i][j] + MOD) % MOD;
    }
  }
}
