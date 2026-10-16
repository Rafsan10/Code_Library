// returns g = gcd(a, b), finds x, y with a*x + b*y = g
ll exgcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1; y = 0;
    return a;
  }
  ll g = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return g;
}
// all solutions: x + k*(b/g), y - k*(a/g)
// a*x + b*y = c solvable iff c % g == 0 (scale by c/g)
