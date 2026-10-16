// x = r1 (mod m1), x = r2 (mod m2); needs 0 <= r < m
// returns smallest x >= 0 (mod lcm), -1 if no solution
// uses exgcd (Extended GCD). lcm must fit in ll
ll crt(ll r1, ll m1, ll r2, ll m2) {
  if (m1 < m2) swap(r1, r2), swap(m1, m2);
  ll p, q, g = exgcd(m1, m2, p, q);
  if ((r2 - r1) % g != 0) return -1;  // no solution
  __int128 t = (__int128)((r2 - r1) % m2) * p % m2;
  ll x = (ll)(t * m1 / g) + r1;
  return x < 0 ? x + m1 / g * m2 : x;
}
ll crt(vector<ll>& r, vector<ll>& m) {
  ll x = r[0], M = m[0];
  for (int i = 1; i < (int)r.size(); ++i) {
    x = crt(x, M, r[i], m[i]);
    if (x == -1) return -1;
    M = M / __gcd(M, m[i]) * m[i];
  }
  return x;
}
