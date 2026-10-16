// sum_{i=1..N} SOD(i) = sum_i i * (N / i). O(sqrt N)
// result ~ 0.82 * N^2 -> fits ll for N <= ~3e9
ll SOD_upto_N(ll N) {
  ll res = 0;
  for (ll i = 1, j; i <= N; i = j + 1) {
    j = N / (N / i); // last i with the same quotient
    res += (N / i) * ((i + j) * (j - i + 1) / 2);
  }
  return res;
}
// sum_{i=1..N} NOD(i) = sum_i (N / i). O(sqrt N)
ll NOD_upto_N(ll N) {
  ll res = 0, u = sqrtl(N);
  while (u * u > N) u--;
  while ((u + 1) * (u + 1) <= N) u++;
  for (ll i = 1; i <= u; i++) res += N / i - i;
  return res * 2 + u;
}
// NOD / SOD of every number 1..n. O(n log n)
vector<ll> divisorSieve(int n, bool sod = false) {
  vector<ll> d(n + 1, 0);
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j += i) d[j] += sod ? i : 1;
  return d;
}
