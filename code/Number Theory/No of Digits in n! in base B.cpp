// digits of n! in base B = floor(log_B(n!)) + 1, O(1)
// lgammal(n + 1) = ln(n!). eps guards exact powers
ll digitsOfFact(ll n, ll B) {
  if (n <= 1) return 1;
  long double lg = lgammal(n + 1.0L) / logl(B);
  return (ll)floorl(lg + 1e-12L) + 1;
}
