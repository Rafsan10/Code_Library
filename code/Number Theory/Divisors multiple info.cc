// Factorize n with `primes` (Sieve, up to sqrt n):
// min/max prime, #distinct primes, #primes with power,
// NOD (number of divisors), SOD (sum of divisors)
void divisorsInfo(ll n, vector<int>& primes) {
  ll nod = 1, sod = 1, mnP = LLONG_MAX, mxP = 0;
  int cntP = 0, totalP = 0;
  for (ll p : primes) {
    if (p * p > n) break;
    if (n % p) continue;
    mnP = min(mnP, p); mxP = max(mxP, p);
    int k = 0; ll s = 1, pw = 1;
    while (n % p == 0) {
      n /= p; k++; pw *= p; s += pw;
    }
    cntP++; totalP += k;
    nod *= (k + 1);
    sod *= s;
  }
  if (n > 1) { // remaining prime factor
    cntP++, totalP++;
    nod *= 2; sod *= (1 + n);
    mnP = min(mnP, n); mxP = max(mxP, n);
  }
  cout << mnP << " " << mxP << " " << cntP << " "
       << totalP << " " << nod << " " << sod << "\n";
}
