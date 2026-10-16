// O(N): primes, smallest prime factor, Euler phi, Mobius
// factorize x < N in O(log x): while (x > 1) p = spf[x]...
const int N = 1e6 + 5;
int spf[N], phi[N], mu[N];
vector<int> primes;
void linearSieve() {
  phi[1] = mu[1] = 1;
  for (int i = 2; i < N; i++) {
    if (!spf[i]) {
      spf[i] = i; phi[i] = i - 1; mu[i] = -1;
      primes.push_back(i);
    }
    for (int p : primes) {
      if (p > spf[i] || 1LL * i * p >= N) break;
      spf[i * p] = p;
      if (p == spf[i]) { // p^2 divides i * p
        phi[i * p] = phi[i] * p; mu[i * p] = 0;
      } else {
        phi[i * p] = phi[i] * (p - 1); mu[i * p] = -mu[i];
      }
    }
  }
}
// phi of one number, O(sqrt n)
ll phiOf(ll n) {
  ll r = n;
  for (ll p = 2; p * p <= n; p++)
    if (n % p == 0) {
      while (n % p == 0) n /= p;
      r -= r / p;
    }
  if (n > 1) r -= r / n;
  return r;
}
