// sum over subsets
// fact: need sum of submasks
void SOS(vector<int>& v) {
  const int BITS = log2(*max_element(v.begin(), v.end())) + 1;
  vector<int> freq(1 << BITS, 0);
  for (int mask : v) freq[mask]++;

  vector<vector<int>> dp(BITS + 1, vector<int>(1 << BITS, 0));
  for (int mask = 0; mask < 1 << BITS; mask++) {
    dp[0][mask] = freq[mask];
  }

  for (int bits = 1; bits <= BITS; bits++) {
    for (int mask = 0; mask < 1 << BITS; mask++) {
      if ((mask & (1 << (bits - 1))) == 0) {
        dp[bits][mask] = dp[bits - 1][mask];
      } else {
        int other_mask = mask - (1 << (bits - 1));
        dp[bits][mask] = dp[bits - 1][mask] + dp[bits - 1][other_mask];
      }
    }
  }

  for (int mask : v) cout << dp[BITS][mask] << '\n';
}
// O(BITS * 2 ^ BITS)
// dp[bits][mask] means left most 'bits' of submasks can be differ (submask)
// for dp[1][11] 01, 00 are not allow because leftmost 1 bit can be differ. 10
// and 11 are allowed. for travarsing all the submask of a mask we can use
// submask = mask
// do {
// submask = (submask - 1) & mask
// } while (submask)
// O(3 ^ BITS)

const int MAXN = 1 << 20, MLOG = 20;
int dp[MAXN], freq[MAXN];

// Sum over subsets (SOS Down)
void forward1() {
  for (int bit = 0; bit < MLOG; bit++)
    for (int i = 0; i < MAXN; i++)
      if (i & (1 << bit)) dp[i] += dp[i ^ (1 << bit)];
}

void backward1() {
  for (int bit = 0; bit < MLOG; bit++)
    for (int i = MAXN - 1; i >= 0; i--)
      if (i & (1 << bit)) dp[i] -= dp[i ^ (1 << bit)];
}

// Sum over supersets (SOS Up)
void forward2() {
  for (int bit = 0; bit < MLOG; bit++)
    for (int i = MAXN - 1; i >= 0; i--)
      if (i & (1 << bit)) dp[i ^ (1 << bit)] += dp[i];
}

void backward2() {
  for (int bit = 0; bit < MLOG; bit++)
    for (int i = 0; i < MAXN; i++)
      if (i & (1 << bit)) dp[i ^ (1 << bit)] -= dp[i];
}
