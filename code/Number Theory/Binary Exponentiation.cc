// b^e % mod. mod is REQUIRED (no default = no wrong-
// mod WA)
// __int128 makes it safe for mod up to ~1e18
ll power(ll b, ll e, ll mod) {
  ll r = 1 % mod; b %= mod; if (b < 0) b += mod;
  while (e > 0) {
    if (e & 1) r = (__int128)r * b % mod;
    b = (__int128)b * b % mod;
    e >>= 1;
  }
  return r;
}
