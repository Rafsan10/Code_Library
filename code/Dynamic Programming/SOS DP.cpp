// SOS DP, O(MLOG * 2^MLOG). Set dp[mask] = f(mask), then
// forward1: dp[mask] = sum of f(sub) over submasks sub
// backward1: inverse of forward1 (Mobius transform)
// forward2 / backward2: same for supermasks
// All submasks of mask, O(3^n) total over all masks:
// for (int s = mask; s; s = (s - 1) & mask) {...} (+ s=0)
const int MAXN = 1 << 20, MLOG = 20;
ll dp[MAXN];
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