// count numbers in [1, num] NOT divisible by any of
// div[0..n-1] = num - (|A| - |A&B| + |A&B&C| - ...)
ll PIE(vector<ll>& div, ll num) {
  int n = div.size();
  ll sum = 0;
  for (int msk = 1; msk < (1 << n); ++msk) {
    ll lcm = 1;
    for (int i = 0; i < n && lcm <= num; ++i)
      if (msk >> i & 1) {
        ll g = __gcd(lcm, div[i]);
        if (lcm / g > num / div[i]) lcm = num + 1; // > num
        else lcm = lcm / g * div[i];
      }
    ll cur = num / lcm;
    if (__builtin_popcount(msk) & 1) sum += cur;
    else sum -= cur;
  }
  return num - sum;
}
