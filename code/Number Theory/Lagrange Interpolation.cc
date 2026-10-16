// P has degree <= n, known y[i] = P(i) for i = 0..n.
// Returns P(x) mod p in O(n) (needs fact / ifact from
// nCr). e.g. sum_{i=1..x} i^k is degree k+1 in x
ll lagrange(vector<ll>& y, ll x) {
  int n = y.size() - 1;
  x %= mod; if (x < 0) x += mod;
  if (x <= n) return y[x];
  vector<ll> pre(n + 2, 1), suf(n + 2, 1);
  for (int i = 0; i <= n; i++)
    pre[i + 1] = pre[i] * ((x - i) % mod) % mod;
  for (int i = n; i >= 0; i--)
    suf[i] = suf[i + 1] * ((x - i) % mod) % mod;
  ll res = 0;
  for (int i = 0; i <= n; i++) {
    ll term = y[i] * pre[i] % mod * suf[i + 1] % mod
              * ifact[i] % mod * ifact[n - i] % mod;
    if ((n - i) & 1) term = (mod - term) % mod;
    res = (res + term) % mod;
  }
  return res;
}
