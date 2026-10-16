// nCr mod prime in O(1) after O(N) precompute
const int N = 1e6 + 5, mod = 1e9 + 7;
ll fact[N], ifact[N];
void preFact() {
  fact[0] = 1;
  for (int i = 1; i < N; i++)
    fact[i] = fact[i - 1] * i % mod;
  ifact[N - 1] = power(fact[N - 1], mod - 2, mod);
  for (int i = N - 2; i >= 0; i--)
    ifact[i] = ifact[i + 1] * (i + 1) % mod;
}
ll nCr(int n, int r) {
  if (r < 0 || n < r) return 0;
  return fact[n] * ifact[r] % mod * ifact[n - r] % mod;
}
ll nPr(int n, int r) {
  if (r < 0 || n < r) return 0;
  return fact[n] * ifact[n - r] % mod;
}
// Catalan(n) = nCr(2n, n) * inv(n + 1)
//        = (nCr(2n, n) - nCr(2n, n + 1) + mod) % mod
// Stars & bars: x1+..+xk = n, xi >= 0
//               -> nCr(n + k - 1, k - 1)
