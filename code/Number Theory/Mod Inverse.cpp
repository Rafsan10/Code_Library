// a^-1 mod m for ANY m with gcd(a, m) = 1 (uses exgcd)
// returns -1 if inverse doesn't exist
// m prime: power(a, m - 2, m) also works
ll modInv(ll a, ll m) {
  ll x, y;
  ll g = exgcd(((a % m) + m) % m, m, x, y);
  if (g != 1) return -1;
  return (x % m + m) % m;
}
// all inverses 1..n mod prime p in O(n):
// inv[1] = 1; inv[i] = (p - p / i) * inv[p % i] % p
