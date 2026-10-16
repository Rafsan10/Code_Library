// Primes in [L, R], R up to ~1e12, R - L up to ~1e7
// `primes` must contain all primes <= sqrt(R) (Sieve)
vector<ll> segmentedSieve(ll L, ll R, vector<int>& primes) {
  vector<bool> isPrime(R - L + 1, true);
  for (ll p : primes) {
    if (p * p > R) break;
    ll start = max(p * p, (L + p - 1) / p * p);
    for (ll j = start; j <= R; j += p) isPrime[j - L] = false;
  }
  vector<ll> res;
  for (ll i = max(L, 2LL); i <= R; i++)
    if (isPrime[i - L]) res.push_back(i);
  return res;
}
