// isPrime: deterministic for all n < 2^64
// factor(n): prime factors (unsorted, with repeats)
using u64 = uint64_t; using u128 = __uint128_t;
u64 mulmod(u64 a, u64 b, u64 m) { return (u128)a * b % m; }
u64 powmod(u64 b, u64 e, u64 m) {
  u64 r = 1; b %= m;
  for (; e; e >>= 1, b = mulmod(b, b, m))
    if (e & 1) r = mulmod(r, b, m);
  return r;
}
bool isPrime(u64 n) {
  if (n < 2) return false;
  for (u64 p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    if (n % p == 0) return n == p;
  u64 d = n - 1; int s = __builtin_ctzll(d); d >>= s;
  for (u64 a : {2, 325, 9375, 28178, 450775, 9780504,
                1795265022}) {
    u64 x = powmod(a, d, n);
    if (x == 0 || x == 1 || x == n - 1) continue;
    bool composite = true;
    for (int r = 1; r < s && composite; r++) {
      x = mulmod(x, x, n);
      if (x == n - 1) composite = false;
    }
    if (composite) return false;
  }
  return true;
}
mt19937_64 rng64(chrono::steady_clock::now()
                     .time_since_epoch().count());
u64 pollard(u64 n) { // a non-trivial factor of composite n
  if (n % 2 == 0) return 2;
  while (true) {
    u64 x = rng64() % (n - 2) + 2, y = x;
    u64 c = rng64() % (n - 1) + 1, d = 1;
    auto f = [&](u64 v) { return (mulmod(v, v, n) + c) % n; };
    while (d == 1) {
      x = f(x); y = f(f(y));
      d = __gcd(x > y ? x - y : y - x, n);
    }
    if (d != n) return d;
  }
}
void factor(u64 n, vector<u64>& f) {
  if (n == 1) return;
  if (isPrime(n)) { f.push_back(n); return; }
  u64 d = pollard(n);
  factor(d, f); factor(n / d, f);
}
